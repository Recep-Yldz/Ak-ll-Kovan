/*
 * Complete project details at https://RandomNerdTutorials.com/esp32-load-cell-hx711/
 *
 * HX711 library for Arduino - example file
 * https://github.com/bogde/HX711
 *
 * MIT License
 * (c) 2018 Bogdan Necula
 *
**/
//---------------------------------- Burda Kütüphaneleri çağıyor
//include "deneyap.h" //olmaşşa "//" ları sil (1.adım)
#include "HX711.h"
//----------------------------------------


//---------------------------------------------Bura Pinleri ayarlıyor
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 3; //Olmaşşa "//" yaz başlarına (2.adım)
const int LOADCELL_SCK_PIN = 5; //Olmaşşa "//" yaz başlarına (2.adım)
//------------------------------------------------------

HX711 scale;

void setup() {
  Serial.begin(115200); //Konuşmayı başlatıyor
  scale.begin(LOADCELL_DOUT_PIN,LOADCELL_SCK_PIN); //Olmaşşa D3,D5 olarak değiştir (2.adım)
  scale.set_scale(0); // Bunu faktör=ölçülen değer/sabit olan değer ile bul ve buraya yaz Ve Burda o tartıyı ayarlıyor
  scale.tare();  
}

void loop() {
  Serial.print("Weight:");
  
  Serial.println(scale.get_units(10), 1); //Burda ağırlığı yazıyor formüllenmiş halini eğer hala ağırlık doğru değilse tekrardan test et ve formülü uygula

  scale.power_down(); //enerjiyi sensöre azaltıyor
  delay(1000);
  scale.power_up(); //enerjiyi sensöre tekrardan veriyor 
}
