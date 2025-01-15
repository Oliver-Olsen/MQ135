#include <Arduino.h>
#include <MQ135.h>

#define MQ_PIN A0

MQ135 mq135_sensor(MQ_PIN);


float temp = 24.8;      // Must assume/get current temp
float humidity = 30.0;  // Must use the current hum or assume it


/*
*       SENSOR VARIABLES
*/

float resistance_zero   = 0;
float corrected_zero    = 0;
float resistance        = 0;
float ppm_measured      = 0;
float ppm_corrected     = 0;

void setup()
{
        Serial.begin(11500);
}

void loop()
{
        resistance_zero = mq135_sensor.getRZero();
        corrected_zero  = mq135_sensor.getCorrectedResistance(temp, humidity);
        resistance      = mq135_sensor.getResistance();
        ppm_measured    = mq135_sensor.getPPM();
        ppm_corrected   = mq135_sensor.getCorrectedPPM(temp, humidity);

        Serial.println(ppm_corrected);
        delay(10000);
}
