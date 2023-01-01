#ifndef _LEVEL_MEASURE_H_
#define _LEVEL_MEASURE_H_

#include "Arduino.h"

#include "device.h"
#include "lora_send.h"

#include "debug_utils.h"
#define DEBUG

/* #define ANALOG_PIN 36
#define CHARGE_PIN 12

#define C_LEVEL_MAX 300
#define C_LEVEL_MIN 200 */

TimerHandle_t level_measurementTimer;

//**********************************************************//
//***** NIVEL POR CAPACIDAD *****************************//
//**********************************************************//

/* void level_measurement()
{
    pinMode(CHARGE_PIN, OUTPUT);
    digitalWrite(CHARGE_PIN, LOW);

    pinMode(ANALOG_PIN, INPUT);

    float capacitancia_media;
    float capacitancia_suma;

    int long level;

    for (int i = 0; i < 100; i++)
    {
        digitalWrite(CHARGE_PIN, HIGH);

        int val = analogRead(ANALOG_PIN);

        digitalWrite(CHARGE_PIN, LOW);

        float capacitancia = (float)val * 4.7 / (float)(4096 - val);
        capacitancia_suma = capacitancia + capacitancia_suma;
    }
    capacitancia_media = capacitancia_suma / 100;
    // capacitancia_suma = 0;

    level = map(capacitancia_media, C_LEVEL_MIN, C_LEVEL_MAX, 0, 100);

    DEBUG_PRINT("Valor en pF: ");
    DEBUG_PRINT(capacitancia_media);

    sendDataLora((String)nivelDepHuerto + "=" + level);

} */

//**********************************************************//
//***** NIVEL POR ULTRASONIDOS *****************************//
//**********************************************************//

// Configuramos los pines del sensor Trigger y Echo
#define PIN_TRI 25
#define PIN_ECHO 36

// Constante velocidad sonido en cm/s
#define VEL_SON 34500.0

// Número de muestras
#define N_SAMPLES 10

// Distancia a los lleno y vacío
#define FULL_DISTANCE 15.0
#define EMPTY_DISTANCE 200.0

// Método que inicia la secuencia del Trigger para comenzar a medir
void iniciarTrigger()
{
    // Ponemos el Triiger en estado bajo y esperamos 2 ms
    digitalWrite(PIN_TRI, LOW);
    delayMicroseconds(2);

    // Ponemos el pin Trigger a estado alto y esperamos 10 ms
    digitalWrite(PIN_TRI, HIGH);
    delayMicroseconds(10);

    // Comenzamos poniendo el pin Trigger en estado bajo
    digitalWrite(PIN_TRI, LOW);
}

void level_measurement()
{

    float distance; // Variable ara almacenar distancia

    float total = 0;       // Total de las que llevamos
    float avg_measure = 0; // Media de las medidas

    unsigned long tiempo = 0;

    // Ponemos el pin Trig en modo salida
    pinMode(PIN_TRI, OUTPUT);
    // Ponemos el pin Echo en modo entrada
    pinMode(PIN_ECHO, INPUT);

    for (int i = 0; i < N_SAMPLES; i++)
    {
        iniciarTrigger();

        // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
        tiempo = pulseIn(PIN_ECHO, HIGH);

        // Obtenemos la distancia en cm, hay que convertir el tiempo en segudos ya que está en microsegundos
        // por eso se multiplica por 0.000001
        distance = tiempo * 0.000001 * VEL_SON / 2.0;

        // Añadimos la lectura al total
        total += distance;

        vTaskDelay(pdMS_TO_TICKS(100));
    }

    // Calculamos la media
    avg_measure = total / N_SAMPLES;

    // Calcula el nivel de liquido y lo envia mediante LoRa
    float measure_water = (EMPTY_DISTANCE - avg_measure) * 80;

    // Envia los datos mediante lora
    sendDataLora((String)nivelDepHuerto + "=" + (String)measure_water);

    DEBUG_PRINT(avg_measure);
    DEBUG_PRINT(" cm");

    DEBUG_PRINT(measure_water);
    DEBUG_PRINT(" l");
}

#endif // _LEVEL_MEASURE_H_
