#include <Arduino.h>

// #include <Wire.h>

#include "config.h"
#include "wifi_functions.h"
#include "server_functions.h"
#include "lora_init.h"
#include "lora_receiver.h"
#include "display_oled.h"
#include "device.h"
#include "device_lora_handler.h"
#include "level_measure.h"
#include "log.h"

#include "debug_utils.h"
#define DEBUG

void setup()
{
  // Borra todas las claves del espacio de nombres en memoria
  // eraseFlash("config");

  // Inicializa el objeto con la variables de configuracion
  Config configData;

  // Inicia la conexion serial
  Serial.begin(115200);

  // Inicia el modulo LoRa
  init_lora();

  // Inicia el display OLED
  // init_oled();

  // Iniciamos los temporizadores encargados de reconectar la conexion wifi y mqtt, en caso de desconexion
  wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(wifiConnectSTA));

  // Se captura los eventos de la conexion wifi
  WiFi.onEvent(WiFiEvent);

  // Configuramos el modo del wifi
  WiFi.mode(configData.getWifiType());

  // Iniciamos la conexion wifi como punto de acceso
  wifiConnectAP();

  // Iniciamos la conexion wifi como cliente
  wifiConnectSTA();

  // Muestra los datos de conexion al punto de acceso
  // printDataWifiAP(configData);

  // Configura el servidor web
  serverHandlers();

  // Inicia ElegantOTA
  AsyncElegantOTA.begin(&server);

  // Inicia el servidor
  server.begin();

  write_log("Servidor HTTP iniciado...");

  DEBUG_PRINT("Servidor HTTP iniciado...");

  // Inicia la tarea que recibe los datos por LoRa
  xTaskCreatePinnedToCore(receiveDataLora, "loraData", 2048, nullptr, 5, nullptr, 1);

  // Inicia la tarea encargada de medir el nivel del deposito
  // xTaskCreatePinnedToCore(level_measurement, "level_measure", 2048, nullptr, 5, nullptr, 1);

  // Inicia el temporizador encargado de medir el nivel del deposito periodicamente
  level_measurementTimer = xTimerCreate("level_measure", pdMS_TO_TICKS(5000), pdTRUE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(level_measurement));
  xTimerStart(level_measurementTimer, 0);

  write_log("Temporizador de medicion del nivel iniciado...");

  // Inicia los pines usados para activas los dispositivos
  initPinDevice();
}

void loop()
{
  /* sendDataLora((String)n);
  n++;
  vTaskDelay(5000); */

  if (Serial.available())
  {
    data_lora_receive_control(Serial.readString());
  }
}
