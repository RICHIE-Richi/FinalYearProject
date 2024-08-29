#include <Servo.h>


int THRESHOLD = 550;
#define EMG_PIN 0


#define SERVO1_PIN 3
#define SERVO2_PIN 5
#define SERVO3_PIN 6
#define SERVO4_PIN 9
#define SERVO5_PIN 10


#include <ezButton.h>

int led_pin1 = 2;
int led_pin2 = 4;
int led_pin3 = 7;
int led_pin4 = 11;
//int led_pin5 = A5;

//servo object
Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo servo_4;
Servo servo_5;


int value = 0;


ezButton limitSwitch1(8);  // create ezButton object that attach to pin 7;
ezButton limitSwitch(12);

void setup() {
  Serial.begin(9600);
  limitSwitch1.setDebounceTime(500); // set debounce time to 50 milliseconds
  servo_1.attach(SERVO1_PIN);
  servo_2.attach(SERVO2_PIN);
  servo_3.attach(SERVO3_PIN);
  servo_4.attach(SERVO4_PIN);
  servo_5.attach(SERVO5_PIN);

  pinMode(led_pin1, OUTPUT);
  digitalWrite(led_pin1, LOW);
  pinMode(led_pin2, OUTPUT);
  digitalWrite(led_pin2, LOW);
  pinMode(led_pin3, OUTPUT);
  digitalWrite(led_pin3, LOW);
  pinMode(led_pin4, OUTPUT);
  digitalWrite(led_pin4, LOW);
  //pinMode(led_pin5, OUTPUT);
  //digitalWrite(led_pin5, LOW);
  delay(500);


}

void MySwitch() {
  limitSwitch1.loop(); // MUST call the loop() function first

  if(limitSwitch1.isPressed())
    Serial.println("The limit switch: UNTOUCHED -> TOUCHED");

  if(limitSwitch1.isReleased())
    Serial.println("The limit switch: TOUCHED -> UNTOUCHED");

  int state = limitSwitch1.getState();
  if(state == HIGH){
    Serial.println("The limit switch: UNTOUCHED");
    digitalWrite(led_pin1, LOW);
    digitalWrite(led_pin2, LOW);
    delay(500);
  }
  if(state == LOW){
    Serial.println("The limit switch: TOUCHED");
    digitalWrite(led_pin1, HIGH);
    digitalWrite(led_pin2, HIGH);
    delay(500);
  }
}

void MySwitch1() {
  limitSwitch.loop(); // MUST call the loop() function first

  if(limitSwitch.isPressed())
    Serial.println("The limit switch: UNTOUCHED -> TOUCHED");

  if(limitSwitch.isReleased())
    Serial.println("The limit switch: TOUCHED -> UNTOUCHED");

  int state = limitSwitch.getState();
  if(state == LOW){
    Serial.println("The limit switch: UNTOUCHED");
    digitalWrite(led_pin3, HIGH);
    digitalWrite(led_pin4, HIGH);
    delay(500);
  }
  if(state == HIGH){
    Serial.println("The limit switch: TOUCHED");
    digitalWrite(led_pin3, LOW);
    digitalWrite(led_pin4, LOW);
    delay(500);
  }
}

void sendsensor(){
  int value = analogRead(EMG_PIN);
  Serial.println(EMG_PIN);
  if(value > THRESHOLD){
    servo_1.write(100);
    servo_2.write(100);
    servo_3.write(100);
    servo_4.write(100);
    servo_5.write(100);
    delay(1000);

 }
 if(value <= THRESHOLD){
  servo_1.write(0);
  servo_2.write(0);
  servo_3.write(0);
  servo_4.write(0);
  servo_5.write(0);
 } 

 Serial.println(value);

}

void loop(){
 MySwitch();
 MySwitch1();
 sendsensor(); 
}