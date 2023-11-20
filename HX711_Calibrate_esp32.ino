//----------------------------------------kütüphaneler Çağırılıyor.
#include "HX711.h"
#include "deneyap.h"
//----------------------------------------

//----------------------------------------Pinler Atanıyor..  
#define LOADCELL_DOUT_PIN D3 //olmazsa bunları sil (1.adım)
#define LOADCELL_SCK_PIN  D5 //olmazsa bunları sil (1.adım)
//----------------------------------------


HX711 LOADCELL_HX711;

//________________________________________________________________________________VOID SETUP()
void setup() {
 

  Serial.begin(115200);
  Serial.println();
  delay(1000);

  Serial.println("Setup...");
  delay(1000);

  Serial.println();
  Serial.println("LOADCELL_HX711 begin.");
  LOADCELL_HX711.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); //olmazsa bunlar D3,D5 olarak Değiştir (2.adım)
  delay(1000);

  Serial.println();
  if (LOADCELL_HX711.is_ready()) {
    Serial.println("Do not place any object or weight on the scale.");
    Serial.println("Please wait...");
    for (byte i = 5; i > 0; i--) {
      Serial.println(i);
      delay(1000);
    }
    
    LOADCELL_HX711.set_scale();    
    Serial.println();
    Serial.println("Set the scales...");
    Serial.println("Please wait...");
    delay(1000);
    
    LOADCELL_HX711.tare();  //--> Ağırlık 0'a ayarlanıyor
    Serial.println();
    Serial.println("Please place objects or weights on the scales.");
    for (byte i = 5; i > 0; i--) {
      Serial.println(i);
      delay(1000);
    }
  } else {
    Serial.println("HX711 not found.");
  }

  Serial.println();
  Serial.println("Setup finish.");
  delay(1000);

  Serial.println();
}
//________________________________________________________________________________

//________________________________________________________________________________VOID LOOP()
void loop() {
  

  if (LOADCELL_HX711.is_ready()) {
    
    long reading = LOADCELL_HX711.get_units(10);
    Serial.print("Sensor reading results : ");
    Serial.println(reading);
  } 
  else {
    Serial.println("HX711 not found.");
  }
  delay(1000);
}
