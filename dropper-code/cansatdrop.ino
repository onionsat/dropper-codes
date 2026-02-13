#include <ESP32Servo.h>

static const int servoPin = 10;

Servo servo1;

int opened = 90;
int closed = 160;

void setup()
{
  Serial.begin(9600);

  //initializing uart(uart1)
  Serial1.begin(115200, SERIAL_8N1, 1, 0);
  servo1.attach(servoPin);
  servo1.write(closed);

  //running radiosetup function 3 times
  for(int i=0; i<3; i++)
  {
    Serial1.println("sys reset");
    delay(100);

    //setting up radio as lora
    Serial1.println("radio set mod lora");
    delay(100);

    //set pa on
    Serial1.println("radio set pa on");
    delay(100);

    //setting freq
    Serial1.println("radio set freq 862750000");
    delay(100);

    //setting power
    Serial1.println("radio set pwr 20");
    delay(100);

    //setting spreadingfactor
    Serial1.println("radio set sf sf10");
    delay(100);

    //setting sync byte
    Serial1.println("radio set sync 12");
    delay(100);

    //setting bandwith to 250
    Serial1.println("radio set bw 125");
    delay(100);
  }

  Serial1.println("radio rx 0");
  delay(100);
}

int servo_counter = 1;

void loop()
{
  if(Serial1.available())
  {
    String valasz = Serial1.readString();
    Serial.println(valasz);
    if(valasz.startsWith("radio_rx 12345678"))
    {
      if(servo_counter == 1)
      {
        servo1.write(closed);
        servo_counter = 2;
      }
      else if(servo_counter == 2)
      {
        servo1.write(opened);
        servo_counter = 1;
      }
    }
  }
}