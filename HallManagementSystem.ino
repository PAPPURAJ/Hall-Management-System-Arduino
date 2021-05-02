#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN D4
#define RST_PIN D2


#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "hall-management-128e9-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "ooSKsFy5F0PHgbAaEvsw7JmE6iSjKEC6XkujM6RF"
#define WIFI_SSID "PAPPURAJ BHOTTACHARJEE KORNO-M21"
#define WIFI_PASSWORD "pppppppP"


MFRC522 mfrc522(SS_PIN, RST_PIN); 

int dd=1,mm=1,yy=2021;



FirebaseData firebaseData;
FirebaseJson json;

void setup() {
  Serial.begin(9600);   // Initiate a serial communication
    SPI.begin(); 
  mfrc522.PCD_Init();

  

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  
}

void loop() {
  // put your main code here, to run repeatedly:
int i=checkCard();

  switch(i) {
    case 1:{
      writeDB("CHANDAN");
      break;
    }
    case 2:{
      writeDB("RUME");
      break;
    }
    case 3:{
      writeDB("SONIA");
      break;
    }
    case 4:{
      writeDB("CHANDAN");
      break;
    }
    

  
    
  }
  


  Serial.println(i);
  delay(1000);
}








void writeDB(String field){
  
 Firebase.setString(firebaseData, "/"+field+"/"+String(dd)+"-"+String(mm)+"-"+String(yy)+"/",String(1));
  
}


void inc(){

  dd++;

  if(dd>30)
    {
      mm++;
      dd=1;
    }

   if(mm>12){
    yy++;
    mm=1; 
   }
  
}


int checkCard(){
  

  // Look for new cards
if ( ! mfrc522.PICC_IsNewCardPresent())
{
return -1;
}
// Select one of the cards
if ( ! mfrc522.PICC_ReadCardSerial())
{
return -1;
}
//Show UID on serial monitor
//Serial.print("UID tag :");
String content= "";
byte letter;
for (byte i = 0; i < mfrc522.uid.size; i++)
{
//Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//Serial.print(mfrc522.uid.uidByte[i], HEX);
content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
content.concat(String(mfrc522.uid.uidByte[i], HEX));
}

content.toUpperCase();

    if (content.substring(1) == "19 D7 5E B2") //change here the UID of the card/cards that you want to give access
    {
        return 1;
    }

    else if(content.substring(1) == "FA D4 0E 28"){

        return 2;
    }
    else if(content.substring(1) == "39 9D 72 B2"){

        return 3;
    }
    else if(content.substring(1) == "19 D6 70 B2"){

        return 4;
    }

    else   {
       return -1;
    }
    return -1;
}
