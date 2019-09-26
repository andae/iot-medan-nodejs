//
// Copyright 2019 Biwabit.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseStream_ESP8266 is a sample that stream bitcoin price from a
// public Firebase and optionally display them on a OLED i2c screen.

#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;


//#define WIFI_SSID "Linix.id"
//#define WIFI_PASSWORD "RooT84**//"
#define FIREBASE_DB_URL "iot-medan.firebaseio.com"
#define FIREBASE_DB_SECRET_KEY "diLNHycCEX9bCwm49wIxivTdD8AjzS69bErRbSGD"

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');


  wifiMulti.addAP("Linix.id", "RooT84**//");
  wifiMulti.addAP("biwabit.com", "Rx84Tx19");

  pinMode(5, OUTPUT);

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1000);
    Serial.print('.');
}
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_DB_URL, FIREBASE_DB_SECRET_KEY);
  Firebase.stream("/automation");
}


void loop() {


  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }

  if (Firebase.available()) {
     FirebaseObject event = Firebase.readEvent();
     String eventType = event.getString("type");
     eventType.toLowerCase();
     Serial.print(eventType);
     if (eventType == "put") {
      String path = event.getString("path");
      String data = event.getString("data");
      if (path.equals("/light/value")) {
        if (data.equals("on")) {
          digitalWrite(5, HIGH);
        } else {
          digitalWrite(5, LOW);
        }
      }
     }
  }
}
