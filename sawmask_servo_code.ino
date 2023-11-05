#include <Servo.h>

Servo myservo;  
#define servoPin 3
#define pushButtonPin 2 

int angle = 60;    
int targetAngle = 130;
int angleStep = 3;
unsigned long lastUpdateTime = 0;
unsigned long updateInterval = 20;

int buttonPushed = 0;
int direction = 1;  

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);
  pinMode(pushButtonPin, INPUT_PULLUP);
  Serial.println("Servo Button");
  myservo.write(angle);
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;

    if (digitalRead(pushButtonPin) == LOW) {
      if (!buttonPushed) {
        buttonPushed = 1;
        direction *= -1; 
        targetAngle = (targetAngle == 60) ? 130 : 60; 
      }
    } else {
      buttonPushed = 0;
    }

    angle += angleStep * direction;

    if (angle >= targetAngle) {
      angle = targetAngle;
    } else if (angle <= 60) {
      angle = 60;
    }

    myservo.write(angle);
    Serial.print("Moved to: ");
    Serial.print(angle);
    Serial.println(" degree");
  }
}
