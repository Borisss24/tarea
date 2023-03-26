
#ifndef ROBOT_HPP
#define ROBOT_HPP


#include <Arduino.h>
#include "BluetoothSerial.h"
#include <DHT.h>


#define CHAN 0
#define FREQ 5000
#define RSLT 10


class Robot : public BluetoothSerial{
    private:
        /* H-bridge pinout */
        int in1;
        int in2;
        int in3;
        int in4;
        int en1;
        int en2;

        /* DHT11 sensor */
        DHT dht;
        void setMotor(String, String);   

    public:
        
        Robot(int, int, int, int, int, int, int);  
	      void setDirection(String);
        void publishSensors();
	      void halt();  
        void setVelocity(int);
       
  
};

#endif