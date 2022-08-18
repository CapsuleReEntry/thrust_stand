#include "HX711.h"

HX711 scale(A1, A0);                          

float calibration_factor = -9.7;          // калибровка!
float units;
float ounces;

void setup() {
  Serial.begin(9600); 
  scale.set_scale();
  scale.tare();                              //Сбрасываем на 0
  scale.set_scale(calibration_factor);       //Применяем калибровку
}

void loop() { 

  Serial.print("Reading: ");
  
  for(int i = 0;i < 10; i ++) units =+ scale.get_units(), 10;   // усредняем показания считав 10 раз 
  units / 10;                                                   // делим на 10
   
  ounces = units * 0.035274;                                    // переводим унции в граммы              
  Serial.print(ounces);                                          // отправляем в монитор порта
  Serial.print(" grams");  
  Serial.println(); 
}
