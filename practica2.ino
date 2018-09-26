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
          digitalWrite(led_verde, HIGH);//enciende el led
          sonido();//suena la alarma
        }else {
          //si el iman esta lejos del reed switch
          //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);//entrar al modo sleep
          digitalWrite(led_verde,LOW);
          digitalWrite(led_rojo, HIGH);
          analogWrite(alarma,LOW);
          
    }

}

void sonido(){
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
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(alarma, HIGH);
    delayMicroseconds(tone);
    digitalWrite(alarma, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // toca el tono correspondiente al nombre de la nota
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
