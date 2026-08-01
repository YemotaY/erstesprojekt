// Roboterräder ##################################
// MOTOR 1
const int M1A = A0;
const int M1B = A1;

// MOTOR 2
const int M2A = A2;
const int M2B = A3;

/*
// Hier wird per PWM der Gleichstrom-Getriebemotoren angesteuert
// MOTOR 1
const int M1A = D3;
const int M1B = D5;

// MOTOR 2
const int M2A = D6;
const int M2B = D9;

*/

// Geschwindigkeit
int velocity = 128;
// ###############################################

// Radar #########################################
#include <Servo.h>

Servo servo;

const int SERVO_PIN = 9;    // Servo
const int TRIG_PIN = 7;     // HC-SR04
const int ECHO_PIN = 6;     // HC-SR04
// ###############################################

// Hilfsfunktionen Radar #########################
void servoSetAngle(int targetAngle, int stepDelay = 5) {

    targetAngle = constrain(targetAngle, 0, 180);

    static int currentAngle = 0;

    if (targetAngle > currentAngle) {
        for (int a = currentAngle; a <= targetAngle; a++) {
            servo.write(a);
            delay(stepDelay);
        }
    } else {
        for (int a = currentAngle; a >= targetAngle; a--) {
            servo.write(a);
            delay(stepDelay);
        }
    }

    currentAngle = targetAngle;
}

void servoSearch() {

    // Von 0° nach 180°
    for (int angle = 0; angle <= 180; angle++) {
        servo.write(angle);
        delay(10);
    }

    // Zurück nach 0°
    for (int angle = 180; angle >= 0; angle--) {
        servo.write(angle);
        delay(10);
    }
}

void servoReset() {
    servo.write(0);
}

float getDistanceCM() {

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 30000); // Timeout 30 ms

    if (duration == 0)
        return -1;          // Kein Echo

    return duration * 0.0343 / 2.0;
}

int scanEnvironment() {

    float left, front, right;

    servoSetAngle(160);
    delay(250);
    left = getDistanceCM();

    servoSetAngle(90);
    delay(250);
    front = getDistanceCM();

    servoSetAngle(20);
    delay(250);
    right = getDistanceCM();

    servoSetAngle(90);

    Serial.print("L:");
    Serial.print(left);
    Serial.print(" V:");
    Serial.print(front);
    Serial.print(" R:");
    Serial.println(right);

    if (front > 0)
        return 2;       // Geradeaus

    if (left > right)
        return 1;       // Links

    return 0;           // Rechts
}

// ###############################################

// Hilfsfunktionen Räder #########################
// Motor vorwärts/rückwärts
bool drive(int direction, int velocity) {
  // ↓ 0 ist rückwärt 
  // ↑ 1 ist vorwärts
  if (direction < 0 || direction > 1 ) {
    Serial.println("Möööp Falsche werte du vollidiot");
    return 1;
  }

  if (direction) {
    analogWrite(M1A, 0);
    analogWrite(M1B, velocity);
    analogWrite(M2A, 0);
    analogWrite(M2B, velocity);
    return 0;
  } else {
    analogWrite(M1A, velocity);
    analogWrite(M1B, 0);
    analogWrite(M2A, velocity);
    analogWrite(M2B, 0);
    return 0;
  }
}

// Motor stop
void stop(){
  analogWrite(M1A,0);
  analogWrite(M1B,0);
  analogWrite(M2A,0);
  analogWrite(M2B,0);
}

// Motor links/rechts
bool steer(int direction, int velocity) {
  if (direction < 0 || direction > 1) {
    // ← link ist 1
    // → rechts ist 0
    Serial.println("Möööp Falsche werte du vollidiot");
    return 1;
  }

  if (direction) {
    analogWrite(M1A, velocity);
    analogWrite(M1B, 0);
    analogWrite(M2A, 0);
    analogWrite(M2B, velocity); // Hier noch rückwärts anstatt einfach stoppen
    return 0;
  } else {
    analogWrite(M1A, 0);
    analogWrite(M1B, velocity); // Hier noch rückwärts anstatt einfach stoppen
    analogWrite(M2A, velocity);
    analogWrite(M2B, 0);
    return 0;
  }
}
void testMotorSpeed() {

    Serial.println("Starte Geschwindigkeitstest...");

    // Vorwärts beschleunigen
    for (int speed = 0; speed <= 255; speed += 25) {
        Serial.print("PWM: ");
        Serial.println(speed);

        drive(1, speed);
        delay(2000);
    }

    // Anhalten
    stop();
    delay(1000);

    // Rückwärts beschleunigen
    for (int speed = 0; speed <= 255; speed += 25) {
        Serial.print("PWM: ");
        Serial.println(speed);

        drive(0, speed);
        delay(2000);
    }

    stop();
    Serial.println("Test beendet.");
}
// ###############################################

// MAIN ##########################################

// Einmalig ausführen beim Initialisieren des Controllers
void setup() {
  // Serielle Verbindung zum PC
  Serial.begin(9600);
  
  //MOTOR 1 - Deklarierung
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  // MOTOR 2 - Deklarierung
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  
  // Radar
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  servo.attach(SERVO_PIN);
  servo.write(90);            // Radar nach vorne

  // Motorkontrollfunktionen
  //if(!drive(1,velocity)){Serial.write("Konnte nicht fahren!")};
  if(!steer(0,velocity)){Serial.println("Konnte nicht fahren!");};
  
}

// Automatikmodu hier im Zyklus
void loop() {
    /*
    int decision = scanEnvironment();

    switch (decision) {

        case 2:     // Frei
            drive(1);
            break;

        case 1:     // Links
            stop();
            delay(100);
            steer(1);
            delay(400);
            stop();
            break;

        case 0:     // Rechts
            stop();
            delay(100);
            steer(0);
            delay(400);
            stop();
            break;
    }

    delay(100);
    */
}
// ###############################################