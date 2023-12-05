#include "deneyap.h" 
#include "HX711.h"

const int LOADCELL_DOUT_PIN = D12; 
const int LOADCELL_SCK_PIN = D13; 

HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN , LOADCELL_SCK_PIN);
}

void loop() {

  if (scale.is_ready()) {
    long okunan = scale.read();
    Serial.print("Hx711 Okunuyor...: ");
    Serial.println(okunan);
  } else {
    Serial.println("Sensör Bulunamadı.");
  }

  delay(1000);
  
}
