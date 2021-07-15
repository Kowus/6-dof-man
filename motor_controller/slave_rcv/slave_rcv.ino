// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#inlcude <Wire.h>

int slaveAddr = 8;
char buff[20];
int setpoint = 0;
int highTol = 2;
int lowTol = -2;
int currdirecTion = 0;
int prevdirecTion = 0;
int enableState = HIGH;

#define dirPin 4
#define stepPin 5

int enablePin = 6;
int del = 5000;
int stt = HIGH;
int posIn = A0;
int st = 0;

void setup() {
  Serial.begin(9600);
  pinMode(enablePin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(posIn, INPUT_PULLUP);

  digitalWrite(enablePin, enableState);
  Wire.begin(SlaveAddr);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent);        // register event
  Serial.begin(115200);
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void receivetEvent()
{
  int count;
  while (Wire.available())
  {
    char c = Wire.read();
    buff[count++] = c;
  }
  setpoint = atoi(buff);
  driveMotor(setpoint);
  count = 0;
}

void driveMotor()
{
  
  int iangle = analogRead(posIn);
  iangle = map(iangle, 0, 1023, 0, 270);

  currdirecTion = digitalRead(dirPin);
  if (prevdirecTion != currdirecTion)
  {
    prevdirecTion = currdirecTion;
  }
  int direcTion = ( (iangle > (setpoint + highTol)) )  ? HIGH : LOW;
  if (iangle <= (setpoint + 3) && iangle >= setpoint - 3)
  {
    enableState = HIGH;
  } else {
    enableState = LOW;
  }
  
  if (!enableState)
  {
    digitalWrite(enablePin, enableState);
    digitalWrite(dirPin, direcTion);
    digitalWrite(stepPin, stt);
    delayMicroseconds(del);
    stt = !stt;
  }
  
  Serial.println(iangle);


}
