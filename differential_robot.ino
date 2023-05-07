#include "robot.hpp"

/* Motors pinout */
#define IN1 32
#define IN2 33
#define IN3 25
#define IN4 14
#define EN1 12
#define EN2 35

// Sensors
#define SNR 13
#define TRI 18
#define ECO 19

//Wifi Connection
#define PORT 80
#define SSID "Totalplay-DBA2"
#define PASSWORD "DBA2E955BEqB7Ct3"

Robot robot(IN1, IN2, IN3, IN4, EN1, EN2, SNR, TRI, ECO, PORT);


void setup() {
    /* Robot */
    robot.start(SSID, PASSWORD);
    robot.halt();

    /* Serial */
    Serial.begin(115200);
    Serial.println("System ready...");
    
}

void loop() {
    char command = robot.getCommand();

    if(command.equals(String('f')))
        robot.setDirection("forward");
    else if(command.equals(String('w')))
        robot.setDirection("backward");
    else if(command.equals (String('s')))
        robot.setDirection("ccw");
    else if(command.equals(String ('d')))
        robot.setDirection("cw");
    else if(command.equals(String ('a')))
        robot.halt();
    else if(command.equals(String ('r')))
        robot.publishSensors();
    else{
      int velocity = command.toInt();
      //Serial.println(velocity);
      robot.setVelocity(velocity);
    }
      
        
    delay(50);

}


