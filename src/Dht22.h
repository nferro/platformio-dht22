/**
 *  dht22.h
 *  Get readings from a DHT22 sensor. Based on OpenAg_DHT22
 */

#ifndef DHT22_H
#define DHT22_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

// 8 MHz(ish) AVR ---------------------------------------------------------
#if (F_CPU >= 7400000UL) && (F_CPU <= 9500000UL)
#define COUNT 3
// 16 MHz(ish) AVR --------------------------------------------------------
#elif (F_CPU >= 15400000UL) && (F_CPU <= 19000000L)
#define COUNT 6
// ESP8266 --------------------------------------------------------
#elif (F_CPU == 80000000L)
#define COUNT 11
#else
#error "CPU SPEED NOT SUPPORTED"
#endif

// how many timing transitions we need to keep track of. 2 * number bits + extra
#define MAXTIMINGS 85

class Dht22 {
public:
  static const uint8_t OK = 0;
  static const uint8_t WARN = 1;
  static const uint8_t ERROR = 2;

  // Public Functions
  Dht22(int pin);
  void begin();
  void update();
  bool get_air_temperature(float &value);
  bool get_air_humidity(float &value);

private:
  // Private Functions
  void getData();
  bool readSensor();

  // Private Variables
  int _pin;
  float _air_temperature;
  bool _send_air_temperature;
  float _air_humidity;
  bool _send_air_humidity;
  uint32_t _time_of_last_reading;
  const uint32_t _min_update_interval = 2000;

  uint8_t _data[6];
  uint8_t _count;
  uint32_t _last_read_time;
  bool _first_reading;

  uint8_t status_level;
  String status_msg;
};

#endif
