#include "robot.hpp"

Robot:: Robot(unsigned int in1, unsigned int in2, unsigned int in3, unsigned int in4, unsigned int en1, unsigned int en2, unsigned int snrPin, unsigned int tri, unsigned int eco, unsigned int port) : dht(snrPin, DHT11), wifiServer(port) {
    this->in1 = in1;
    this->in2 = in2;
    this->in3 = in3;
    this->in4 = in4;
    this->tri = tri; 
    this->eco = eco; 
    

    pinMode(snrPin, INPUT);
    dht.begin();

    this->en1 = en1;
    this->en2 = en2;
    ledcSetup(CHAN, FREQ, RSLT);
    ledcAttachPin(en1, CHAN);
    ledcAttachPin(en2, CHAN); //we are defining the frequenci, so if we move de en we must change de chan
    pinMode(en1, OUTPUT);
    pinMode(en2, OUTPUT);

    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(tri, OUTPUT);
    pinMode(eco, INPUT);
    
}

//start robot
void Robot:: start (const char* ssid, const char* password){
    // Static IP address
    IPAddress local_IP(192, 168, 100, 192);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 0, 0);
    IPAddress primaryDNS(8, 8, 8, 8);   
    IPAddress secondaryDNS(8, 8, 4, 4); 
    delay(1000);

    /* Configuring static IP address*/
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) 
      Serial.println("STA Failed to configure");

    /* Connecting to the WiFi network*/
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.println("Connecting to WiFi...");
      delay(1000);
    }
 
    Serial.println("Connected to the WiFi network");
    Serial.println(WiFi.localIP());
 
    wifiServer.begin();
}
//Getting a command
char Robot::getCommand(){
    /* Wait for a client */
    if(!client){
      do{
          client = wifiServer.available();
          Serial.println("Waiting for a client...");
          delay(1000);
      }while(!client);
      Serial.println("Conected to a client");
    }
   
    while (client.connected()) {
      if(client.available()) {
        String command = client.readString();
        return command;
      }
      delay(10);
    }
    
    client.stop();
    return String('e');
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
  client.print(dht.readHumidity());
  delay(500);
  client.print(dht.readTemperature());
  Serial.println("Robot: sensors");
  delay(500);
  client.print(ultrasonic());

  return;
}

float Robot::ultrasonic(){
  float time, distance; 

  digitalWrite(tri, LOW);
  delay(1);
  digitalWrite(tri, HIGH);
  delay(1);
  digitalWrite(tri, LOW);

  time = pulseIn(eco, HIGH);
  distance = time / 58.3;

  return distance;
}