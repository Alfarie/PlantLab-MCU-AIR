#include <Task.h>
#include<SoftwareSerial.h>

TaskManager taskManager;
SoftwareSerial toHq(10,9);

#include "./modules/sensors.h"

void setup(){
    toHq.begin(9600);
    Serial.begin(115200);
    taskManager.StartTask(Sensors::instance());
}

void loop(){
    taskManager.Loop();
}