//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 03_Load_Cell_Sensor_5kg_Calibration
// In this step, the calibration value will be stored in the ESP32 flash memory.
// The calibration value in this step will be used in the next step.
// Because the calibration values are stored in the ESP32 flash memory,
// in the next step it is enough to load the calibration values stored in the ESP32 flash memory (without having to calibrate again).

//----------------------------------------Including the libraries.
#include "deneyap.h"
#include "HX711.h"
#include <Preferences.h>
//----------------------------------------

//----------------------------------------Defines the connected PIN between HX711 and ESP32.
#define LOADCELL_DOUT_PIN D3
#define LOADCELL_SCK_PIN  D5
//----------------------------------------

/////////////////// ENTER THE WEIGHT OF OBJECTS WHICH WEIGHT IS ALREADY KNOWN FOR THE CALIBRATION PROCESS ///////////////////
// Defines the weight of an object whose weight is known for the calibration process.
// Before the calibration process, prepare an object with a known weight in grams.
// Then enter the weight value into the "weight_of_object_for_calibration" variable below.
// Use objects weighing 100 grams or more for calibration.
// In this project I used an object weighing 181 grams for calibration.

#define weight_of_object_for_calibration 181                                                                                   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Variable to hold sensor reading values.
long sensor_Reading_Results; 

// Float variable to get calibration value. The calibration value is the sensor reading divided by the known weight of the object.
// CALIBRATION_FACTOR = sensor_Reading_Results / weight_of_object_for_calibration
float CALIBRATION_FACTOR;

// Bool variable to display the weighing results after the calibration process is complete.
bool show_Weighing_Results = false;

int weight_In_g;    // Int variable to hold the value of the weighing results in units of grams (g).
float weight_In_oz; // Float variable to hold the value of the weighing results in units of ounce (oz).

// Initialize the HX711 library as LOADCELL_HX711.
HX711 LOADCELL_HX711;

// Initialize the Preferences library as preferences.
Preferences preferences;

//________________________________________________________________________________VOID SETUP()
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println();
  delay(2000);

  Serial.println("Setup...");
  delay(1000);

  preferences.begin("CF", false);
  delay(100);

  Serial.println();
  Serial.println("Do not place any object or weight on the scale.");
  delay(1000);

  Serial.println();
  Serial.println("LOADCELL_HX711 begin.");
  LOADCELL_HX711.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println();
  Serial.println("Setup finish.");
  delay(1000);

  Serial.println();
  Serial.println("Sequence of commands for the calibration process :");
  Serial.println("1. Send the P character to prepare for the calibration process.");
  Serial.println("2. Send the C character to calibration.");
  Serial.println("The above commands must be sequential from 1 to 2.");
  delay(1000);
  Serial.println();
  Serial.println("Please enter/send the character P to prepare for the calibration process.");
}
//________________________________________________________________________________

//________________________________________________________________________________VOID LOOP()
void loop() {
  // put your main code here, to run repeatedly:

  //----------------------------------------Conditions for the calibration process.
  if(Serial.available()) {
    char inChar = (char)Serial.read();  // Accommodates incoming characters from serial communication.
    Serial.println();
    Serial.print("Received characters : ");
    Serial.println(inChar);

    // Conditions to prepare for the calibration process.
    if (inChar == 'P') {
      show_Weighing_Results = false;
      delay(1000);
      if (LOADCELL_HX711.is_ready()) {  
        Serial.println(); 
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
        
        LOADCELL_HX711.tare();
        Serial.println();
        Serial.println("Please place an object whose weight is known on the scale.");
        Serial.flush();
        
        for (byte i = 5; i > 0; i--) {
          Serial.println(i);
          delay(1000);
        }
        
        Serial.println();
        Serial.println("Please enter/send the character C for calibration.");
      } else {
        Serial.println("HX711 not found.");
      }
    }

    // Conditions to start the calibration process.
    if (inChar == 'C') {
      if (LOADCELL_HX711.is_ready()) {
        Serial.println(); 
        Serial.println("Start calibration...");
        Serial.println("Let the object whose weight is known remain on the scale.");
        Serial.println("Please wait...");
        Serial.println(); 
        
        for (byte i = 0; i < 5; i++) {
          sensor_Reading_Results = LOADCELL_HX711.get_units(10);
          Serial.print("Sensor reading results : ");
          Serial.println(sensor_Reading_Results);
          delay(1000);
        }

        // Formula to get CALIBRATION_FACTOR value.
        CALIBRATION_FACTOR = sensor_Reading_Results / weight_of_object_for_calibration; 

        // The calibration value will be stored in the flash memory.
        // So the calibration value can be directly used for the next step.

        Serial.println(); 
        Serial.println("Save calibration values to flash memory.");
        // Saves calibration values to flash memory. Format : putFloat(const char* key, const float_t value).
        preferences.putFloat("CFVal", CALIBRATION_FACTOR); 
        delay(500);

        Serial.println(); 
        Serial.println("Load calibration values from flash memory.");
        float LOAD_CALIBRATION_FACTOR; 
        // Load calibration values stored in flash memory. Format : getFloat(const char* key, const float_t defaultValue).
        LOAD_CALIBRATION_FACTOR = preferences.getFloat("CFVal", 0); 
        delay(500);

        Serial.println(); 
        Serial.println("Set the scale with the CALIBRATION_FACTOR value.");
        LOADCELL_HX711.set_scale(LOAD_CALIBRATION_FACTOR); // Set the scale with the CALIBRATION_FACTOR value.
        delay(500);
        
        Serial.println(); 
        Serial.print("CALIBRATION_FACTOR : ");
        Serial.println(LOAD_CALIBRATION_FACTOR);
        delay(2000);
        
        show_Weighing_Results = true;

        Serial.println();
        Serial.println("Calibration complete.");
        Serial.println();
        Serial.println("If you want to recalibrate, please enter/send the character P.");
        Serial.println();
        Serial.println("The scales are ready to use.");
        Serial.println();
        delay(2000);
      } else {
        Serial.println("HX711 not found.");
      }
    }
  }
  //----------------------------------------

  //----------------------------------------The condition for printing the results of weighing objects on the serial monitor after the calibration process is complete.
  if (show_Weighing_Results == true) {
    if (LOADCELL_HX711.is_ready()) {
      // The value 10 in get_units(10) means getting the average value of 10 readings.
      // For more details see in File -> Examples -> HX711 Arduino Library -> HX711_full_example

      // Get the reading of the object's weight in grams (g).
      weight_In_g = LOADCELL_HX711.get_units(10); 

      // Get the reading of the object's weight in ounce (oz).
      // The ounce is a unit of mass that has several definitions depending on the system of units.
      // As an example :
      // - If you use "International avoirdupois ounce", then 1 ounce = 28.349523125 grams.
      // - If you use "French ounce (once)", then 1 ounce = 30.59 grams.
      // - For more details, you can see here: https://en.wikipedia.org/wiki/Ounce.
      // - In this project, I use "International avoirdupois ounce".
      weight_In_oz = float(weight_In_g) / 28.34952;
      
      Serial.print("Weight : ");
      Serial.print(weight_In_g);
      Serial.print(" g");
      Serial.print(" | ");
      Serial.print(weight_In_oz, 2);
      Serial.println(" oz");
    } else {
      Serial.println("HX711 not found.");
    }
  }
  //----------------------------------------

  delay(1000);
}
//________________________________________________________________________________
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<