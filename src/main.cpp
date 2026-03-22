#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

BluetoothSerial SerialBT;
// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// MOTOR PINS
#define motor1pin1 27
#define motor1pin2 26
#define motor2pin1 25
#define motor2pin2 33
#define enableA 14
#define enableB 32
#define ALERT_LED 2
#define TRIG_LEFT 5
#define ECHO_LEFT 18
#define TRIG_RIGHT 17
#define ECHO_RIGHT 16
#define PWM_FREQ 1000
#define PWM_RESOLUTION 8
#define PWM_CH_A 0
#define PWM_CH_B 1
char command = 'S';
float leftDistance = 0;
float rightDistance = 0;
float avgDistance = 0;
String potholeStatus = "NORMAL";

float readUltrasonic(int trigPin, int echoPin)
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000); 
    float distance = duration * 0.034 / 2;

    if (distance == 0) distance = 400; 

    return distance;
}

void stopMotors()
{
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);
}

void moveForward()
{
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
}

void moveBackward()
{
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
}

void turnLeft()
{
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
}

void turnRight()
{
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
}

void detectPothole()
{
    avgDistance = (leftDistance + rightDistance) / 2;

if (avgDistance <= 3)
{
    potholeStatus = "NORMAL";
    digitalWrite(ALERT_LED, LOW);
}
else if (avgDistance <= 6) 
{
    potholeStatus = "SMALL PIT";
    digitalWrite(ALERT_LED, LOW);
}
else 
{
    potholeStatus = "LARGE PIT";
    digitalWrite(ALERT_LED, HIGH);
}
}

void updateDisplay()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    display.setCursor(0, 0);
    display.print("Left: ");
    display.print(leftDistance);

    display.setCursor(0, 10);
    display.print("Right: ");
    display.print(rightDistance);

    display.setCursor(0, 20);
    display.print("Avg: ");
    display.print(avgDistance);

    display.setCursor(0, 35);
    display.print("Status:");
    display.setCursor(0, 45);
    display.print(potholeStatus);

    display.display();
}

void setup()
{
    Serial.begin(460800);
    SerialBT.begin("ESP32_ROBOT");
    pinMode(motor1pin1, OUTPUT);
    pinMode(motor1pin2, OUTPUT);
    pinMode(motor2pin1, OUTPUT);
    pinMode(motor2pin2, OUTPUT);
    pinMode(enableA, OUTPUT);
    pinMode(enableB, OUTPUT);
    pinMode(ALERT_LED, OUTPUT);
    pinMode(TRIG_LEFT, OUTPUT);
    pinMode(ECHO_LEFT, INPUT);
    pinMode(TRIG_RIGHT, OUTPUT);
    pinMode(ECHO_RIGHT, INPUT);
    ledcSetup(PWM_CH_A, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(PWM_CH_B, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(enableA, PWM_CH_A);
    ledcAttachPin(enableB, PWM_CH_B);
    ledcWrite(PWM_CH_A, 200);
    ledcWrite(PWM_CH_B, 200);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("OLED Failed");
        while (true);
    }

    display.clearDisplay();
}

void loop()
{
    if (SerialBT.available())
    {
        command = SerialBT.read();
        Serial.println(command);
    }

    leftDistance = readUltrasonic(TRIG_LEFT, ECHO_LEFT);
    rightDistance = readUltrasonic(TRIG_RIGHT, ECHO_RIGHT);
    detectPothole();

    if (command == 'F')
    {
        if (potholeStatus == "LARGE PIT")
        {
            stopMotors();
        }
        else
        {
            moveForward();
        }
    }
    else if (command == 'B')
    {
        moveBackward();
    }
    else if (command == 'L')
    {
        turnLeft();
    }
    else if (command == 'R')
    {
        turnRight();
    }
    else
    {
        stopMotors();
    }

    Serial.print("L: ");
    Serial.print(leftDistance);
    Serial.print(" | R: ");
    Serial.print(rightDistance);
    Serial.print(" | Status: ");
    Serial.println(potholeStatus);
    updateDisplay();
}