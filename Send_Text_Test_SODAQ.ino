//Text Message Configuration and Testing for SIM900 on SODAQ board.

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

void SendTextMessage()
{
  mySerial.println("AT+CMGF=1\r");    //Because we want to send the SMS in text mode
  delay(100);
  mySerial.println("AT + CMGS = \"+1xxxxxxxxxx\"");//send sms message, be careful need to add a country code before the cellphone number
  delay(100);
  mySerial.println("This is the SODAQ, coming in loud and clear!");//the content of the message
  delay(100);
  mySerial.println((char)26);//  the ASCII code of the ctrl+z is 26
  delay(100);
  mySerial.println();
  delay(100);
  mySerial.println("AT$GPSACP") ;  
}


void loop()
{
  SendTextMessage();
  digitalWrite(led, HIGH) ; 
  delay(2000) ; 
  digitalWrite(led, LOW) ;
  delay(8000); 
  
 // do // remove this loop at your peril
 // { 
 //  delay(1); 
 // }
 // while (1>0);
}
  





