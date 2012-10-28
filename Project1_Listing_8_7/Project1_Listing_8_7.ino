#include <SPI.h>
#include <Adb.h>
#include <DHT22.h>
 
// Adb connection.
Connection * connection;
 
// Elapsed time for ADC sampling. The rate at which ADC value is sent to Android device.
long lastTime;

// Data wire is plugged into port 7 on the Arduino
#define DHT22_PIN 7

// Setup a DHT22 instance
DHT22 myDHT22(DHT22_PIN);
DHT22_ERROR_t errorCode;

#define LIGHT_PIN       0

//State of LED. Initially OFF. 
uint8_t LEDState=0;

// sensor variables
float temp;
float humid;
int light;

char buf1[16];
char buf2[16];
char buf3[16];
 
// Event handler for the shell connection. 
// This event handler is called whenever data is sent from Android Device to Seeeduino ADK.
// Any data / command to be sent to I/O of ADK has to be handled here.
void adbEventHandler(Connection * connection, adb_eventType event, uint16_t length, uint8_t * data)
{
 
  // In this example Data packets contain one byte and it decides the state of a LED connected to port 13
  // The size of data is predetermined for this application. Android device also uses the same size.
 
  if (event == ADB_CONNECTION_RECEIVE)
  {
     if(LEDState != data[0])
     {
         digitalWrite(13, data[0]);   // Change the state of LED 
         LEDState = data[0];          // Store the State of LED
     }	
  }
 
}
 
void setup()
{
 
  // Note start time
  lastTime = millis();
  
  temp = 0.0f;
  humid = 0.0f;
  light = 0;

   //setup the analog pins as input, probly redundant
  // pinMode(TEMPERATURE_PIN, INPUT);
   pinMode(LIGHT_PIN, INPUT);
 
  // Set Digital pin 13 (Arduino LED) as output
  pinMode(13,OUTPUT);
 
  // Initialise the ADB subsystem.  
  ADB::init();
 
  // Open an ADB stream to the phone's shell. Auto-reconnect. Use any unused port number eg:4568
  connection = ADB::addConnection("tcp:4568", true, adbEventHandler);  
 
}
 
void loop()
{
   //make one initial measurement and send it:
   DHT22_ERROR_t errorCode;
   errorCode = myDHT22.readData();
   
   switch(errorCode)
  {
    case DHT_ERROR_NONE:
     temp =  myDHT22.getTemperatureC();
     humid = myDHT22.getHumidity();
     break;
  }
  light = analogRead(LIGHT_PIN);
  
  //Check if ADC needs to be sampled.
  if ((millis() - lastTime) > 20000)
  {
    ftoa(buf1, temp, 2);
    ftoa(buf2, humid, 2);   
    sprintf(buf3,"%s,%s,%d", buf1, buf2,light);
    
    //Send the ADC value to Android device as two bytes of data.
    connection->writeString(buf3);
    lastTime = millis();
  }
 
  // Poll the ADB subsystem.
  ADB::poll();
}

//Convert double to char (due to currently sprintf in Arduino fails to do so)
char *ftoa(char *a, double f, int precision)
{
  long p[] = {0,10,100,1000,10000,100000,1000000,10000000,100000000};
  
  char *ret = a;
  long heiltal = (long)f;
  itoa(heiltal, a, 10);
  while (*a != '\0') a++;
  *a++ = '.';
  long desimal = abs((long)((f - heiltal) * p[precision]));
  itoa(desimal, a, 10);
  return ret;
}

