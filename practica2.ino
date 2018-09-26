#include "LowPower.h"
#define led_verde 4
#define led_rojo 3
#define sensor 2
#define alarma 9
int length = 15; // el numero de las notas
char notes[] = "ccggaagffeeddc "; 
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

void setup() {
  pinMode(sensor, INPUT_PULLUP);//establecer el switch como entrada
  pinMode(led_verde, OUTPUT);//poner el led como salida
  pinMode(led_rojo, OUTPUT);//poner el led como salida
  pinMode(alarma, OUTPUT);//poner la bocina como salida.
  Serial.begin(9600);

}
void loop() {
  //si el iman se acerca al reed switch
  if(digitalRead(sensor)==LOW){
          digitalWrite(led_rojo,LOW);//apaga el red rojo
          sonido();//suena la alarma
        }else {
          //si el iman esta lejos del reed switch
          attachInterrupt(0,sensor,FALLING);//Interrupcion para bajar el consumo de energia
          LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);//Apaga ciertas funciones del Arduino para bajar el consumo de energia
          detachInterrupt(1);
          digitalWrite(led_verde,LOW);//apaga el led verde
          digitalWrite(led_rojo, HIGH);//prende el led rojo 
    }

}

void sonido(){
  //metodo para hacer sonar la bocina con una melodia
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); 
    } else {
      playNote(notes[i], beats[i] * tempo);
    }

    // pausa entre notas
    delay(tempo / 2); 
  }
}

void playTone(int tone, int duration) {
  //metodo para calcular los tonos de la melodia de la bocina
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(led_verde, HIGH);//apaga el led
    digitalWrite(alarma, HIGH);
    delayMicroseconds(tone);
    digitalWrite(led_verde, LOW);//enciende el led
    digitalWrite(alarma, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  //metodo para la secuencia de las notas de la melodia
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // toca el tono correspondiente al nombre de la nota
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
