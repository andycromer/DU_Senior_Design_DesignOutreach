//Upload Testing for SIM900 on SODAQ board.

//Andy Cromer
//May 6th, 2014
//Senior Design - Team WaterPump

//Code last Updated: May 6th, 2014


/* Description of Code: This code allows for the user to test the SIM900 with the 
SODAQ board by sending an upload string to xively.com by using the Badger Meter.

*/

//Program Begin:

#include <SoftwareSerial.h>
#include <String.h>
int led = 6;  //For debugging use... with either the hall sensor or uploading.

SoftwareSerial mySerial(0,1);   //Create a serial TX and RX for the SIM900

// Hallsensor (input) = digital pin 4
int HALLSENSORPIN = 4 ; 

// Names of the strings created
String inputString = "" ; //a string to hold incoming data, (empty at the moment)
boolean stringComplete = false ; // True or False whether the string is complete (For upload)
String HallSensorString = "" ; //a string to hold the incoming data of the Hall Sensor

//HallSensor Counter
int HallSensorCounter = 0 ;
int HallSensorCounterFinal = 0 ;
unsigned long lastmillis = 0; 

//VOID SETUP!!!!!!
void setup()
{ 
  mySerial.begin(19200);                 // the GPRS baud rate 
  delay(3000);
  mySerial.println("AT");
  delay(3000);
  mySerial.println("AT");
  delay(3000);
  
  pinMode(led, OUTPUT);      //For debugging purposes
  delay(100);
  
  inputString.reserve(200); // reserve 200 bytes for the inputString:
  
  // Hall Sensor Stuff
  pinMode(HALLSENSORPIN, INPUT );
  digitalWrite(HALLSENSORPIN , HIGH) ;  //Set High so they won't tick away.
  //attachInterrupt(0 , hall_interrupt , FALLING ) ; //interrupt is attached, pin 4  
}

//HALLSENSOR FUNCTION !!!!!
void getHallSensorData()
{
  digitalWrite(led, HIGH) ; 
  delay(700) ; 
  digitalWrite(led, LOW) ;
  delay(700);
  digitalWrite(led, HIGH) ; 
  delay(700) ; 
  digitalWrite(led, LOW) ;
  delay(700);
  digitalWrite(led, HIGH) ; 
  delay(700) ; 
  digitalWrite(led, LOW) ;
  delay(700);
  
  attachInterrupt(0 , hall_interrupt , FALLING ) ; //interrupt is attached, pin 4 
  
  digitalWrite(led, HIGH );
  delay(3000) ; 
  digitalWrite(led,LOW ) ; 
  
  if(millis() - lastmillis >= 3000)
  {
    //Update hallsensor data every 3 seconds.
    
    detachInterrupt(0) ; //Disable interrupt when calculating
    
    HallSensorCounterFinal = HallSensorCounter ; 
    
    HallSensorString += HallSensorCounterFinal ; 
    
    HallSensorCounter = 0 ; //Restart the Hall Sensor Counter
    lastmillis = millis() ; //Update the lastmillis
    //attachInterrupt(0, hall_interrupt , FALLING ) ; //enable interrupt
    
  }
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
  
  mySerial.print("\"headers\": {\"X-ApiKey\":");//in here, you should replace your xively key
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
  
  mySerial.println("{\"id\": \"xivelyBadgerMeter\",\"current_value\": \"" + HallSensorString +  "\"},");
  delay(500);
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


/////VOID LOOP //////

void loop()
{
  getHallSensorData() ; 
  delay(5000); 
  XivelyCom();
  delay(1000) ; 
  
  //clear the strings:
  inputString = "" ;
  //clear the string of the Hall Sensor
  HallSensorString = "" ; 
  
}


void hall_interrupt()
{
  //This code will be executed every time the interrupt 0 (pin2) gets low.
  HallSensorCounter++ ; 
}


/*
 SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available. This is according to Arduino CC.
*/

void serialEvent() 
{
  while(Serial.available()) 
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') 
    {
      stringComplete = true;
    }
     //Serial.println(inputString.length());
  }
}


//DEBUGGING PROGRAM ONLY IF YOU HAVE A SERIAL MONITOR 
/* //(Use this to debug if you have a serial monitor.... 
   // Recocomend using D4 and D5 hookups according to SODAQ site?)

void ShowSerialData() 
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
}

*/









