//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 01_Test_Load_Cell_Sensor_5kg_and_HX711
//----------------------------------------Including the libraries.
#include "HX711.h"
//---------------------------------------- NOT == Bu baya beni aşar o yüzden hiç anlatmıyorum

//----------------------------------------Defines the connected PIN between HX711 and ESP32.
#define LOADCELL_DOUT_PIN 3 //olmassa bunları sil (1.adım)
#define LOADCELL_SCK_PIN  5 //olmassa bunları sil (1.adım)
//----------------------------------------

// Initialize the HX711 library as LOADCELL_HX711.
HX711 LOADCELL_HX711;

//________________________________________________________________________________VOID SETUP()
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println();
  delay(1000);

  Serial.println("Setup...");
  delay(1000);

  Serial.println();
  Serial.println("LOADCELL_HX711 begin.");
  LOADCELL_HX711.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); //olmassa bunlar D3,D5 olarak Değiştir (2.adım)
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
    
    LOADCELL_HX711.tare();  //--> Reset scale to 0.
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
  // put your main code here, to run repeatedly:

  if (LOADCELL_HX711.is_ready()) {
    // The value 10 in get_units(10) means getting the average value of 10 readings.
    // For more details see in File -> Examples -> HX711 Arduino Library -> HX711_full_example
    long reading = LOADCELL_HX711.get_units(10);
    Serial.print("Sensor reading results : ");
    Serial.println(reading);
  } 
  else {
    Serial.println("HX711 not found.");
  }
  delay(1000);
}
