
//Main Program Code for Design Outreach using the SODAQ and SIM900

//Code Creators: Andy Cromer , Erin Galiger , Blake Burwell , Kyle C.
//May 25th, 2014
//Senior Design - Team WaterPump

//Code last Updated: May 25th, 2014


/*Description of Code: 
*This code records the gallons pumped every 1 hr and stores the data.
*The data every hour is stored into its own personal string where it is then time stamped.
*The data is uploaded twice a day.

*/

//Code Begins 

#include <SoftwareSerial.h>
#include <String.h>
int led = 6;  //For debugging use... with either the hall sensor or uploading.

SoftwareSerial mySerial(0,1);   //Create a serial TX and RX for the SIM900

int count = 0;
int countstate = 0 ;
int lastcountstate = 0 ;

unsigned long ts_12pm ;
unsigned long ts_1pm  ;
unsigned long ts_2pm  ;
unsigned long ts_3pm  ;
unsigned long ts_4pm  ;
unsigned long ts_5pm  ;
unsigned long ts_6pm  ;

int HallSensorCounterFinal = 0 ; 

String HallSensorString_12pm = "" ; //12pm's string to hold the data for that hour.
String HallSensorString_1pm  = "" ; //1pm's string to hold the data for that hour.
String HallSensorString_2pm  = "" ; //2pm's string to hold the data for that hour.
String HallSensorString_3pm  = "" ; //3pm's string to hold the data for that hour.
String HallSensorString_4pm  = "" ; //4pm's string to hold the data for that hour.
String HallSensorString_5pm  = "" ; //5pm's string to hold the data for that hour.
String HallSensorString_6pm  = "" ; //6pm's string to hold the data for that hour.

//VOID SETUP!!!!!!
void setup()
{ 
  mySerial.begin(19200);                 // the GPRS baud rate 
  delay(3000);
  mySerial.println("AT");
  delay(3000);
  mySerial.println("AT");
  delay(3000);
  
  pinMode(4, INPUT); // Read the input on pin 4 of Grove Sensor
  pinMode(led, OUTPUT);      //For debugging purposes
  delay(100);
   
}


/////VOID LOOP //////  MAIN Program  
  void loop()
    {
      getHallSensorData_12pm() ; 
      delay(1000);
      getHallSensorData_1pm() ; 
      delay(1000);
      getHallSensorData_2pm() ; 
      delay(1000);
      getHallSensorData_3pm() ; 
      delay(1000);
     // getHallSensorData_4pm() ; 
     // delay(1000);
     // getHallSensorData_5pm() ; 
     // delay(1000);
     // getHallSensorData_6pm() ; 
      delay(1000);
      XivelyCom();
      delay(8000);
      XivelyCom();
      
      delay(1000) ;
      count = 0 ; //clear the counter of the 6pm count so that it can be used for the 12pm count. In all other sections the counter is cleared at the begining of the program. 
 
      //clear the string of the Hall Sensor
       HallSensorString_12pm = "" ;
       HallSensorString_1pm  = "" ;
       HallSensorString_2pm  = "" ;
       HallSensorString_3pm  = "" ;
       HallSensorString_4pm  = "" ;
       HallSensorString_5pm  = "" ;
       HallSensorString_6pm  = "" ;
    }

