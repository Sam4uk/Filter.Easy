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

// #define USE_SQURE
#define USE_SIN

#define ADD_NOICE
#define ADD_SPLASH

#define AMPLITUDE (3.)
#define NOICE (10.)
#define SPLASH (20)
#define SPLASH_INTES (30)

ArithmeticMean<float> Mean;
CurrentAverage<float> Average;

MedianFilter<float> Med;

void setup() {
  Serial3.begin(115200);

  Mean.setRenge(10);

  Average.setInterval(60);
  Average.setCoefficient(0.5);
}

long //
    loops{};

float //
    Clear,
    clearSin,     ///<
    clearSqure,   ///<
    noice,        ///<
    splash,       ///<
    derty_signal; ///<

void loop() {
  Clear = clearSin = AMPLITUDE * sin(radians(loops));

  clearSqure = AMPLITUDE * (sin(radians(loops)) > 0 ? 1 : -1);
  noice = random(-NOICE, NOICE) / NOICE;
  splash = (random(SPLASH_INTES) ? 0 : random(-SPLASH, SPLASH));
  derty_signal =
#if defined(USE_SQURE)
      clearSqure
#endif
#if defined(USE_SIN)
          clearSin
#endif


#if defined(ADD_NOICE)
      + noice
#endif
#if defined(ADD_SPLASH)
      + splash
#endif
      ;
  // Serial3.print(Clear);
  // Serial3.print(' ');
  Serial3.print(derty_signal);
  Serial3.print(' ');
  //====================================================================//
    // Serial3.print(Mean(derty_signal));
     Serial3.print(' ');
    // Serial3.print(Mean2(derty_signal));

  Serial3.print(Average(derty_signal));
  // Serial3.print(Med(derty_signal));
  //====================================================================//
  Serial3.print(' ');
//   Serial3.print(SPLASH + 5);
//   Serial3.print(' ');
//   Serial3.print(-SPLASH - 5);
  Serial3.println();
  delay(10);
  loops += 1;
}
#if defined(USE_SQURE) and defined(USE_SIN)
#error Оберіть один
#endif
#if !(defined(USE_SQURE) or defined(USE_SIN))
#error Оберіть один
#endif
