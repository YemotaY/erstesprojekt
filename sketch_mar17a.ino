String codigo = "";

//MOTOR 1
const int M1A = A0;
const int M1B = A1;
//MOTOR 2
const int M2A = A2;
const int M2B = A3;
int iterator = 0;

//velocidad
int velocity = 128;


void setup() {

  Serial.begin(9600);
  //MOTOR 1
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  //MOTOR2
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);

  //Inicia detenido tanto el motor A , como el motor B
  //analogWrite(M1A,0);
  //analogWrite(M1B,0);
  //analogWrite(M2A,0);
  //analogWrite(M2B,0);

  //Testdrive aufruf
  //drive(1);
  steer(0);
  // for(int i = 0; i <= 255;i++){
  //  Serial.print(i);
  //  drive(1, i);
  //  delay(200);
  //}
}

void drive(int direction) {
  if (direction < 0 || !direction > 1 ) {
    Serial.write("Möööp Falsche werte du vollidiot");
    return "Möööp Falsche werte";
  }
  // direction: wenn 0 dann rückwärt wenn 1 dann vorwärts
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


void steer(int direction) {
  if (direction < 0 || !direction > 1) {
    //lilnks ist 1
    //rechts ist 0
    Serial.write("Möööp Falsche werte du vollidiot");
    return "Möööp Falsche werte";
  }
  // direction: wenn 0 dann rückwärt wenn 1 dann vorwärts
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

void loop() {

}
