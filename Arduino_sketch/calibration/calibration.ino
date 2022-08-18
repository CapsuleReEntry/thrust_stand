//код для калибровки
//код для калибровки
#include "HX711.h"

HX711 scale(A1, A0); // DT, CLK

float Calibration_Factor_Of_Load_cell = -3.7; // этот калибровочный коэффициент настраивается в соответствии с тензодатчиком
float U;
float O;

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.set_scale();
  scale.tare(); //Сбросьте масштаб до 0
  long zero_factor = scale.read_average(); //Получаем базовое чтение
  Serial.print("Zero factor: "); //Это можно использовать, чтобы устранить необходимость тарирования шкалы. Полезно в проектах постоянного масштаба.
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(Calibration_Factor_Of_Load_cell); //Отрегулируйте этот калибровочный коэффициент
  Serial.print("Reading: ");
  U = scale.get_units();
  if (U < 0)
  {
    U = 0.00;
  }
  O = U * 0.035274;
  Serial.print(O);
  Serial.print(" grams");
  Serial.print(" Calibration_Factor_Of_Load_cell: ");
  Serial.print(Calibration_Factor_Of_Load_cell);
  Serial.println();

  if (Serial.available())
  {
    char temp = Serial.read();
    if (temp == '+' || temp == 'a')
      Calibration_Factor_Of_Load_cell += 1;
    else if (temp == '-' || temp == 'z')
      Calibration_Factor_Of_Load_cell -= 1;
  }
}
