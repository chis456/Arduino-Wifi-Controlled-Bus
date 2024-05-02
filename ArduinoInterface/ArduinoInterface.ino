#include <Wire.h>

//front motor driver
int AenableA = 7;
int Ain1 = 6;
int Ain2 = 5;

int AenableB = 2;
int Ain3 = 4;
int Ain4 = 3;

//back motor driver
int BenableA = 13;
int Bin1 = 12;
int Bin2 = 11;

int BenableB = 8;
int Bin3 = 10;
int Bin4 = 9;

bool forward = false;
bool backward = false;
bool left = false;
bool right = false;
bool brake = true;


void setup() {
  pinMode(AenableA, OUTPUT);
	pinMode(AenableB, OUTPUT);
	pinMode(Ain1, OUTPUT);
	pinMode(Ain2, OUTPUT);
	pinMode(Ain3, OUTPUT);
	pinMode(Ain4, OUTPUT);

  pinMode(BenableA, OUTPUT);
	pinMode(BenableB, OUTPUT);
	pinMode(Bin1, OUTPUT);
	pinMode(Bin2, OUTPUT);
	pinMode(Bin3, OUTPUT);
	pinMode(Bin4, OUTPUT);

  digitalWrite(Ain1, LOW);
	digitalWrite(Ain2, LOW);
	digitalWrite(Ain3, LOW);
	digitalWrite(Ain4, LOW);
  digitalWrite(Bin1, LOW);
	digitalWrite(Bin2, LOW);
	digitalWrite(Bin3, LOW);
	digitalWrite(Bin4, LOW);

  //master slave connection with NodeMCU ESP8266
  Wire.begin(8);             
  Wire.onReceive(receiveEvent); 
  Wire.onRequest(requestEvent);
  Serial.begin(9600);          
}

void loop() {
  //delay(100);
}

//recieving data from NodeMCU
void receiveEvent(int howMany) {
  char command;
  while (0 <Wire.available()) 
  {
    command = Wire.read();
    Serial.println("command: " + command);
  }

  if(command == 'f')
  {
    brake = false;
    forward = true;
    backward = false;
  }
  else if(command == 'l')
  {
    brake = false;
    left = true;
    right = false;
  }
  else if(command == 'r')
  {
    brake = false;
    left = false;
    right = true;
  }
  else if(command == 'b')
  {
    brake = false;
    forward = false;
    backward = true;
  }
  else if(command == 's')
  {
    brake = true;
    forward = false;
    backward = false;
    left = false;
    right = false;
  }

  //in3 and in4 are right side, in4 is forward
  //in1 and in2 are left side, in1 is forward

  //forward
  if(forward && !left && !right)
  {
    analogWrite(AenableA, 255);
    digitalWrite(Ain1, HIGH);
	  digitalWrite(Ain2, LOW);
    digitalWrite(Ain3, LOW);
    digitalWrite(Ain4, HIGH);

    analogWrite(BenableA, 255);
    digitalWrite(Bin1, HIGH);
	  digitalWrite(Bin2, LOW);
    digitalWrite(Bin3, LOW);
    digitalWrite(Bin4, HIGH);
  }

  //reverse
  else if(backward && !left && !right)
  {
    analogWrite(AenableB, 100);
    digitalWrite(Ain1, LOW);
	  digitalWrite(Ain2, HIGH);
    digitalWrite(Ain3, HIGH);
    digitalWrite(Ain4, LOW);

    analogWrite(BenableB, 100);
    digitalWrite(Bin1, LOW);
	  digitalWrite(Bin2, HIGH);
    digitalWrite(Bin3, HIGH);
    digitalWrite(Bin4, LOW);
  }

  //turn left
  else if(left && !backward)
  {
    analogWrite(AenableA, 255);
    digitalWrite(Ain1, LOW);
	  digitalWrite(Ain2, LOW);
    digitalWrite(Ain3, LOW);
    digitalWrite(Ain4, HIGH);

    analogWrite(BenableA, 255);
    digitalWrite(Bin1, LOW);
	  digitalWrite(Bin2, LOW);
    digitalWrite(Bin3, LOW);
    digitalWrite(Bin4, HIGH);
  }
  //turn left in reverse
  else if(left && backward)
  {
    analogWrite(AenableA, 255);
    digitalWrite(Ain1, LOW);
	  digitalWrite(Ain2, LOW);
    digitalWrite(Ain3, HIGH);
    digitalWrite(Ain4, LOW);

    analogWrite(BenableA, 255);
    digitalWrite(Bin1, LOW);
	  digitalWrite(Bin2, LOW);
    digitalWrite(Bin3, HIGH);
    digitalWrite(Bin4, LOW);
  }

  //turn right
  else if(right && !backward)
  {
    analogWrite(AenableA, 100);
    digitalWrite(Ain1, HIGH);
	  digitalWrite(Ain2, LOW);
    digitalWrite(Ain3, LOW);
    digitalWrite(Ain4, LOW);

    analogWrite(BenableA, 100);
    digitalWrite(Bin1, HIGH);
	  digitalWrite(Bin2, LOW);
    digitalWrite(Bin3, LOW);
    digitalWrite(Bin4, LOW);
  }

  //turn right in reverse
  else if(backward && right)
  {
    analogWrite(AenableA, 100);
    digitalWrite(Ain1, LOW);
	  digitalWrite(Ain2, HIGH);
    digitalWrite(Ain3, LOW);
    digitalWrite(Ain4, LOW);

    analogWrite(BenableA, 100);
    digitalWrite(Bin1, LOW);
	  digitalWrite(Bin2, HIGH);
    digitalWrite(Bin3, LOW);
    digitalWrite(Bin4, LOW);
  }

  //brake
  else if(brake)
  {
    analogWrite(AenableA, 255);
    digitalWrite(Ain1, LOW);
	  digitalWrite(Ain2, LOW);
    digitalWrite(Ain3, LOW);
	  digitalWrite(Ain4, LOW);

    analogWrite(BenableA, 255);
    digitalWrite(Bin1, LOW);
	  digitalWrite(Bin2, LOW);
    digitalWrite(Bin3, LOW);
	  digitalWrite(Bin4, LOW);
  }
  Serial.println();
}