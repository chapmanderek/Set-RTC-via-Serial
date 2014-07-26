/*Sets RTC to time given through serial monitor
Derek Chapman 6-21-14
v1 7/6/14
*/

#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>

int incoming = 99;
int RTCaddress = 0x68;

void setup()
{
  
  Serial.begin(57600);
  Wire.begin();
}

void loop()
{
  printmenu();
  
  while(Serial.available() < 1) ;// wait for Arduino Serial Monitor
  incoming = Serial.parseInt();
  
  if(incoming == 1)
    {setRTCfromSerial();}
  else if(incoming == 2)
    {
      for(int i = 1; i < 6; i++)
        {getRTCtime(); delay(1000);}
    }
  else if(incoming == 3)
    {getRTCdate();}
  else if(incoming == 4)
    {setduino();}
  else if(incoming == 5)
    {getduinotime();}
  else if(incoming == 6)
    {getduinodate();}  
}

void printmenu()
{
  Serial.println("\n---What would you like to do?");
  Serial.println("1.  Update time on RTC");
  Serial.println("2.  Check time on RTC");
  Serial.println("3.  Check date on RTC");
  Serial.println("4.  RTC --> Duino");
  Serial.println("5.  Check time on duino");
  Serial.println("6.  Check date on duino\n");
}

void setRTCfromSerial()  //gets time data from serial input then sets the RTC
{
  Wire.beginTransmission(RTCaddress);  
  Wire.write(0);  //start at address # 0, seconds
  Wire.endTransmission();
  
  tmElements_t tm;
  Serial.println("\n---RTC Time Set---");
  
  Serial.print("Enter military hours:  ");
  while(Serial.available() < 1) ;// wait for Arduino Serial Monitor
  tm.Hour = Serial.parseInt();
  Serial.println(tm.Hour);
  
  Serial.print("Enter minutes:  ");
  while(Serial.available() < 1);
  tm.Minute = Serial.parseInt();
  Serial.println(tm.Minute);
  
  Serial.print("Enter seconds:  ");
  while(Serial.available() < 1);
  tm.Second = Serial.parseInt();
  Serial.println(tm.Second);
  
  Serial.print("Enter month:  ");
  while(Serial.available() < 1);
  tm.Month = Serial.parseInt();
  Serial.println(tm.Month);
  
  Serial.print("Enter date:  ");
  while(Serial.available() < 1);
  tm.Day = Serial.parseInt();
  Serial.println(tm.Day);
  
  Serial.print("Enter four digit year:  ");
  while(Serial.available() < 1);
  tm.Year = Serial.parseInt() - 1970;
  Serial.println(tm.Year);
  
  Serial.print("Fire it up?");
  while(Serial.available() < 1);
  Serial.read();

  if(RTC.write(tm))
    {Serial.println("The following time was successfully written to the RTC.");}
  else
    {Serial.println("Robot Error!  Setting the RTC time failed.");}
  
  Serial.println();
  getRTCtime();
  getRTCdate();
}

void getRTCtime()
{
  tmElements_t temptm;
  
  if(RTC.read(temptm))
    {  
      Serial.print("Current time according to RTC is: ");
      Serial.print(temptm.Hour, DEC);  Serial.print(":");  
  
      if(temptm.Minute < 10)
        {Serial.print("0");}
      Serial.print(temptm.Minute, DEC); Serial.print(":");  
  
      if(temptm.Second < 10)
        {Serial.print("0");}
      Serial.println(temptm.Second, DEC);
    }
      
  else
    {Serial.println("\nRobot error!  Reading RTC failed!");}
  
}

void getRTCdate()
{
  tmElements_t temptm;
  
  if(RTC.read(temptm))
    {
      Serial.println("Current date according to RTC is: ");
      Serial.print(temptm.Month, DEC); Serial.print("/"); 
      Serial.print(temptm.Day, DEC); Serial.print("/"); 
      Serial.println(temptm.Year, DEC);
    }
  else
    {Serial.println("\nRobot error!  Reading RTC failed!");}
}

void setduino()
{
  time_t t = RTC.get();
 
  if(t != 0)
    {
      setTime(t);
      Serial.println("Duino time set succesfully from RTC");
    }
  else{Serial.println("Robot error setting duino time from RTC!");}
}

void getduinotime()
{
  Serial.println("Current time according to duino is: ");
  Serial.print(hour());  Serial.print(":");  
  
  if(minute() < 10)
    {Serial.print("0");}
  Serial.print(minute()); Serial.print(":");  
  
  if(second() < 10)
    {Serial.print("0");}
  Serial.println(second());
}

void getduinodate()
{
  int dayofweek = weekday();
  
  Serial.println("Current date according to duino is: ");
  Serial.print(month()); Serial.print("/");  
  Serial.print(day());  Serial.print("/");
  Serial.println(year());
  
  Serial.print("Today is ");
  
  switch(dayofweek)
  {
    case 1:
    Serial.println("Sunday"); break;
    
    case 2:
    Serial.println("Monday"); break;

    case 3:
    Serial.println("Tuesday"); break;

    case 4:
    Serial.println("Wednesday"); break;

    case 5:
    Serial.println("Thursday"); break;

    case 6:
    Serial.println("Friday"); break;

    case 7:
    Serial.println("Saturday"); break;

    default:
    Serial.println("Fribs-day"); break;
  }
}
