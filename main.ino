#include "var_define.h"
#include "wifi_mqtt_define.h"

void setup() {

 #include "motor_define.h"
 #include "wifi_setup.h"
 #include "mqtt_setup.h"

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  #include "button_loop.h"

}

