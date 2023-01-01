#ifndef _DEVICE_LORA_HANDLER_H_
#define _DEVICE_LORA_HANDLER_H_

#include <Arduino.h>

#include "device.h"

#include "debug_utils.h"
#define DEBUG

void data_lora_receive_control(String data)
{
    // Comprueba si es la electrovalvula del sector 1 y pasa los datos a la funcion
    // que se encarga de activar o desactivar la electrovalvula
    if (data.indexOf((String)evDepHuertoSec1) != -1)
    {
        String payload = data.substring(data.indexOf("=") + 1);

        DEBUG_PRINT((String)evDepHuertoSec1 + "=" + payload);

        // Control sector 1
        if (payload == ON)
        {
            DEBUG_PRINT("Sector_1=ON");
            digitalWrite(EV_SEC_1_ON, LOW);
            vTaskDelay(500);
            digitalWrite(EV_SEC_1_ON, HIGH);
        }
        else if (payload == OFF)
        {
            DEBUG_PRINT("Sector_1=OFF");
            digitalWrite(EV_SEC_1_OFF, LOW);
            vTaskDelay(500);
            digitalWrite(EV_SEC_1_OFF, HIGH);
        }

        // Envia los datos mediante lora
        sendDataLora((String)evDepHuertoSec1State + "=" + payload);
    }

    // Comprueba si es la electrovalvula del sector 2 y pasa los datos a la funcion
    // que se encarga de activar o desactivar la electrovalvula
    if (data.indexOf((String)evDepHuertoSec2) != -1)
    {
        String payload = data.substring(data.indexOf("=") + 1);

        DEBUG_PRINT((String)evDepHuertoSec2 + "=" + payload);

        if (payload == ON)
        {
            DEBUG_PRINT("Sector_2=ON");
            digitalWrite(EV_SEC_2_ON, LOW);
            vTaskDelay(500);
            digitalWrite(EV_SEC_2_ON, HIGH);
        }
        else if (payload == OFF)
        {
            DEBUG_PRINT("Sector_2=OFF");
            digitalWrite(EV_SEC_2_OFF, LOW);
            vTaskDelay(500);
            digitalWrite(EV_SEC_2_OFF, HIGH);
        }

        // Envia los datos mediante lora
        sendDataLora((String)evDepHuertoSec2State + "=" + payload);
    }
}

#endif //_DEVICE_LORA_HANDLER_H_
