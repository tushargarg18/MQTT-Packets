#include<SoftwareSerial.h>

SoftwareSerial com(2,3);

const char  connectpkt[] = {0x10,0x2C,0x00,0x06,0x4D,0x51,0x49,0x73,0x64,0x70,0x03,0xC2,0x01,0x2C,0x00,0x06,0x41,0x42,0x43,0x44,0x45,0x46,0x00,0x08,0x6A,0x7A,0x7A,0x6A,0x66,0x68,0x6C,0x66,0x00,0x0C,0x38,0x4F,0x72,0x6E,0x59,0x6D,0x79,0x32,0x4D,0x4F,0x74,0x36,0x82,0x09,0x00,0x01,0x00,0x04,0x68,0x6F,0x6D,0x65,0x00};
const char pubpkt[] ={0x30,0x0B,0x00,0x04,0x68,0x6F,0x6D,0x65,0x68,0x65,0x6C,0x6C,0x6F};
const char subpkt[] ={0x82,0x09,0x00,0x01,0x00,0x04,0x68,0x6F,0x6D,0x65,0x00};
void setup() 
{
  String resp;
  Serial.begin(9600);
  com.begin(9600);
  //resp = command("AT+CWJAP_CUR=\"Smarthink Tech\",\"Akhil.123@:\"",15000);
  //Serial.println(resp);
  command("AT+RST",1000);
  delay(15000);
  resp = command("AT+CIPSTART=\"TCP\",\"postman.cloudmqtt.com\",12607,0",2000);
  Serial.println(resp);
  resp = command("AT+CIPSEND=57",1000);
  Serial.print(resp);
  int i = 0;
  for(i = 0; i< 57;++i)
  {
    com.write(connectpkt[i]);
  }
  resp = rec(4000);
  Serial.println(resp);
}

void loop() 
{
  char input;
  while(com.available())
  {
    input = com.read();
    Serial.println(input);
  }
}
String command(const char *toSend, unsigned long milliseconds) 
{
  String result; 
  com.println(toSend);
  unsigned long startTime = millis();
  while (millis() - startTime < milliseconds) 
  {
   while(com.available()) 
   {
    result += char(com.read());
   }
  } 
  return result;
}
String rec(unsigned long milliseconds) 
{
  String result; 
  unsigned long startTime = millis();
  while (millis() - startTime < milliseconds) 
  {
   while(com.available()) 
   {
    result += char(com.read());
   }
  } 
  return result;
}
