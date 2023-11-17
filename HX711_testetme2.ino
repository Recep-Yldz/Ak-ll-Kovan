//#include "deneyap.h" //olmassa "//" sil (1.Adım)
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 3; //olmassa başlarına "//" koy (2.Adım)
const int LOADCELL_SCK_PIN = 5; //olmassa başlarına "//" koy (2.Adım)

HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN , LOADCELL_SCK_PIN); //olmassa Değişkenlerin yerine D3,D5 Değiştir (2.Adım)
}

void loop() {

  if (scale.is_ready()) {
    long reading = scale.read();
    Serial.print("HX711 reading: ");
    Serial.println(reading);
  } else {
    Serial.println("HX711 not found.");
  }

  delay(1000);
  
}
