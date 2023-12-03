//HX711 Arduino Librar by Bogdan Necula 0.7.5 kütüphanesiyle yazılmıştır
#include "deneyap.h"
#include <Arduino.h>
#include "HX711.h"

//pinler ayarlınır
const int LOADCELL_DOUT_PIN = D12;
const int LOADCELL_SCK_PIN = D13;

HX711 scale; //sensör çalışır

void setup() {
  Serial.begin(57600);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Ağırlık Ayarlanmadan Önce:");
  Serial.print("Okunan: \t\t");
  Serial.println(scale.read()); //okumaya başlar

  Serial.print("Ortalama: \t\t");
  Serial.println(scale.read_average(20));  //20 defa okur

  Serial.print("Değer: \t\t");
  Serial.println(scale.get_value(5));  

  Serial.print("Birimleri: \t\t");
  Serial.println(scale.get_units(5), 1);
            
  scale.set_scale(); //faktörü yaz faktör == ölçülen değer / bilinen ağırlık
  scale.tare();

  Serial.println("Ayarlandıktan Sonra:");

  Serial.print("Okunan: \t\t");
  Serial.println(scale.read());                

  Serial.print("Ortalama: \t\t");
  Serial.println(scale.read_average(20));  //20 defa okur

  Serial.print("Değer: \t\t");
  Serial.println(scale.get_value(5)); 

  Serial.print("Birimleri: \t\t");
  Serial.println(scale.get_units(5), 1);       

  Serial.println("Okunanlar:");
}

void loop() {
  Serial.print("1 kere Okunana:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| Ortalama:\t");
  Serial.println(scale.get_units(10), 5);

  delay(5000);
}