//Line Sensors
#define rightSensor 14
#define midSensor 15
#define leftSensor 16

 //HBridgeL          //dont use these unless with an hbridge
#define LAnalog 10
#define LIn1 7
#define LIn2 8

// HBridgeR     //dont use these unless with an hbridge
#define RAnalog 9
#define RIn3 5
#define RIn4 6

//LEDs
#define ledRed 12 
#define ledGreen 3
#define ledBlue 4


//Sensor Variables
int vLeftSensor;
int vRightSensor;
int vMidSensor;

// Left Motor
int L1;    //defines motion as forward
int L2;
int maxSpeedL = 252;     //adjust the speed of the wheels to match eatch other
int midSpeedL;
int speedL;
int straightL = 93;

// Right Motor
int R1;   //defines motion as forward
int R2;
int maxSpeedR = 255;  //adjust the speed of the wheels to match each other
int midSpeedR;
int speedR;
int straightR = 100;

int motorState1= HIGH;
int motorState0 = LOW;

//Time Variables
int currentMillis;
int previousMillis = 0;
int delayTime = 25;

//Zeroing Variables
int nSamples = 100;
int zeroM = 0;
int zeroL = 0;
int zeroR = 0;

//PID Variables
float p = -.03;
float i;
float d; 

//Error Variables
int pErrorL = 0;
int pErrorR = 0;
int pErrorMid = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(rightSensor, INPUT);
pinMode(midSensor, INPUT);
pinMode(leftSensor, INPUT);
pinMode (ledRed, OUTPUT);
pinMode (ledGreen, OUTPUT);
pinMode (ledBlue, OUTPUT);
// Left Motor
  pinMode(LAnalog, OUTPUT);
  pinMode(LIn1, OUTPUT);
  pinMode(LIn2, OUTPUT);

  // Right Motor
  pinMode(RAnalog, OUTPUT);
  pinMode(RIn3, OUTPUT);
  pinMode(RIn4, OUTPUT);
Serial.begin(9600);

// zero
  for (int k = 0; k < nSamples; k++)
  {
    zeroM += analogRead(midSensor);
    zeroL += analogRead(leftSensor);
    zeroR += analogRead(rightSensor);
    
    delay(7);
  }
  zeroM /= nSamples;
  zeroL /= nSamples;
  zeroR /= nSamples;
}



void loop() {
  
  // put your main code here, to run repeatedly:
  
  currentMillis = millis();  //update time

  if (currentMillis - delayTime >= previousMillis){
    previousMillis = currentMillis;      //update sensor values after delayTime
  
  vRightSensor= analogRead(rightSensor);
  vMidSensor= analogRead(midSensor);
  vLeftSensor = analogRead(leftSensor);
  }

  if (abs(pErrorL) > 300 && abs(pErrorR) > 300){
    motorState1 = LOW;
  }



  pErrorL = zeroL - vLeftSensor;
  pErrorR = zeroR - vRightSensor;

  speedL = straightL - (p*pErrorL);
  speedR = straightR - (p*pErrorR);
  
  //analogWrite to motors depending on sensor values
 // Left Motor
  //analogWrite(LAnalog, speedL);      //93 for now
 // digitalWrite(LIn1, motorState1);   //May need to adjust the high low depending on configuration
  //digitalWrite(LIn2, motorState0);

  // Right Motor
  //analogWrite(RAnalog, speedR);   //100 for now
  //digitalWrite(RIn3, motorState1);   //May need to adjust the high low depending on configuration
  //digitalWrite(RIn4, motorState0);

  if((speedL+7) > speedR){
    digitalWrite(ledBlue, HIGH);
  }

  if((speedL+7) < speedR){
    digitalWrite(ledRed, HIGH);
  }
  if((speedL+7 == speedR){
    digitalWrite(ledGreen, HIGH);
  }
}