#!/usr/bin/python

#Initiate communication between Pi and Arduino.
import serial
read = serial.Serial('/dev/ttyACM0', 9600, 8, 'N', 1, timeout=5)

#Import general purpose input and output pins.
import RPi.GPIO as GPIO
#Set naming convention for IO pins
GPIO.setmode(GPIO.BCM)
#Set pin 18 for output
GPIO.setup(18,GPIO.OUT)

#Load the KNN model.
import pickle
with open('knn_pickle', 'rb') as knn_model:
          knn = pickle.load(knn_model)

#Infinite Loop
while True:

    #Read every line...
    line = read.readline()

    #...and run the KNN classifier on it.
    prediction = knn.predict(line)

    #If a fault is detected, 
    if prediction == '1':

	  #Engage output for buzzer, alarm, light, etc…
        GPIO.output(18, GPIO.HIGH)

	  #...and send SMS to maintenance personnel.
        from twilio.rest import Client

	  #Account SID and Authentication Token are given through Twilio
	  #during registration.
        account_sid = 'AC3aeb7ccad59423bfbf1e66fe42eca4c2'
        auth_token = '96a00c17caee38373dc4e56459bb2495'
        client = Client(account_sid, auth_token)
        message = client.api.account.messages.create(
                        to = '+18473610138',
                        from_ = '+17739182391',
                        body = '!!!FAULT DETECTED!!!')

    else:#Otherwise, keep output off and continue checking each line.
        GPIO.output(18, GPIO.LOW)
        print(line)
