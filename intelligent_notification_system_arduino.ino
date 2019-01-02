//Initiate IO
const int bottomL1 = A0;
const int bottomL2 = A1;
const int bottomL3 = A2;
const int sideL1 = A3;
const int sideL2 = A4;
const int sideL3 = A5;

float bottomCurrentL1 = 0;
float bottomCurrentL2 = 0;
float bottomCurrentL3 = 0;
float sideCurrentL1 = 0;
float sideCurrentL2 = 0;
float sideCurrentL3 = 0;


void setup() {
//Serial communication at 9600 baud rate.
Serial.begin(9600);
//Initiate analog pins as inputs for voltage signals.
pinMode(bottomL1, INPUT);
pinMode(bottomL2, INPUT);
pinMode(bottomL3, INPUT);
pinMode(sideL1, INPUT);
pinMode(sideL2, INPUT);
pinMode(sideL3, INPUT);
}

void loop() {
//Here we read the six currents
//We divide by 7.5 in order to match the values with actual amperage
 bottomCurrentL1 = (analogRead(bottomL1) / 7.50);
 bottomCurrentL2 = (analogRead(bottomL2) / 7.50);
 bottomCurrentL3 = (analogRead(bottomL3) / 7.50);
 sideCurrentL1 = (analogRead(bottomL1) / 7.50);
 sideCurrentL2 = (analogRead(bottomL2) / 7.50);
 sideCurrentL3 = (analogRead(bottomL3) / 7.50);
 
//Here we print out the time, three currents, and alarm status to the serial //monitor in array form. The Pi will use this output as an input to the KNN //model.
 Serial.print('[[');
 Serial.print(bottomCurrentL1);
 Serial.print(","); 
 Serial.print(bottomCurrentL2);
 Serial.print(",");  
 Serial.print(bottomCurrentL3);
 Serial.print(",");  
 Serial.print(sideCurrentL1);
 Serial.print(",");  
 Serial.print(sideCurrentL2);
 Serial.print(",");  
 Serial.print(sideCurrentL3);
 Serial.println("]]"); 
 
 delay(5000);
}//close void loop
