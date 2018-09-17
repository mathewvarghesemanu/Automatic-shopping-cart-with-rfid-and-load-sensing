
#include<SoftwareSerial.h>
#include <LiquidCrystal.h>
int count = 0;                                          // count = 0
char input[12];                                         // character array of size 12
char idlist[20][20] = {"$0009680529", "$0009665459"};
char itemlist[20][20] = {"pears soap  35  itemno1", "classmates  40  itemno2   "};
char finallist[2][20];
int index = 99, flag = 0;
int totalamt = 0, c = 0, d = 0, no1 = 0, no2 = 0;
int delready = 0, readready = 1, start = 0;
int delpin = 6;
int printpin = 8;
int statusled = 3;
int buzzerpin = 4;
const int rs = A5, en = A4, d4 = 12, d5 = 11, d6 = 10, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SoftwareSerial mySerial(2, 3);
void setup()
{


  pinMode(delpin, INPUT);
  pinMode(buzzerpin, OUTPUT);
  pinMode(statusled, OUTPUT);
  digitalWrite(statusled, LOW);
  mySerial.begin(9600);
  Serial.begin(9600);                                  // begin serial port with baud rate 9600bps
  lcd.begin(16, 2);
}
void loop()
{
  if (start == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("   Welcome!");
    lcd.setCursor(0, 1);
    lcd.print(" Billing system");
    delay(2000);
    start = 1;
  }
  if (digitalRead(printpin) == HIGH)
  {
    for(int i=0;i<50;i++)
    Serial.println("");
    
    
    if (no1>0)
    {
     
         Serial.print("Pears Soap");
        Serial.print("Pears Soap");
        Serial.print("            Cost per item:35");
        Serial.print("            No : ");
        Serial.print(no1);
        Serial.print("            Cost : ");
        Serial.print(no1*35);
         Serial.println("");
        
    
    }
    if (no2>0)
    {
       Serial.print("classmates notebook");
        Serial.print("   Cost per item:40");
        Serial.print("            No : ");
        Serial.print(no1);
        Serial.print("            Cost : ");
        Serial.print(no1*40);
         Serial.println("");
    }
    Serial.print("Total amount : ");
    Serial.println(totalamt);
  }
  
  if (digitalRead(delpin) != HIGH)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Total amount:");
    lcd.setCursor(1, 6);
    lcd.print(totalamt);
  }

  digitalWrite(statusled, LOW);
  delay(500);
  flag = 0;
  c = 0;
  d = 0;
  index = 99;
  input[1] = '7';
  input[2] = '7';
  input[0] = '7';
  if (digitalRead(delpin) == HIGH)
  {
    delready = 1;
    readready = 0;
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("delete mode");
    digitalWrite(statusled, HIGH);
  }
  else
  {
    delready = 0;
    readready = 1;
  }


  if (mySerial.available())
  {

    count = 0;
    while (mySerial.available() && count < 12)         // Read 12 characters and store them in input array
    {
      input[count] = mySerial.read();
      count++;
      delay(5);
    }
    input[12] = '\0';
    digitalWrite(buzzerpin, HIGH);
    digitalWrite(statusled, HIGH);
    delay(200);
    digitalWrite(buzzerpin, LOW);
    digitalWrite(statusled, LOW);
  }

  for (int i; i < 12; i++)
  {
    if (input[i] == idlist[0][i])
      c++;
    if (input[i] == idlist[1][i])
      d++;
  }

  //Serial.println(c);
  if (c == 11)
  {
    index = 0;
    flag = 1;
  }
  if (d == 11)
  {
    index = 1;
    flag = 1;
  }
  if (c != 11 && d != 11)
    index = 99;

  if (readready == 1)
    if (flag == 1)
      if (index == 1)
      {
        no1++;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pears Soap");
        lcd.setCursor(0, 1);
        lcd.print("Cost:35");
        lcd.setCursor(12, 1);
        lcd.print("No:");
        lcd.print(no1);
        delay(2000);
      }
      else if (index == 0)
      {
        no2++;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("classmates");
        lcd.setCursor(0, 1);
        lcd.print("Cost:40");
        lcd.setCursor(12, 1);
        lcd.print("No:");
        lcd.print(no2);
        delay(2000);
      }

  if (delready == 1)
    if (flag == 1)
      if (index == 1)
      {
        if (no1 > 0)
        {
          no1--;
         lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pears Soap");
        lcd.setCursor(0, 1);
        lcd.print("Cost:35");
        lcd.setCursor(12, 1);
        lcd.print("No:");
        lcd.print(no1);
        delay(2000);
        }
      }
      else if (index == 0)
        if (no2 > 0)
        {
          no2--;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("classmates");
          lcd.setCursor(0, 1);
          lcd.print("Cost:40");
          lcd.setCursor(12, 1);
          lcd.print("No:");
          lcd.print(no2);
          delay(2000);
        }
  if (flag == 1)
  {
    totalamt = no1 * 35 + no2 * 40;
  }
  // Serial.println(input);
  // Serial.println(idlist[0]);
  //Serial.println(totalamt);
  //Serial.print(no1);                             // Print RFID tag number
  //Serial.println(no2);
  // Serial.println(flag);

}

