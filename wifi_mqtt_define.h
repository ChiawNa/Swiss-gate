#include <WiFi.h>              
#include <PubSubClient.h>      
#include <WiFiClientSecure.h>  
#include <ArduinoJson.h>

const char* ssid = "Hee Wifi";
const char* password = "423619no26";

const char* mqtt_server = "43719f133ee64f1c88475e83fac1642f.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;  
const char* mqtt_user = "user8";
const char* mqtt_password = "Ab123456";

WiFiClientSecure espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message [");
  Serial.print(topic);
  Serial.print("] ");
  
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  Serial.println(message);

  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.c_str());
    return;
  }

  const char* buttonValue1 = doc["button1"];
  const char* buttonValue2 = doc["button2"];
  const char* buttonValue3 = doc["button3"];

  if (buttonValue1) {
    if (strcmp(buttonValue1, "1") == 0) {
      if (!motor1Running) {
        Serial.println("Starting Motor 1");
        digitalWrite(motor1Pin1, HIGH);  
        digitalWrite(motor1Pin2, LOW);
        motor1Running = true;
        motor1StartTime = millis(); 
      }
    } else if (strcmp(buttonValue1, "0") == 0) {
      if (motor1Running) {
        Serial.println("Stopping Motor 1");
        digitalWrite(motor1Pin1, LOW);   
        digitalWrite(motor1Pin2, LOW);
        motor1Running = false;
      }
    } else {
      Serial.println("Unrecognized button value for Motor 1");
    }
  }

  if (buttonValue2) {
    if (strcmp(buttonValue2, "1") == 0) {
      if (!motor2Running) {
        Serial.println("Starting Motor 2");
        digitalWrite(motor2Pin1, HIGH);  
        digitalWrite(motor2Pin2, LOW);
        motor2Running = true;
        motor2StartTime = millis(); 
      }
    } else if (strcmp(buttonValue2, "0") == 0) {
      if (motor2Running) {
        Serial.println("Stopping Motor 2");
        digitalWrite(motor2Pin1, LOW);   
        digitalWrite(motor2Pin2, LOW);
        motor2Running = false;
      }
    } else {
      Serial.println("Unrecognized button value for Motor 2");
    }
  }

  if (buttonValue3) {
    if (strcmp(buttonValue3, "1") == 0) {
      if (!motor1Running || !motor2Running) {
        Serial.println("Starting both Motors");
        digitalWrite(motor1Pin1, HIGH);  
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, HIGH);  
        digitalWrite(motor2Pin2, LOW);
        motor1Running = true;
        motor2Running = true;
        motor1StartTime = millis(); 
        motor2StartTime = millis(); 
      }
    } else if (strcmp(buttonValue3, "0") == 0) {
      if (motor1Running || motor2Running) {
        Serial.println("Stopping both Motors");
        digitalWrite(motor1Pin1, LOW);   
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, LOW);   
        digitalWrite(motor2Pin2, LOW);
        motor1Running = false;
        motor2Running = false;
      }
    } else {
      Serial.println("Unrecognized button value for both Motors");
    }
  }
}

void reconnect() {
  if (!client.connected()) {
    if (!attemptingConnection && !connectedOnce) {
      Serial.print("Attempting MQTT connection...");
      attemptingConnection = true;
    }

    if (client.connect("ArduinoClient", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      Serial.flush(); 
      delay(100);     

      client.subscribe("test/1");

      attemptingConnection = false;
      connectedOnce = true;
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      Serial.flush(); 
      delay(100);     

      delay(5000);    
    }
  }
}