#ifndef _LORA_RECEIVER_H_
#define _LORA_RECEIVER_H_
#include <Arduino.h>

#include "display_oled.h"
#include "device_lora_handler.h"
#include "log.h"

#include "debug_utils.h"
#define DEBUG

/* void testMem(String taskName)
{
    static int stackMem, stackMemTemp;

    stackMemTemp = uxTaskGetStackHighWaterMark(nullptr);

    if (!stackMem || (stackMemTemp < stackMem))
    {
        stackMem = stackMemTemp;
        Serial.printf("\n%s tiene stack mem %u\n", taskName.c_str(), stackMem);
    }
} */

void receiveDataLora(void *pvParameter)
{
    for (;;)
    {
        String rssi = "RSSI";
        String packSize = "--";
        String packetData = "";

        // try to parse packet
        int packetSize = LoRa.parsePacket();

        if (packetSize)
        {
            // received a packet
            packSize = String(packetSize, DEC);
            DEBUG_PRINT(packSize);

            rssi = String(LoRa.packetRssi(), DEC);
            DEBUG_PRINT(rssi);

            // read packet
            while (LoRa.available())
            {
                packetData += (char)LoRa.read();
            }

            // Procesa los datos recibidos
            data_lora_receive_control(packetData);

            // sendDataLora(packetData + " OK");

            write_log("Receive LoRa: " + packetData);
            DEBUG_PRINT(packetData);
        }

        // Calcula la memoria libre que queda de esta tarea, a fin de calcular la memoria necesaria para ella
        // testMem("receiveDataLora");

        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

#endif //_LORA_RECEIVER_H_