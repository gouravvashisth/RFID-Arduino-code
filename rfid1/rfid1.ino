#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  
 #include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 6);// Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
   
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(5,OUTPUT);
 

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  digitalWrite(5,LOW);
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "A9 66 A2 5A") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    digitalWrite(5,HIGH);
    delay(200);
    digitalWrite(5,LOW);
    Serial.println();
    delay(3000);
    
     mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919467425362\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Dear parents, Gourav vashisth is present");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
    
  }
  else if(content.substring(1) == "32 A4 EC 90") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
     digitalWrite(5,HIGH);
    delay(200);
    digitalWrite(5,LOW);
    Serial.println();
    delay(3000);
   
     mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919467425362\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Dear parents, Aman sharma is present");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
    
  }
 
 else   {
  digitalWrite(5,HIGH);
    delay(2000);
    digitalWrite(5,LOW);
    Serial.println(" Access denied");
    delay(3000);
     mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919467425362\"\r"); // Replace x with mobile number
  delay(1000);
  
  mySerial.println("Dear parents,Gourav vashisth is absent");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
   
  }
} 
