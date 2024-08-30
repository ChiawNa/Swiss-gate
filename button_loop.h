  if (digitalRead(buttonPin) == LOW) {  
    if (motor1Running) {
      Serial.println("Button pressed - stopping Motor 1");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      motor1Running = false;
    }
    if (motor2Running) {
      Serial.println("Button pressed - stopping Motor 2");
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
      motor2Running = false;
    }
  }


  if (motor1Running && (millis() - motor1StartTime >= motorRunTime)) {
    Serial.println("Auto-stopping Motor 1 after 5 seconds");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    motor1Running = false;
  }

  if (motor2Running && (millis() - motor2StartTime >= motorRunTime)) {
    Serial.println("Auto-stopping Motor 2 after 5 seconds");
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    motor2Running = false;
  }