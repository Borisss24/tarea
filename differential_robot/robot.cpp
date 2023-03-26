#include "robot.hpp"

Robot::Robot( int in1, int in2,  int in3, int in4, int en1, int en2, int snrPin) : dht(snrPin, DHT11){
    this->in1 = in1;
    this->in2 = in2;
    this->in3 = in3;
    this->in4 = in4;
    this->en1 = en1;
    this->en2 = en2;

    pinMode(snrPin, INPUT);
    dht.begin();
    ledcSetup(CHAN, FREQ, RSLT);
    ledcAttachPin(en1, CHAN);
    ledcAttachPin(en2, CHAN); //we are defining the frequenci, so if we move de en we must change de chan
  
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(en1, OUTPUT);
    pinMode(en2, OUTPUT);
 
  
}

void Robot::setMotor(String motor, String dir){
    if (motor == "right" and dir == "positive"){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
     }
     else if (motor == "right" and dir == "negative"){
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
     }
     else if (motor == "left" and dir == "positive"){
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
     }
     else if (motor == "left" and dir == "negative"){
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
     }
     else
         Serial.println("Wrong motor direction");
}

void Robot::setDirection(String dir){
    if (dir == "forward"){
            setMotor("right", "negative");
            setMotor("left", "positive");
            Serial.println("Robot: move forward");
    }
    else if (dir == "backward"){
            setMotor("right", "positive");
            setMotor("left", "negative");
            Serial.println("Robot: move backward");
    }
    else if (dir == "cw"){
            setMotor("right", "positive");
            setMotor("left", "positive");
            Serial.println("Robot: move cw");
    }
    else if (dir == "ccw"){
            setMotor("right", "negative");
            setMotor("left", "negative");
            Serial.println("Robot: move ccw");
    }
    else
        Serial.println("Wrong robot direction");
               
    return;
}

  void Robot::setVelocity(int vel){
  Serial.print("Robot: set Velocity percentage to ");
  Serial.println(vel);
  vel=map(constrain(vel, 0, 100),0,100,0,1023);
  ledcWrite(CHAN,vel);
  
  return;
  }


void Robot::halt(){
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    Serial.println("Robot: stop");

    return;
}


void Robot::publishSensors(){
  print("Relative humidity: ");
  print(dht.readHumidity());
  println(" %");
  print("Temperature: ");
  print(dht.readTemperature());
  println(" °C");


  return;
}