//HallSensorSections!!!

  void getHallSensorData_12pm()
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
      digitalWrite(led, HIGH) ; 
      delay(700);
      digitalWrite(led, LOW);
      delay(700) ;
      //Four Blinks to show that we have entered one of the Hall Sensor Functions.
      
      //countstate = digitalRead(4) ;
      long time_12pm = 15000;
      lastcountstate = 0 ; 
      ts_12pm = millis() + time_12pm ;
      
      while (millis() < ts_12pm)
        {
          countstate = digitalRead( 4 ); // Go read the pin.
            if (countstate != lastcountstate) 
              {
                lastcountstate=countstate;   
              if (countstate == HIGH) 
                {
                 count++;
                 //mySerial.println("inside loop at 12pm");
                 //mySerial.println(count); 
 
                }  
             }  
         }
            HallSensorCounterFinal = count ;   
            HallSensorString_12pm = ""   ;
            HallSensorString_12pm += HallSensorCounterFinal ;   
    }
    
   void getHallSensorData_1pm()
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
      digitalWrite(led, HIGH) ; 
      delay(700);
      digitalWrite(led, LOW);
      delay(700) ;
      //Four Blinks to show that we have entered one of the Hall Sensor Functions.
      
      //countstate = digitalRead(4) ;
      count = 0 ;
      long time_1pm = 15000;
      lastcountstate = 0 ; 
      ts_1pm = millis() + time_1pm ;
      
      while (millis() < ts_1pm)
        {
          countstate = digitalRead( 4 ); // Go read the pin.
            if (countstate != lastcountstate) 
              {
                lastcountstate=countstate;   
              if (countstate == HIGH) 
                {
                 count++;
                 //mySerial.println("inside loop at 1pm");
                 //mySerial.println(count); 
 
                }  
             }  
         }
            HallSensorCounterFinal = count ;   
            HallSensorString_1pm = ""   ;
            HallSensorString_1pm += HallSensorCounterFinal ;   
    } 
    
  void getHallSensorData_2pm()
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
      digitalWrite(led, HIGH) ; 
      delay(700);
      digitalWrite(led, LOW);
      delay(700) ;
      //Four Blinks to show that we have entered one of the Hall Sensor Functions.
      
      //countstate = digitalRead(4) ;
      count = 0 ;
      long time_2pm = 15000;
      lastcountstate = 0 ; 
      ts_2pm = millis() + time_2pm ;
      
      while (millis() < ts_2pm)
        {
          countstate = digitalRead( 4 ); // Go read the pin.
            if (countstate != lastcountstate) 
              {
                lastcountstate=countstate;   
              if (countstate == HIGH) 
                {
                 count++;
                 //Serial.println("inside loop at 2pm");
                 //Serial.println(count); 
 
                }  
             }  
         }
            HallSensorCounterFinal = count ;   
            HallSensorString_2pm = ""   ;
            HallSensorString_2pm += HallSensorCounterFinal ;   
    }
   
   
   void getHallSensorData_3pm()
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
      digitalWrite(led, HIGH) ; 
      delay(700);
      digitalWrite(led, LOW);
      delay(700) ;
      //Four Blinks to show that we have entered one of the Hall Sensor Functions.
      
      //countstate = digitalRead(4) ;
      count = 0 ;
      long time_3pm = 15000;
      lastcountstate = 0 ; 
      ts_3pm = millis() + time_3pm ;
      
      while (millis() < ts_3pm)
        {
          countstate = digitalRead( 4 ); // Go read the pin.
            if (countstate != lastcountstate) 
              {
                lastcountstate=countstate;   
              if (countstate == HIGH) 
                {
                 count++;
                 //Serial.println("inside loop at 3pm");
                 //Serial.println(count); 
 
                }  
             }  
         }
            HallSensorCounterFinal = count ;   
            HallSensorString_3pm = ""   ;
            HallSensorString_3pm += HallSensorCounterFinal ;   
    }  
     
     
  void getHallSensorData_4pm()
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
      digitalWrite(led, HIGH) ; 
      delay(700);
      digitalWrite(led, LOW);
      delay(700) ;
      //Four Blinks to show that we have entered one of the Hall Sensor Functions.
      
      //countstate = digitalRead(4) ;
      count = 0 ;
      long time_4pm = 15000;
      lastcountstate = 0 ; 
      ts_4pm = millis() + time_4pm ;
      
      while (millis() < ts_4pm)
        {
          countstate = digitalRead( 4 ); // Go read the pin.
            if (countstate != lastcountstate) 
              {
                lastcountstate=countstate;   
              if (countstate == HIGH) 
                {
                 count++;
                 //Serial.println("inside loop at 4pm");
                 //Serial.println(count); 
 
                }  
             }  
         }
            HallSensorCounterFinal = count ;   
            HallSensorString_4pm = ""   ;
            HallSensorString_4pm += HallSensorCounterFinal ;   
    }   
  
  void getHallSensorData_5pm()
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
      digitalWrite(led, HIGH) ; 
      delay(700);
      digitalWrite(led, LOW);
      delay(700) ;
      //Four Blinks to show that we have entered one of the Hall Sensor Functions.
      
      //countstate = digitalRead(4) ;
      count = 0 ;
      long time_5pm = 15000;
      lastcountstate = 0 ; 
      ts_5pm = millis() + time_5pm ;
      
      while (millis() < ts_5pm)
        {
          countstate = digitalRead( 4 ); // Go read the pin.
            if (countstate != lastcountstate) 
              {
                lastcountstate=countstate;   
              if (countstate == HIGH) 
                {
                 count++;
                 //Serial.println("inside loop inside 5pm");
                 //Serial.println(count); 
 
                }  
             }  
         }
            HallSensorCounterFinal = count ;   
            HallSensorString_5pm = ""   ;
            HallSensorString_5pm += HallSensorCounterFinal ;   
    } 

  void getHallSensorData_6pm()
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
      digitalWrite(led, HIGH) ; 
      delay(700);
      digitalWrite(led, LOW);
      delay(700) ;
      //Four Blinks to show that we have entered one of the Hall Sensor Functions.
      
      //countstate = digitalRead(4) ;
      count = 0 ;
      long time_6pm = 15000;
      lastcountstate = 0 ; 
      ts_6pm = millis() + time_6pm ;
      
      while (millis() < ts_6pm)
        {
          countstate = digitalRead( 4 ); // Go read the pin.
            if (countstate != lastcountstate) 
              {
                lastcountstate=countstate;   
              if (countstate == HIGH) 
                {
                 count++;
                 //Serial.println("inside loop at 6pm");
                 //Serial.println(count); 
 
                }  
             }  
         }
            HallSensorCounterFinal = count ;   
            HallSensorString_6pm = ""   ;
            HallSensorString_6pm += HallSensorCounterFinal ;   
    } 


