#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <Arduino.h>
#include <WiFi.h>
#include "DHT.h"

#define CHAN 0
#define FREQ 5000
#define RSLT 10


class Robot{
    private:
        /* H-bridge pinout */
        int in1;
        int in2;
        int in3;
        int in4;
        int en1;
        int en2;
        int tri;
        int eco;

        /* DHT11 sensor */
        DHT dht;

        void setMotor (String, String);  
        WiFiServer wifiServer;
        WiFiClient client; 
      
        
    public:
        Robot(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);  
        void start (const char*, const char*);
        char getCommand();
	      void setDirection(String);
        void publishSensors();
        float ultrasonic();
	      void halt();  
        void setVelocity(int);
};

#endif