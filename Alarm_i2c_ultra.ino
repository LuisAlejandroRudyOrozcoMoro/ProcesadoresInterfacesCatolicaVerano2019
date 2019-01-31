#include <NewPing.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Select which PWM-capable pins are to be used.
#define BLUE_PIN  9

#define TRIGGER_PIN  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 5 // Maximum distance we want to ping for (in centimeters).

//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
boolean triggered = false;
long duration;
int distance;

#define ALARM 3
float sinVal;
int toneVal;

void setup() {
  lcd.begin(16, 2); //Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light

  //set pinModes for RGB strip
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(ALARM, OUTPUT);
  digitalWrite(ALARM,LOW);
  

  //reset lights
  analogWrite(BLUE_PIN, 0);
  lcd.setCursor(0, 0);
  lcd.print("INICIANDO");

  delay(1000);
  Serial.begin(9600);
  lcd.clear();

}

void loop() {
  
  if (triggered == true) {
    alarm();
  }
  else {
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ECHO_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.println(distance);
    lcd.setCursor(0, 0);
    lcd.print("Sin accdts hace");
    lcd.setCursor(0, 1);
    lcd.print("SEGS: ");
    lcd.print(millis()/1000);
    delay(500);
    if (distance > 4 && distance < 10) {
      triggered = true;
    }
  }
}

void alarm() {
  for (int i = 0; i <= 255; i += 10)
  {
    analogWrite(BLUE_PIN, i);
    delay(10);
  }
  for (int i = 0; i >= 0 ; i -= 10)
  {
    analogWrite(BLUE_PIN, i);
    delay(10);
  }
  digitalWrite(ALARM, HIGH);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("INTRUSION A LOS ");
  delay(500);
  lcd.backlight();
}