//////////////////////DATA SEND SECTION //////////////////////

///Send to Xively()///
///this function is to send the sensor data to the xively,
//you can see the new value in the xivley.com after we execute this function.///

void XivelyCom()
{
  //Used for visual confirmation, 5 seconds on means upload begining
  digitalWrite(led, LOW );
  delay(100);
  digitalWrite(led, HIGH) ; 
  delay(5000) ; 
  digitalWrite(led, LOW) ;
  delay(100);
  
   mySerial.println("AT");
   delay(1000);
   mySerial.println("AT");
   delay(1000);
  
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
  
  //mySerial.println("{\"id\": \"xivelyBadgerMeter\", \"datapoints\":[{\"at\": \2014-05-25T23:05:30Z\", \"value\": \""+HallSensorString_12pm + "\"}] ,") ;
  //delay(500);
  //ShowSerialData();
  
  mySerial.println("{\"id\" : \"xivelyBadgerMeter\" , \"datapoints\" : [ { \"at\" : \"2014-05-27T04:40:30Z\" , \"value\" : \"" + HallSensorString_12pm + "\" } , {\"at\" : \"2014-05-27T04:45:30Z\" , \"value\" : \"" + HallSensorString_1pm + "\"  } , {\"at\" : \"2014-05-27T04:50:30Z\" , \"value\" : \"" + HallSensorString_2pm + "\"  } , {\"at\" : \"2014-05-27T04:55:30Z\" , \"value\" : \"" + HallSensorString_3pm + "\"  } ] } , "); 
   delay(500) ; 
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

digitalWrite(led, HIGH) ; 
       delay(300);
       digitalWrite(led, LOW);
       delay(300) ;
       digitalWrite(led, HIGH) ; 
       delay(300);
       digitalWrite(led, LOW);
       delay(300) ;

}











