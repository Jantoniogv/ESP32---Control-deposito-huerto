#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "Arduino.h"

#include "log.h"
#include "lora_send.h"

#include "debug_utils.h"
#define DEBUG

// Pines de los reles de las electrovalvulas
#define EV_SEC_1_ON 12
#define EV_SEC_1_OFF 13

#define EV_SEC_2_ON 15
#define EV_SEC_2_OFF 2

#define ON "ON"

#define OFF "OFF"

// Estado de cada electrovalvula
/* struct elecVal
{
    bool evDepHuertoSec1 = false;
    bool evDepHuertoSec2 = false;

} elecVal; */

// Topic recibidos
const char evDepHuertoSec1[] = "regar/huerto/sec1";
const char evDepHuertoSec2[] = "regar/huerto/sec2";

// Topic enviar estados
const char evDepHuertoSec1State[] = "regar/huerto/sec1/state";
const char evDepHuertoSec2State[] = "regar/huerto/sec2/state";

// Topic enviar
const char nivelDepHuerto[] = "nivel/deposito/huerto";

void initPinDevice()
{
    // Inicializar electrovalvula sector 1
    pinMode(EV_SEC_1_ON, OUTPUT);
    digitalWrite(EV_SEC_1_ON, HIGH);

    pinMode(EV_SEC_1_OFF, OUTPUT);
    digitalWrite(EV_SEC_1_OFF, HIGH);

    // Inicializar electrovalvula sector 2
    pinMode(EV_SEC_2_ON, OUTPUT);
    digitalWrite(EV_SEC_2_ON, HIGH);

    pinMode(EV_SEC_2_OFF, OUTPUT);
    digitalWrite(EV_SEC_2_OFF, HIGH);

    // Escribe en el log inicializacion de los pines
    write_log("Pines de las electrovalvulas iniciados...");
}

#endif // _DEVICE_H_