/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <MQ135.h>
#include <DHT.h>


#define MQ_PIN          A0
#define DHT_SENSORPIN   13

#define DHTTYPE         DHT11


MQ135 mq135_sensor(MQ_PIN);
DHT dht(DHT_SENSORPIN, DHTTYPE);

float temp      = 0;      // Must assume/get current temp
float humidity  = 0;      // Must use the current hum or assume it


float resistance_zero   = 0;
float corrected_zero    = 0;
float resistance        = 0;
float ppm_measured      = 0;
float ppm_corrected     = 0;


  /*
  * CODE STRUCTURE
  *
  * MEASURED DATA (TEMP/HUM)
  * MEASURE CO2
  * UPLOAD TO THINKSPEAK
  * GET CLOAD DATA
  * HANDLE/ACT ON DATA
  * 
  * 
  * 
  */

void dht11_readout(float *temp, float *humidity);
void mq135_measurement(float *resistance_zero, float *corrected_zero, float *resistance, float *ppm_measured,  float *ppm_corrected);



void setup() {
  Serial.begin(9600);
  dht.begin();
  
}

void loop() {
  dht11_readout(&temp, &humidity);
  mq135_measurement(&resistance_zero, &corrected_zero, &resistance, &ppm_measured,  &ppm_corrected);
  delay(10000);
}



void dht11_readout(float *temp, float *humidity)
{
  *temp     = dht.readTemperature();
  *humidity = dht.readHumidity();
}


void mq135_measurement(float *resistance_zero, float *corrected_zero, float *resistance, float *ppm_measured,  float *ppm_corrected)
{
  *resistance_zero = mq135_sensor.getRZero();
  *corrected_zero  = mq135_sensor.getCorrectedResistance(temp, humidity);
  *resistance      = mq135_sensor.getResistance();
  *ppm_measured    = mq135_sensor.getPPM();
  *ppm_corrected   = mq135_sensor.getCorrectedPPM(temp, humidity);

  
  Serial.println(*ppm_corrected);

}




