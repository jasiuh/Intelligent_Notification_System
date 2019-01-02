//Initiate IO
const int bottomL1 = A0;
const int bottomL2 = A1;
const int bottomL3 = A2;
const int sideL1 = A3;
const int sideL2 = A4;
const int sideL3 = A5;
int alarm1 = 0;//this will be '1' if alarm is active
unsigned long time;//initiate timestamps

float bottomCurrentL1 = 0;
float bottomCurrentL2 = 0;
float bottomCurrentL3 = 0;
float sideCurrentL1 = 0;
float sideCurrentL2 = 0;
float sideCurrentL3 = 0;

void setup() {
//Serial communication at 9600 baud rate.
Serial.begin(9600);
//Initiate analog pins as inputs for voltage signals
pinMode(bottomL1, INPUT);
pinMode(bottomL2, INPUT);
pinMode(bottomL3, INPUT);
pinMode(sideL1, INPUT);
pinMode(sideL2, INPUT);
pinMode(sideL3, INPUT);

while(!Serial);//wait until serial port is open and print:
//Print the column names
 Serial.print("Time,");
 Serial.print("BL1,");
 Serial.print("BL2,");
 Serial.print("BL3,");
 Serial.print("SL1,");
 Serial.print("SL2,");
 Serial.print("SL3,");
 Serial.println("ALARM");
}//close setup()

void loop() {
  //Here we read the six currents
  //We divide by 7.5 in order to match the readings with real amperage value
 bottomCurrentL1 = (analogRead(bottomL1) / 7.50);
 bottomCurrentL2 = (analogRead(bottomL2) / 7.50);
 bottomCurrentL3 = (analogRead(bottomL3) / 7.50);
 sideCurrentL1 = (analogRead(sideL1) / 7.50);
 sideCurrentL2 = (analogRead(sideL2) / 7.50);
 sideCurrentL3 = (analogRead(sideL3) / 7.50);
 
//Calculate 12% of the current values. This will be our threshold.
 float twelve_BC_L1 = bottomCurrentL1 * 0.12;
 float twelve_BC_L2 = bottomCurrentL2 * 0.12;
 float twelve_BC_L3 = bottomCurrentL3 * 0.12;
 float twelve_SC_L1 = sideCurrentL1 * 0.12;
 float twelve_SC_L2 = sideCurrentL2 * 0.12;
 float twelve_SC_L3 = sideCurrentL3 * 0.12;

////////////////////////////////////////////////////////////////////////////
//Conditional statements for alarm status.
if (sideCurrentL1 >= 10 && sideCurrentL2 >= 10 && sideCurrentL3 >= 10 && 
    bottomCurrentL1 >= 10 && bottomCurrentL2 >= 10 && bottomCurrentL3 >= 10){
  if (abs(bottomCurrentL1 - bottomCurrentL2) >= twelve_BC_L1 ||
      abs(bottomCurrentL1 - bottomCurrentL2) >= twelve_BC_L2 ||
      abs(bottomCurrentL2 - bottomCurrentL3) >= twelve_BC_L2 ||
      abs(bottomCurrentL2 - bottomCurrentL3) >= twelve_BC_L3 ||
      abs(bottomCurrentL1 - bottomCurrentL3) >= twelve_BC_L1 ||
      abs(bottomCurrentL1 - bottomCurrentL3) >= twelve_BC_L3 ||
      abs(sideCurrentL1 - sideCurrentL2) >= twelve_SC_L1 ||
      abs(sideCurrentL1 - sideCurrentL2) >= twelve_SC_L2 ||
      abs(sideCurrentL2 - sideCurrentL3) >= twelve_SC_L2 ||
      abs(sideCurrentL2 - sideCurrentL3) >= twelve_SC_L3 ||
      abs(sideCurrentL1 - sideCurrentL3) >= twelve_SC_L1 ||
      abs(sideCurrentL1 - sideCurrentL3) >= twelve_SC_L3) 
 { 
     alarm = 1;//engage alarm
 }
 else {
    alarm = 0;
 }
}//close larger if-statement

/////////////////////////////////////////////////////////////////////////////
 //Here we print out the time, three currents, and alarm status to the serial monitor.
 time = millis();
 Serial.print(time); 
 Serial.print(","); 
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
 Serial.print(",");
 Serial.println(alarm);

 delay(60);
}//close void loop
