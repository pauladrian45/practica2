#include "LowPower.h"
#define led_verde 4
#define sensor 2
#define alarma 9
int length = 15; // el numero de las notas
char notes[] = "ccggaagffeeddc "; 
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 400;

void setup() {
  pinMode(sensor, INPUT_PULLUP);//establecer el switch como entrada
  pinMode(led_verde, OUTPUT);//poner el led como salida
  pinMode(alarma, OUTPUT);//poner la bocina como salida.
  attachInterrupt(0,sistema,FALLING);//Interrupcion para la alarma del sistema
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);//Apaga ciertas funciones del Arduino para bajar el consumo de energia
  Serial.begin(9600);
}
void loop() {
  //si el iman se acerca al reed switch
  detachInterrupt(0);
  //if(FALLING != LOW){
    sonido();//proceso de alarma
    attachInterrupt(0,sistema,FALLING);//Interrupcion para la alarma del sistema
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);//Apaga ciertas funciones del Arduino para bajar el consumo de energia
 // }
}



void sistema(){
  
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
    digitalWrite(alarma, HIGH);
    digitalWrite(led_verde, HIGH);//apaga el led
    delayMicroseconds(tone);
    digitalWrite(alarma, LOW);
    digitalWrite(led_verde, LOW);//enciende el led
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
