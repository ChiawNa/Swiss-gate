const int motor1Pin1 = 18;   
const int motor1Pin2 = 19;   
const int motor2Pin1 = 21;   
const int motor2Pin2 = 22;   
const int buttonPin = 23;   

bool motor1Running = false;
bool motor2Running = false;
bool attemptingConnection = false;  // Flag to manage connection status messages
bool connectedOnce = false;
unsigned long motor1StartTime = 0;  
unsigned long motor2StartTime = 0;  
const unsigned long motorRunTime = 5000; 