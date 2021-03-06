//                                              FINAL CODE
// Last Edit: 19/11/2020 13:07
//----------------------------------------------------------------------------------------------------------

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Tone32.h>

//Create Task Function
void Task_Keran1 (void *param);
void Task_Keran2 (void *param);
void Task_LampuDapur (void *param);
void Task_LampuKamarMandi (void *param);
void Task_LampuBelakang (void *param);
void Task_GasDapur (void *param);


char ssid[] = "MYWIFI";
char pass[] = "MYWIFIPASSWORD";
char token[] = "MYTOKEN";


int stateLD = 1, stateLKM = 1, stateLB = 1;
RF24 radio(15, 2);
const byte addressPipe = 'T';
int msg[1];

void setup() {
  disableCore0WDT();
  disableCore1WDT();
  Serial.begin(9600);
  Serial.println("Booting.....");
  
  //Relays
  pinMode(21, OUTPUT); //Keran Kamar Mandi
  pinMode(5, OUTPUT); //Keran Belakang
  pinMode(17, OUTPUT); //Lampu Dapur
  pinMode(16, OUTPUT); //Lampu Belakang
  pinMode(4, OUTPUT); //Lampu Kamar Mandi

  //Lamp Button
  pinMode(3, INPUT_PULLUP); //Dapur
  pinMode(26, INPUT_PULLUP); //Kamar Mandi
  pinMode(25, INPUT_PULLUP); //Lampu Belakang

  //Float Switch
  pinMode(22, INPUT_PULLUP); //Kamar Mandi
  pinMode(32, INPUT_PULLUP); //Belakang
  
  //Create Task
  xTaskCreate(Task_Keran1, "TaskKeran1", 1000, NULL, 1, NULL);
  xTaskCreate(Task_Keran2, "TaskKeran2", 1000, NULL, 1, NULL);
  xTaskCreate(Task_LampuDapur, "TaskLampuDapur", 1000, NULL, 1, NULL);
  xTaskCreate(Task_LampuKamarMandi, "TaskLampuKamarMandi", 1000, NULL, 1, NULL);
  xTaskCreate(Task_LampuBelakang, "TaskLampuBelakang", 1000, NULL, 1, NULL);
  xTaskCreate(Task_GasDapur, "TaskGas", 1000, NULL, 1, NULL);

  Blynk.begin(token, ssid, pass);
  
  radio.begin();
  radio.openReadingPipe(1, addressPipe);
  radio.startListening();
  
  digitalWrite(3, LOW);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
}

void loop() {
  Blynk.run();
}

void Task_Keran1(void *param)
{
    (void) param;
    for(;;)
    {
        if(digitalRead(22) == HIGH) //ON
        {
          digitalWrite(21, HIGH);
        }
        else if(digitalRead(22) == LOW) //OFF
        {
          digitalWrite(21, LOW);
        }
    }
}

void Task_Keran2(void *param)
{
    (void) param;
    for(;;)
    {
        if(digitalRead(32) == HIGH) //ON
        {
          digitalWrite(5, HIGH);
        }
        else if(digitalRead(32) == LOW) //OFF
        {
          digitalWrite(5, LOW);
        }
    }
  
}

void Task_LampuDapur(void *param)
{
    (void) param;
    for(;;)
    {
      Serial.println(digitalRead(3));
      if(digitalRead(3) == LOW && stateLD == 0)
      {
          vTaskDelay(300/portTICK_PERIOD_MS);
          stateLD = 1;
          digitalWrite(17, LOW);
          Blynk.virtualWrite(V0, stateLD);
      }
      else if(digitalRead(3) == LOW && stateLD == 1)
      {
          vTaskDelay(300/portTICK_PERIOD_MS);
          stateLD = 0;
          digitalWrite(17, HIGH);
          Blynk.virtualWrite(V0, stateLD);
      }
    }
}

void Task_LampuKamarMandi(void *param)
{
    (void) param;
    for(;;)
    {
      Serial.println(digitalRead(26));
        if(digitalRead(26) == LOW && stateLKM == 0)
        {
            vTaskDelay(300/portTICK_PERIOD_MS);
            stateLKM = 1;
            digitalWrite(4, LOW);
            Blynk.virtualWrite(V1, stateLKM);
        }
        else if(digitalRead(26) == LOW && stateLKM == 1)
        {
            vTaskDelay(300/portTICK_PERIOD_MS);
            stateLKM = 0;
            digitalWrite(4, HIGH);
            Blynk.virtualWrite(V1, stateLKM);
        }
    }
}

void Task_LampuBelakang(void *param)
{
    (void) param;
    for(;;)
    {
      Serial.println(digitalRead(25));
        if(digitalRead(25) == LOW && stateLB == 0)
        {
            vTaskDelay(300/portTICK_PERIOD_MS);
            stateLB = 1;
            digitalWrite(16, LOW);
            Blynk.virtualWrite(V2, stateLB);
        }
        else if(digitalRead(25) == LOW && stateLB == 1)
        {
            vTaskDelay(300/portTICK_PERIOD_MS);
            stateLB = 0;
            digitalWrite(16, HIGH);
            Blynk.virtualWrite(V2, stateLB);
        }
    }
}

void Task_GasDapur(void *param)
{
  (void) param;
  for(;;)
  {
    radio.read(msg, sizeof(msg[1]));
    if(msg[0] == 1)
    {
      Blynk.notify("GAS DAPUR BOCOR!!!");
    }
  }
}

BLYNK_WRITE(V0) //Lampu Dapur
{
  if(param.asInt() == 1 && stateLD == 0)
  {
    stateLD = 1;
    digitalWrite(17, LOW);
  }
  else if(param.asInt() == 0 && stateLD == 1)
  {
    stateLD = 0;
    digitalWrite(17, HIGH);
  }
}

BLYNK_WRITE(V1) //Lampu Kamar Mandi
{
  if(param.asInt() == 1 && stateLKM == 0)
  {
    stateLKM = 1;
    digitalWrite(4, LOW);
  }
  else if(param.asInt() == 0 && stateLKM == 1)
  {
    stateLKM = 0;
    digitalWrite(4, HIGH);
  }
}

BLYNK_WRITE(V2) //Lampu Belakang
{
  if(param.asInt() == 1 && stateLB == 0)
  {
    stateLB = 1;
    digitalWrite(16, LOW);
  }
  else if(param.asInt() == 0 && stateLB == 1)
  {
    stateLB = 0;
    digitalWrite(16, HIGH);
  }
}
