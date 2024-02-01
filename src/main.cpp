/*
HIDROMATICO V1.0b
Control de sistema hidroponico con integracion MQTT - HomeAssistant
Diego Maroto - BilbaoMakers - Febrero 2024
*/



#pragma region INCLUDES

#include <TaskScheduler.h>				// Task Scheduler
#include <cppQueue.h>					// Libreria para uso de colas.
#include <ArduinoJson.h>				// ArduinoJson
#include <string>						// Para el manejo de cadenas
#include <NTPClient.h>					// Para la gestion de la hora por NTP
#include <WiFiUdp.h>					// Para la conexion UDP con los servidores de hora.
#include <ArduinoOTA.h>					// Actualizaciones de firmware por red.
#include <DNSServer.h>            		//Local DNS Server used for redirecting all requests to the configuration portal
#include <WiFiManager.h>          		//https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#pragma endregion


#pragma region Objetos

WiFiManager wm;
WiFiManagerParameter custom_mqtt_server("server", "mqtt server", "", 40);

#pragma endregion


#pragma region Funciones

void saveParamsCallback () {
  Serial.println("Get Params:");
  Serial.print(custom_mqtt_server.getID());
  Serial.print(" : ");
  Serial.println(custom_mqtt_server.getValue());
}

#pragma endregion


#pragma region SETUP
// funcion SETUP de Arduino
void setup() {
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP    
    // put your setup code here, to run once:
    Serial.begin(115200);
    
    //reset settings - wipe credentials for testing
    //wm.resetSettings();
    wm.addParameter(&custom_mqtt_server);
    wm.setConfigPortalBlocking(false);
    wm.setSaveParamsCallback(saveParamsCallback);

    //automatically connect using saved credentials if they exist
    //If connection fails it starts an access point with the specified name
    if(wm.autoConnect("AutoConnectAP")){
        Serial.println("connected...yeey :)");
    }
    else {
        Serial.println("Configportal running");
    }
}

#pragma endregion


#pragma region LOOP

// Funcion LOOP de Arduino
// Se ejecuta en el Core 1
// Como todo se getiona por Task aqui no se pone NADA
void loop() {
    wm.process();
    // put your main code here, to run repeatedly:
}

#pragma endregion


/// FIN DEL PROGRAMA ///