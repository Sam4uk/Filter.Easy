/**
 * @file Filter.Easy.hpp
 * @author Sam4uk (Sam4uk@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-04-18
 *
 * @copyright Copyright (c) 2024
 *
 */
#if !defined(FILTER_EASY_HPP)
#define FILTER_EASY_HPP

#include <Arduino.h>

/**
 * @brief
 *
 * @tparam T
 */
template <class T> class VirtualFilter {
public:
  virtual T operator()(T value) = 0;
};

/**
 * @brief
 *
 * @tparam T
 */
template <class T> class ArithmeticMean : public VirtualFilter<T> {
public:
  /**
   * @brief Set the Renge object
   *
   * @param renge
   */
  void setRenge(unsigned renge) {
    _range = renge;
    return;
  };

  /**
   * @brief
   *
   * @param value
   * @return T
   */
  T operator()(T value) override final {
    acum += value;
    ++count;
    if (count >= _range) {
      _avarenge = acum / count;
      count = 0;
      acum = 0;
    }
    return _avarenge;
  };

private:
  unsigned       //
      _range{1}, ///<
      count{};   ///<

  T                //
      _avarenge{}, ///<
      acum{};      ///<
};
/**
 * @brief
 *
 * @tparam T
 */
template <class T> class CurrentAverage : public VirtualFilter<T> {
public:
  /**
   * @brief Set the Interval object
   *
   * @param time_ms
   */
  void setInterval(long time_ms) {
    _time_step = time_ms;
    return;
  };

  /**
   * @brief Set the Coefficient object
   *
   * @param coefficient
   */
  void setCoefficient(float coefficient) {
    _coefficient = coefficient;
    return;
  }
  /**
   * @brief
   *
   * @param value
   * @return T
   */
  T operator()(T value) override final {
    if (millis() - _filter_timer > _time_step) {
      _filter_timer = millis();
      _value = value * _coefficient + _value * (1 - _coefficient);
    }
    return _value;
  }

private:
  unsigned long        //
      _filter_timer{}, ///<
      _time_step{};    ///<

  T                     //
      _value{},         ///<
      _coefficient{1.}; ///<
};

/**
 * @brief
 *
 * @tparam T
 */
template <class T> class MedianFilter : public VirtualFilter<T> {
public:
  /**
   * @brief
   *
   * @param value
   * @return T
   */
  T operator()(T value) override final {
    _values[_index++] = value;
    if (_index >= _3_)
      _index = 0;
    T middle;
    if ((_values[_a_] <= _values[_b_]) and (_values[_a_] <= _values[_c_]))
      middle = (_values[_b_] <= _values[_c_]) ? _values[_b_] : _values[_c_];
    else if ((_values[_b_] <= _values[_a_]) and (_values[_b_] <= _values[_c_]))
      middle = (_values[_a_] <= _values[_c_]) ? _values[_a_] : _values[_c_];
    else
      middle = (_values[_a_] <= _values[_b_]) ? _values[_a_] : _values[_b_];
    return middle;
  };

private:
  enum { _a_ = 0, _b_, _c_, _3_ }; ///<

  unsigned      //
      _index{}; ///<

  T                   //
      _values[_3_]{}; ///<
};

// develop section
#if 0
template <class T> class A_B_Filter : public VirtualFilter<T> {
public:
  void setParameters(float delta, float sigma_process, float sigma_noise) {
    dt = delta;
    float lambda = (float)sigma_process * dt * dt / sigma_noise;
    float r = (4.0 + lambda - sqrt(8.0 * lambda + lambda * lambda)) / 4.0;
    a = 1.0 - r * r;
    b = 2.0 * (2.0 - a) - 4.0 * sqrt(1.0 - a);
    return;
  };
  T operator()(T value) override final {
    xm = value;
    xk = xk_1 + (float)vk_1 * dt;
    vk = vk_1;
    rk = xm - xk;
    xk += (float)a * rk;
    vk += (float)b * rk / dt;
    xk_1 = xk;
    vk_1 = vk;
    return xk_1;
  }

private:
  float dt;
  float xk_1, vk_1, a, b;
  float xk, vk, rk;
  float xm;
};
#endif

#if 0
template <class T> class Kalman : public VirtualFilter<T> {
public:
  T operator()(T value) override final {
    kalmangain = errestimate / (errestimate + errmeasure);
    currentestimate = lastestimate + kalmangain * (value - lastestimate);
    errestimate = (1.0 - kalmangain) * errestimate +
                  fabs(lastestimate - currentestimate) * q;
    lastestimate = currentestimate;
    return currentestimate;
  };

private:
  float errmeasure{40}, errestimate{40}, q{.5}, currentestimate{.0},
      lastestimate{.0}, kalmangain{.0};
};
#endif

#endif