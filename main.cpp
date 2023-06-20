#include <Servo.h>
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "#"
#define WIFI_PASSWORD "#"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDCeFB7Stv4H_Ix5YlJSk5-db9wKezxkIU"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://exous-39536-default-rtdb.firebaseio.com/"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int intValue;
float floatValue;
bool signupOK = false;
int counter_reset = 0;

Servo shoulder_x;
Servo shoulder_y;
Servo albow;
Servo wrest;

void catch_move();
void move_up();
void bye();

void setup() {
  shoulder_x.attach(27);
  shoulder_y.attach(14);
  albow.attach(12);
  wrest.attach(13);

  // for firebase
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getInt(&fbdo, "/order")) {
      if (fbdo.dataType() == "int") {
        intValue = fbdo.intData();
        Serial.println(intValue);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  }

  switch (intValue)
  {
    case 1:
    move_up();
    break;
    
    case 2:
    bye();
    break;
    
    case 3:
    catch_move();
    break;
  }

  delay(500);
  

}

void move_up(){
    if(counter_reset > 1){
      counter_reset = 0;
      double shoulder_y_counter = 180;
      for(int i = 0 ; i <= 75 ; i++){
        shoulder_x.write(i);
        shoulder_y.write((shoulder_y_counter -= 90.0/75.0));
        delay(10);
      }
    }
    for(int i = 0 ; i <= 75 ; i++){
      shoulder_x.write(i);
      shoulder_y.write(180);
      albow.write(140);
      delay(20);
    }
    delay(500);

    for(int i = 75 ; i >= 0 ; i--){
      shoulder_x.write(i);
      shoulder_y.write(180);
      albow.write(140);
      delay(20);
    }
    delay(500);
    counter_reset++;
}

void bye(){
    for(int i = 0; i <= 75 ; i++){ //
    shoulder_x.write(i); // make it reach 90 with loop
    shoulder_y.write(90);
    albow.write(50);
    wrest.write(90);
    delay(15);
  }
  for(int i = 75; i >= 0 ; i--){
    shoulder_y.write(90); 
    albow.write(50);
    wrest.write(90);
    shoulder_x.write(i); // make the same above
    delay(15);
  }
}

void catch_move(){
    shoulder_x.write(75);
    wrest.write(120);

    double shoulder_y_counter = 180 ;
    for(int i = 120 ; i >= 60 ; i--){
      albow.write(i);
      shoulder_y.write(shoulder_y_counter);
      shoulder_y_counter -= 2/3 ;
      delay(20);
    }

    delay(500);
    for(int i = 60 ; i <= 120 ; i++){
      albow.write(i);
      shoulder_y.write(shoulder_y_counter);
      shoulder_y_counter += 2/3 ;
      delay(20);
    }
    delay(500);

}

/* void init(){
  double j = 60 ;


    shoulder_x.write(90); // 75
    shoulder_y.write(90); 
    albow.write(140); 
    delay(2000);  

    shoulder_x.write(0); // 0
    shoulder_y.write(0);
    albow.write(60);
    delay(2000);

} */