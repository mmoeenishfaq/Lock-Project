#include <usbhid.h>
#include <usbhub.h>
#include <hiduniversal.h>
#include <hidboot.h>
#include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial sw(0, 1); // RX, TX
int index1=0;
char arr[4]="";
class MyParser : public HIDReportParser {
  public:
    MyParser();
    void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
  protected:
    uint8_t KeyToAscii(bool upper, uint8_t mod, uint8_t key);
    virtual void OnKeyScanned(bool upper, uint8_t mod, uint8_t key);
    virtual void OnScanFinished();
};

MyParser::MyParser() {}

void MyParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
  // If error or empty, return
  if (buf[2] == 1 || buf[2] == 0) return;

  for (uint8_t i = 7; i >= 2; i--) {
    // If empty, skip
    if (buf[i] == 0) continue;

    // If enter signal emitted, scan finished
    if (buf[i] == UHS_HID_BOOT_KEY_ENTER) {
      OnScanFinished();
    }

    // If not, continue normally
    else {
      // If bit position not in 2, it's uppercase words
      OnKeyScanned(i > 2, buf, buf[i]);
    }

    return;
  }
}

uint8_t MyParser::KeyToAscii(bool upper, uint8_t mod, uint8_t key) {
  // Letters
  if (VALUE_WITHIN(key, 0x04, 0x1d)) {
    if (upper) return (key - 4 + 'A');
    else return (key - 4 + 'a');
  }

  // Numbers
  else if (VALUE_WITHIN(key, 0x1e, 0x27)) {
    return ((key == UHS_HID_BOOT_KEY_ZERO) ? '0' : key - 0x1e + '1');
  }

  return 0;
}

void MyParser::OnKeyScanned(bool upper, uint8_t mod, uint8_t key) {
  uint8_t ascii = KeyToAscii(upper, mod, key);
  Serial.print((char)ascii);
  //sw.print((char)ascii);
}

void MyParser::OnScanFinished() {
  Serial.println();
}

USB          Usb;
USBHub       Hub(&Usb);
HIDUniversal Hid(&Usb);
MyParser     Parser;

void setup() {
  Serial.begin( 115200 );
  //Serial.println("Start");
    pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);

  if (Usb.Init() == -1) {
    //Serial.println("OSC did not start.");
  }

  delay( 200 );

  Hid.SetReportParser(0, &Parser);
   sw.begin(115200);
}

void loop() {
Usb.Task();  
  
  int star = digitalRead(2);   // keypad pin 2
  int seven = digitalRead(3);  // keypad pin 3
  int four = digitalRead(4);  // keypad pin 4
  int one = digitalRead(5);  // keypad pin 5
  int zero = digitalRead(6);  // keypad pin 6
  int eight = digitalRead(7);  // keypad pin 7
  int five = digitalRead(8);  // keypad pin 8
  int two = digitalRead(A0);  // keypad pin 9
  int pound = digitalRead(10);  // keypad pin 10
  int nine = digitalRead(11);  // keypad pin 11
  int six = digitalRead(12);  // keypad pin 12
  int three = digitalRead(A5);  // keypad pin 13
  
  // When the digitalRead() of a pin returns 0 the corresponding 
  // key label is printed via Serial.
  if(!star){  arr[index1]='*';  index1++; delay(200); }
  if(!seven){ arr[index1]='7'; index1++; delay(200); }
  if(!four){  arr[index1]='4'; index1++; delay(200); }
  if(!one){  arr[index1]='1'; index1++; delay(200); }
  if(!zero){  arr[index1]='0'; index1++; delay(200); }
  if(!eight){  arr[index1]='8'; index1++; delay(200); }
  if(!five){  arr[index1]='5'; index1++; delay(200); }
  if(!two){  arr[index1]='2'; index1++; delay(200); }
  if(!pound){  arr[index1]='#'; index1++; delay(200); }
  if(!nine){  arr[index1]='9'; index1++; delay(200); }
  if(!six){  arr[index1]='6'; index1++; delay(200); }
  if(!three){  arr[index1]='3'; index1++; delay(200); }
  if(index1==4)
  {
    arr[4]='\0';
Serial.println(arr);
//sw.println(arr);
index1=0;
  
  }
  


}
