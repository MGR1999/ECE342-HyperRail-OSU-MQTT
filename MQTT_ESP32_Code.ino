/******************************************************************************
MQTT_ESP32_Code.ino v.1.2.
Arduino code for subscribing to MQTT topic for recieving messages
Date: 2/17/2021
Authors: 

Michael Guske, Oregon State University
Alex Wende, SparkFun Electronics

This code connects the ESP32 to a MQTT broker and subcribes to a topic. 
The main purpose of this code is for recieving messages from a client connected
to the MQTT broker.
******************************************************************************/

#include <WiFi.h>
#include <PubSubClient.h>

const char *WifiName =  "Normies-in 69ghz";   // name of your WiFi network
const char *password =  "AACDKM12345"; // password of the WiFi network

const char *ID = "Examp";  // Name of our device, must be unique
const char *TOPIC = "ESP32";  // Topic to subcribe to


WiFiClient wclient;
PubSubClient client(wclient); // Setup MQTT client


void callback(char* topic, byte* payload, unsigned int length) {
  String response;

  for (int i = 0; i < length; i++) {
    response += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(response);
  if(response == "Go")  // Turn the light on
  {
    client.publish(TOPIC,"Beavs!");
  }
  else if(response == "end")  // Turn the light off
  {
   client.publish(TOPIC,"Goodbye");
   exit(0);
  }
}

// Connect to WiFi network
void setup_wifi() {
  Serial.print("\nConnecting to ");
  Serial.println(WifiName);

  WiFi.begin(WifiName, password); // Connect to network

  while (WiFi.status() != WL_CONNECTED) { // Wait for connection
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Reconnect to client
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if(client.connect(ID)) {
      client.subscribe(TOPIC);
      Serial.println("connected");
      Serial.print("Subcribed to: ");
      Serial.println(TOPIC);
      Serial.println('\n');

    } else {
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200); // Start serial communication
  delay(100);
  setup_wifi(); // Connect to network
  client.setServer("broker.hivemq.com", 1883);
  client.setCallback(callback);// Initialize the callback routine
}

void loop() {
  if (!client.connected())  // Reconnect if connection is lost
  {
    reconnect();
  }
  client.loop();
}
