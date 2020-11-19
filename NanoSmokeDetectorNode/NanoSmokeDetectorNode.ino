//                                              FINAL CODE
// Last Edit: 19/11/2020 13:11
//----------------------------------------------------------------------------------------------------------


#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

int gaslevel;
RF24 radio(6,7);
const byte addressPipe = 'T';
int msg[1];

void setup() {
  pinMode(2, INPUT_PULLUP); //BUTTON
  pinMode(4, OUTPUT); //BUZZER
  pinMode(5, OUTPUT); //LED
  pinMode(A3, INPUT); //MQ-6
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(addressPipe);
}

void loop() {
  if(digitalRead(2) == HIGH)
    {
      gaslevel = analogRead(A3);
      Serial.println(gaslevel);
      if(gaslevel>130)
      {
        msg[0] = 1;
        radio.write(msg, sizeof(msg[1]));
          tone(4, 1000);
          digitalWrite(5, HIGH);
          delay(100);
          noTone(4);
          digitalWrite(5, LOW);
          delay(100);
      }
    }
    else if(digitalRead(2) == LOW)
    {
      digitalWrite(5, HIGH);
      delay(60000);
      digitalWrite(5, LOW);
    }
  }
