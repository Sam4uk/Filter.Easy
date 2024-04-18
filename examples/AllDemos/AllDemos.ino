/**
 * @file AllDemos.ino
 * @author Sam4uk (Sam4uk@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-04-18
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <Filter.Easy.hpp>

ArithmeticMean<float> Mean;
CurrentAverage<float> Average;
MedianFilter<float> Med;

void setup() {
  Serial.begin(115200);
  Mean.setRenge(3);
  Average.setInterval(60);
  Average.setCoefficient(0.5);
}
long degree = 0;
void loop() {
  degree += 5;
  int valNoise = (float)sin(radians(degree)) * 100

                 + (random(5) == 0 ? 1 : 0) * (random(0, 2) ? -1 : 1) * 20;
  Serial.print(valNoise);
  Serial.print(',');
  // Serial.print(Mean(valNoise));
  // Serial.print(',');
  // Serial.print(Average(valNoise));
  // Serial.print(',');
  Serial.print(Med(valNoise));
  Serial.print(",120,-120");
  Serial.println();
  delay(50);
}