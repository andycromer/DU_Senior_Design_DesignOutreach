//Real Time Clock (RTC) to adjust the time on the SODAQ which uses the...
// DS3231 Timer.

//Andy Cromer
//April 26th, 2014
//Senior Design - Team WaterPump

//Code last Updated: April 28th, 2014

#include "Wire.h"
#define DS1307_ADDRESS 0x68
#include "Sodaq_DS3231.h"

void setup()
  {
    Wire.begin();
    Serial.begin(9600);
    setDS3231time() ;
  }

void loop()
  {
    printDate();
    delay(1000);
  }

byte bcdToDec(byte val)  
  {
    // Convert binary coded decimal to normal decimal numbers
    return ( (val/16*10) + (val%16) );
  }



void setDS3231time()
{
     
  byte second = 0 ;
  byte minute = 31 ;
  byte hour   = 4 ; // 4pm
  byte dayOfWeek = 0 ;
  byte date = 13 ;
  byte month = 04 ;
  byte year = 14 ;
  
  // sets time and date data to DS3231
     Wire.beginTransmission(DS1307_ADDRESS);
     Wire.write(0); // set next input to start at the seconds register
     Wire.write(bcdToDec(second));
     Wire.write(bcdToDec(minute));
     Wire.write(bcdToDec(hour));
     Wire.write(bcdToDec(dayOfWeek));  // set day of week (1=Sunday, 7=Saturday)
     Wire.write(bcdToDec(date)); // set date (1 to 31)
     Wire.write(bcdToDec(month));
     Wire.write(bcdToDec(year));
     Wire.endTransmission();
}


void printDate()
  {
    // Reset the register pointer
    Wire.beginTransmission(DS1307_ADDRESS);
    Wire.write(0);
    Wire.endTransmission();

    Wire.requestFrom(DS1307_ADDRESS, 7);

    int second = bcdToDec(Wire.read());
    int minute = bcdToDec(Wire.read());
    int hour = bcdToDec(Wire.read() & 0b111111); //24 hour time
    int weekDay = bcdToDec(Wire.read()); //0-6 -> sunday - Saturday
    int date = bcdToDec(Wire.read());
    int month = bcdToDec(Wire.read());
    int year = bcdToDec(Wire.read());

  //print the date EG   3/1/11 23:59:59
  Serial.print(month);
  Serial.print("/");
  Serial.print(date);
  Serial.print("/");
  Serial.print(year);
  Serial.print(" ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.println(second);
  
  rtc.convertTemperature();            //convert current temperature into registers       
  float tempFloat = rtc.getTemperature(); //read registers and display the temperature

  Serial.println(tempFloat) ; 

}
