//includes 
//#include <SPI.h>
//#include <Adb.h>

#include <Max3421e.h>
#include <Usb.h>
#include <FHB.h>

//constant definition
#define ARRAY_SIZE 12

//recognize accessory
AndroidAccessory acc("Manufacturer","Model","Description",
                  "Version", "URI","Serial"); 

//global variable definition
char hello[ARRAY_SIZE] = {'h','e','l','l','o',' ','w','o','r','l','d','!'}; 

void setup() {
  //set baud rate for serial communication
  Serial.begin(115200);
  delay(500); 
   acc.powerOn();  
}

void loop() {
  Serial.print("hello world primer"); 
if(acc.isConnected()) {
  for (int x = 0; x < ARRAY_SIZE; x++) {
    Serial.print(hello[x]); 
    delay(250); 
  }
  Serial.println(); 
  delay(250); 
}
}

