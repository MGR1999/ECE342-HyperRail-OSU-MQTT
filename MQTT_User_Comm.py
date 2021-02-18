#MQTT_Comm_Script v.1.3.
#Date: 2/17/2021
#Author: Michael Guske, Oregon State University
#
#
#Python script for publishing to MQTT based system. 
#Takes in user input and sends to subscribed MQTT topic 


import paho.mqtt.client as mqtt #import the client lib
print("connecting to broker")

while(1):
    command = input()
    broker_address = "broker.hivemq.com" 
    client = mqtt.Client("Group-11-ESP32") #create/renew an instance of the client
    client.connect(broker_address) #connect to the broker
    #print("Subscribing to topic","room")
    #client.subscribe("room")   for subscribing to broker
    if(command == "end"):
        exit()
    print("Publishing command to ESP32")
    client.publish("ESP32",command) #client.publish(name of client, message)
    