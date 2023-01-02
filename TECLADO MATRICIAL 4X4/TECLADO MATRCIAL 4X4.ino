#include <Key.h>
#include <Keypad.h>
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
char key;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {

  key = keypad.getKey(); // obtiene la tecla y se asigna a una variable
 
  if (key){
    Serial.println(key); // comprueba que se presiono algo y lo envia al monitor serial

  }
}
