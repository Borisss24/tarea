#include "robot.hpp"

/* Motors pinout */
#define IN1 32
#define IN2 33
#define IN3 25
#define IN4 14
#define EN1 12
#define EN2 35
#define SNR 13
#define ULT 2

Robot robot(IN1, IN2, IN3, IN4, EN1, EN2, SNR);

char command;

void setup() {
    /* Robot */
    robot.begin("TERRENEITOR");
    robot.halt();

    /* Serial */
    Serial.begin(115200);
    Serial.println("System ready...");

}

void loop() {
    while(!robot.available()){;}
    command = robot.read();

    if(command == 'w')
        robot.setDirection("forward");
    else if(command == 's')
        robot.setDirection("backward");
    else if(command == 'd')
        robot.setDirection("ccw");
    else if(command == 'a')
        robot.setDirection("cw");
    else if(command == 'z')
        robot.halt();
    else if(command == 'x')
        robot.publishSensors();  
    else if(command == 'm')
        robot.readUltrasonicSensor();

    else
        Serial.println("Wrong command...");

 
    delay(50);

}