//1.4.2 dht 11 Adafruit kütüphanesiyle yazılmıştır
#include "deneyap.h"
#include "DHT.h"
#define dhtpin D0 //Pin tanımlanır

DHT dht(dhtpin,DHT11); //Sensör tanımlanır yani (DHT "isim"(sensör pini , sensör modeli);)
void setup() {
  Serial.begin(9600);
  dht.begin(); //Sensörün  Konuşmaşı başlar
}

void loop() {
  float nem = dht.readHumidity(); //Nemi okur ve "nem" değişkenine atar
  float sicaklik = dht.readTemperature(); //Sıcaklığı okur ve "sicaklik" değişkenine atar
  Serial.print("Sıcaklık = "); //--
  Serial.print(sicaklik); //--
  Serial.print("Nem Oranı = "); //--  İki -- yerlerde ise sıcaklığı ve nemi serial monitere yazdırır
  Serial.print(nem); //--
  delay(1500); // dikkat bu sensör en az 1 saniye(1000 ms) bekleme alması gerekmektedir burda 1.5 saniye(1500 ms) bekleme verilmiştir

}