
/*
serialcomm.ino
Binary file dimensions: 4.294 bytes 
Max file dimensions: 32.256 bytes (Arduino Uno, Due, Nano)



Author: Riccardo Rossi 
Date:   22/12/2018
Project: Orvieto Scienza 2018 - Radiazioni ionizzanti
License: Free software | GNU GPL


Description:
  Lo script riceve i dati in arrivo dal contatore geiger su un pin analogico e li invia tramite seriale USB ad un programma python ricevente.
  Riceve dati dallo stesso programma per controllare led di stato o avviare procedure di recovery.
  La comunicazione seriale avviene tramite numeri interi per ragioni di velocità Tx/Rx.
  Il tempo impiegato dall'invio di un codice da script Python e l'effettiva esecuzione da Arduino è di c.ca 1.5 S.
  Il tempo impiegato dall'invio di un codice da questo script e l'effetiva ricezione da script Python è trascurabile.
  Il riavvio dello script Python, del Raspberry o la disconnessione e riconnessione del cavo seriale, causano un soft-reboot dell'Arduino.
  Un hard-reboot dell'Arduino può causare errori nella lettura della porta seriale nello script Python.  
*/


/*                      ---{LICENSE}---
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.

*/






#include <SPI.h>


int stateLed = 6;
int errLed = 12;
int actLed = 11;
int connLed = 10;
int disconnLed = 9;
int geiger = 2;
int reset=4;
int act=0;
int stat=1;
int brightness = 0;   
int fadeAmount = 5;


void stateFade(){
  if (stat==2) {
  analogWrite(stateLed, brightness);    
  brightness = brightness + fadeAmount;
 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }        
  delay(30);         
  }  }

void allOff() {
    digitalWrite(stateLed, LOW);
  delay(300);
  
  digitalWrite(errLed, LOW);
  delay(300);
  digitalWrite(actLed, LOW);
  delay(300);
  digitalWrite(connLed, LOW);
  delay(300);
  digitalWrite(disconnLed, LOW);
  delay(200);
}

void actBlink() {
 
 digitalWrite(actLed, HIGH);
 delay(500);
 digitalWrite(actLed, LOW);
  
}

void error() {
  
  Serial.println(33);
  
  while(1){
    digitalWrite(errLed, HIGH);
    delay(800);
    digitalWrite(errLed, LOW);
    delay(800);  
    Serial.println(33);
} }

void ledTest() {
  
  digitalWrite(stateLed, HIGH);
  delay(300);
  digitalWrite(stateLed, LOW);
  
  digitalWrite(errLed, HIGH);
  delay(300);
  digitalWrite(errLed, LOW);
  
  digitalWrite(actLed, HIGH);
  delay(300);
  digitalWrite(actLed, LOW);
  
  digitalWrite(connLed, HIGH);
  delay(300);
  digitalWrite(connLed, LOW);
  
  digitalWrite(disconnLed, HIGH);
  delay(300);
  digitalWrite(disconnLed, LOW);

  digitalWrite(stateLed, HIGH);
  delay(200);
  digitalWrite(stateLed, LOW);
  delay(500);
  digitalWrite(stateLed, HIGH);

}

void tube_impulse() {  
  Serial.println(1);
  actBlink();

}


///////////////////////////////////////////////////////////////////////


void setup(){
  delay(200); 
  pinMode(reset, OUTPUT); 
  digitalWrite(reset, HIGH);

  Serial.begin(115200);
  
  pinMode(stateLed, OUTPUT);
  pinMode(errLed, OUTPUT);
  pinMode(actLed, OUTPUT);
  pinMode(connLed, OUTPUT);
  pinMode(disconnLed, OUTPUT);
  pinMode(geiger, INPUT);
  pinMode(reset, OUTPUT);
  ledTest();
  
  
  digitalWrite(reset, HIGH);
  digitalWrite(geiger, LOW);
  
  
  while (!Serial);
  Serial.println(121);
  
  attachInterrupt(0, tube_impulse, FALLING); //START
  
  allOff();
  digitalWrite(stateLed, HIGH);
}

///////////////////////////////////////////////////////////////////////

void loop(){
  if(Serial.available()) {
   
    int msg = Serial.parseInt();
    Serial.println(121);
    switch (msg) {
    case 2:
      digitalWrite(stateLed, HIGH);
      stat=1;
      break;
    case 3:
      digitalWrite(stateLed, LOW);
      stat=0;
      break;
    case 4:
      digitalWrite(errLed, HIGH);
      break;
    case 5:
      digitalWrite(errLed, LOW);
      break;
    case 6:
      digitalWrite(actLed, HIGH);
      break;
    case 7:
      digitalWrite(actLed, LOW);
      break;
    case 8:
      digitalWrite(connLed, HIGH);
      break;
    case 9:
      digitalWrite(connLed, LOW);
      break;
    case 10:
      digitalWrite(disconnLed, HIGH);
      break;
    case 11:
      digitalWrite(disconnLed, LOW);
      break;
    case 12:
      stat=2;
      break;
    case 107:              //state check
      Serial.println(121);
      break;
    
    case 82:              //aduino reset
     Serial.println(82);
     digitalWrite(reset, LOW);
     break;    
     
    case 33:
      Serial.println(33);
      allOff();
      error();
      break;
      
    case 100:             //simulate act
      Serial.println(1);
      actBlink();
      break;
      
  }
 
 }
 stateFade();
}


