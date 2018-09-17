#include<SoftwareSerial.h>
char ch[20];
SoftwareSerial mySerial(2, 3);
void setup() {
  
  Serial.begin(9600);
  mySerial.begin(9600);

}

void loop() {
  while (mySerial.available())
{
  for (int i; i < 12; i++)
      ch[i] = mySerial.read();
    ch[12] = '\0';
  }
  Serial.print(ch);
}
