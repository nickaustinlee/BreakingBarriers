//includes would be placed here

//constant definition
#define ARRAY_SIZE 12

//global variable definition
char hello[ARRAY_SIZE] = {'h','e','l','l','o',' ','w','o','r','l','d','!'}; 

void setup() {
  //set baud rate for serial communication
  Serial.begin(115200); 
}

void loop() {
  //print characters from array to serial monitor
  for(int x = 0; x< ARRAY_SIZE; x++) {
    Serial.print(hello[x]); 
    delay(250); 
  }
  
  Serial.println(); 
  delay(250); 
} 

