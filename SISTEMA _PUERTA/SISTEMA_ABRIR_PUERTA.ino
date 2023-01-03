#include <Key.h>
#include <Keypad.h>
#include <ESP32Servo.h>
const uint8_t ROWS = 4; // indicamos la la cantidad de filas
const uint8_t COLS = 4; // indicamos la la cantidad de filas
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// pines correspondientes a las filas
byte colPins[COLS] = { 27, 14, 12, 13 };
// pines correspondientes a las columnas
byte rowPins[ROWS] = { 32, 33, 25, 26 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // CREAMOS EL OBJETO KEYPAD
char pass [7] ="ABCD45"; // Variable de tipo caracter para almacenar la contraseña
char ingresaPass[7];
int indice = 0; // esta variable ayuda a que se vaya guiando que letra es
int redLedPin = 15; // pin del led rojo 
int greenLedPin = 2;// pin del led verde
int servoPin = 5;// pin del servo
int buzzPin = 4;
Servo servo_1;// inicializamos el servo


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  servo_1.attach(servoPin, 500, 2500);// 
  servo_1.write(0);
  delay(1500);
}

void loop() {

char key = keypad.getKey(); // obtiena la tecla y la asigna a una variable

  if (key){
    ingresaPass[indice] = key; // almacena lo que se ingresa en el arreglo de pass
    indice++; //aumenta los caracteres a almacenar
    Serial.println(key); // envia al monitor serial la letra enviada
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
  }

  if (indice == 6){ // cuando se ingresen 6 o mas caracteres, entonces:
    if (strcmp(pass, ingresaPass) == 0){
      Serial.println("Acceso permitido");// Muestra la confirmacion
      digitalWrite(greenLedPin, HIGH);// enciende el led verde
      digitalWrite(buzzPin, HIGH);// Activa el buzzer
      delay(500);
      digitalWrite(buzzPin, LOW);  
      servo_1.write(179);// Mueve el motor para abrir la puerta
      delay(2500);// se espera 2.5segundos
      servo_1.write(0);// regresa a la posicion inicial
      digitalWrite(greenLedPin, LOW);// apaga el led verde 
      delay(1500);// espera 1.5 seg
    }
    else{
      Serial.println("Acceso denegado");
      digitalWrite(redLedPin, HIGH);
      digitalWrite(buzzPin, HIGH);
      delay(150);
      digitalWrite(buzzPin, LOW);
      delay(150);
      digitalWrite(buzzPin, HIGH);
      delay(150);
      digitalWrite(buzzPin, LOW);
    }
    indice = 0;
  }
}
