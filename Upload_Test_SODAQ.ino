//Upload Testing for SIM900 on SODAQ board.

//Andy Cromer
//April 26th, 2014
//Senior Design - Team WaterPump

//Code last Updated: April 27th, 2014


/* Description of Code: This code allows for the user to test the SIM900 with the 
SODAQ board by sending a text message to a desired user. 

*/

//Program Begin:

#include <SoftwareSerial.h>
#include <String.h>
int led = 6;  //For debugging use...

SoftwareSerial mySerial(0,1);   //Create a serial TX and RX for the SIM900

void setup()
{ 
  mySerial.begin(19200);                 // the GPRS baud rate 
  delay(3000);
  mySerial.println("AT");
  delay(3000);
  mySerial.println("AT");
  delay(3000);
  pinMode(led, OUTPUT);
  
}

void SendTextMessage() //Used to quickly check service with carrier. Sending 
//a quick text is a great check. 
{
  mySerial.println("AT+CMGF=1\r");    //Because we want to send the SMS in text mode
  delay(100);
  mySerial.println("AT + CMGS = \"+17202347869\"");//send sms message, be careful need to add a country code before the cellphone number
  delay(100);
  mySerial.println("This is the SODAQ, coming in loud and clear!");//the content of the message
  delay(100);
  mySerial.println((char)26);//  the ASCII code of the ctrl+z is 26
  delay(100);
  mySerial.println();
  delay(100);
  mySerial.println("AT$GPSACP") ;
  
  //Used for visual conformation... two blinks = texts
  digitalWrite(led, HIGH) ; 
  delay(1000) ; 
  digitalWrite(led, LOW) ;
  digitalWrite(led, HIGH) ; 
  delay(1000) ; 
  digitalWrite(led, LOW) ;
  
}


//////////////////////DATA SEND SECTION //////////////////////

///Send to Xively()///
///this function is to send the sensor data to the xively,
//you can see the new value in the xivley.com after we execute this function.///

void XivelyCom()
{
  //Used for visual confirmation, 5 seconds on means upload begining
  digitalWrite(led, HIGH) ; 
  delay(5000) ; 
  digitalWrite(led, LOW) ;
  delay(100);
  
   mySerial.println("AT+CGATT?");
   delay(1000);
   //ShowSerialData();   //These are used to Debug in when Serial Monitor is available.
 
   //mySerial.println("Checking Internet Connection...");
   mySerial.println("AT+CREG?\r");
   delay(1000);
   //ShowSerialData();
 
   mySerial.println("at+cstt=?");
   delay(1000);
   //ShowSerialData();
 
   mySerial.println("at+cstt?");
   delay(1000);
   //ShowSerialData(); 
 
   mySerial.println("AT+CSTT=\"wap.cingular\",\"wap@cingulargprs.com\",\"CINGULAR1\"" )  ;//start task and setting the APN,
   delay(4000);
   //ShowSerialData();
 
 //Template for writting the above code for APN user to get onto AT&T service.
 //mySerial.println("AT+CSTT=\"APN\",\"USER\",\"PWD\"")  ;//start task and setting the APN,
 // delay(3000);
 // ShowSerialData();
 

  //mySerial.println("Bring up the wireless connection");
  mySerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
  //ShowSerialData();
 
 
  mySerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
  //ShowSerialData();
  
  //Stop here for void setup in attempt2
  mySerial.println("AT+CIPSTATUS");
  delay(3000);
  //ShowSerialData();
  
  //mySerial.println("AT+CIPSPRT=0");
  //delay(3000);
  //ShowSerialData();
  
  mySerial.println("AT+CIPHEAD=1"); //- Tells module to add an 'IP Header' to receive data 
  delay(1000);
  //ShowSerialData();
  
  //// numeric IP for api.xively.com (Using IP uses less memory then actual address.)
  mySerial.println("AT+CIPSTART=\"TCP\",\"216.52.233.121\",\"8081\""); // - Start up TCP connection (mode, IP address/name, port) 
  delay(2000);
  //ShowSerialData();
  
  // DATA Being SENT!!!!
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(2000);
  //ShowSerialData();
  
  //Example Data Points
  String humidity = "1025";//these 4 line code are imitate the real sensor data, because the demo did't add other sensor, so using 4 string variable to replace.
  String moisture = "1222";//you can replace these four variable to the real sensor data in your project
  String temperature = "40";//
  String barometer = "67.87";//
  
  //Sending Data Points
  mySerial.print("{\"method\": \"put\",\"resource\": \"/feeds/159150126\",\"params\" : {},");//here is the feed you apply from pachube
  delay(500);
  //ShowSerialData();
  
  mySerial.print("\"headers\": {\"X-ApiKey\":");//in here, you should replace your pachubeapikey
  delay(500);
  //ShowSerialData();
 mySerial.print("\"7jc0RGaysFDK39ePIxcLeuRBSTOGbwqwxhK2TAAFw9Lgz82o\"},\"body\":");
  delay(500);
  //ShowSerialData();

  mySerial.print(" {\"version\": \"1.0.0\",\"datastreams\": ");
  delay(500);
  //ShowSerialData();
  mySerial.println("[{\"id\": \"Barometer1_xively\",\"current_value\": \"" + barometer + "\"},");
  delay(500);
  //ShowSerialData();
  mySerial.println("{\"id\": \"Humidity1_xively\",\"current_value\": \"" + humidity + "\"},");
  delay(500);
  //ShowSerialData();
  mySerial.println("{\"id\": \"Moisture1_xively\",\"current_value\": \"" + moisture + "\"},");
  delay(500);
  //ShowSerialData();
  
  //mySerial.println("{\"id\": \"xivelyWaterSensor\",\"current_value\": \"" + flowDataString +  "\"},");
  //delay(500);
  //ShowSerialData();
  
  mySerial.println("{\"id\": \"Temperature1_xively\",\"current_value\": \"" + temperature + "\"}]},\"token\": \"lee\"}");
  delay(500);
  //ShowSerialData();
 
  mySerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  mySerial.println();
  //ShowSerialData();
 
  mySerial.println("AT+CIPCLOSE");//close the connection
  delay(100);
  //ShowSerialData();

delay(100);
}
 
/* //(Use this to debug if you have a serial monitor.... 
   // Recocomend using D4 and D5 hookups according to SODAQ site.)

void ShowSerialData() 
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
}

*/

void loop()
{
  SendTextMessage();
  delay(5000); 
  XivelyCom();
}



