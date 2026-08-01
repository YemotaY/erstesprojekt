// MOTOR 1
const int M1A = A0;
const int M1B = A1;

// MOTOR 2
const int M2A = A2;
const int M2B = A3;
int iterator = 0;

// Geschwindigkeit
int velocity = 128;

// Einmalig ausführen beim Initialisieren des Controllers
void setup() {
  // Serielle Verbindung zum PC
  Serial.begin(9600);

  //MOTOR 1 - Deklarierung
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  //MOTOR 2 - Deklarierung
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);

  // Motorkontrollfunktionen
  //drive(1);
  steer(0);
}

// Motor vorwärts/rückwärts
void drive(int direction) {
  // ↓ 0 ist rückwärt 
  // ↑ 1 ist vorwärts
  if (direction < 0 || !direction > 1 ) {
    Serial.write("Möööp Falsche werte du vollidiot");
    return "Möööp Falsche werte";
  }

  if (direction) {
    analogWrite(M1A, 0);
    analogWrite(M1B, velocity);
    analogWrite(M2A, 0);
    analogWrite(M2B, velocity);
  } else {
    analogWrite(M1A, velocity);
    analogWrite(M1B, 0);
    analogWrite(M2A, velocity);
    analogWrite(M2B, 0);
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
void steer(int direction) {
  if (direction < 0 || !direction > 1) {
    // ← link ist 1
    // → rechts ist 0
    Serial.write("Möööp Falsche werte du vollidiot");
    return "Möööp Falsche werte";
  }

  if (direction) {
    analogWrite(M1A, velocity);
    analogWrite(M1B, 0);
    analogWrite(M2A, 0);
    analogWrite(M2B, 0);
  } else {
    analogWrite(M1A, 0);
    analogWrite(M1B, 0);
    analogWrite(M2A, velocity);
    analogWrite(M2B, 0);
  }
}

// Automatikmodu hier im Zyklus
void loop() {

}
