//This is the code for The Auto Aid Cart Bluetooth Remote Controll and Gps Room Follower
//There Will Be A Serial Monitor in the Arduino App Specefied In the Website
//connect Bluetooth Device Named " HC-06 " device pascode will be 1234
//upload New Ping library which is in a zip file in the arduino code folder for this code to work
//program the buttons on the arduino app to the specefied values
//By Dharsan Ravindran

#include <SoftwareSerial.h>//embeds the serial software lirary so information can be transmitted via bluetooth
#include <Servo.h>//embeds the servo library so the servos can be programed
#define trigPin 3 // define the pins of your sensor
#define echoPin 6

int RxPin = 10;//sets pin number for rx pin on bluetooth module
int TxPin = 11;//sets pin number for the tx pin on bluetooth module

SoftwareSerial mySerial(RxPin, TxPin); // setting up connecting the rx and tx pins for the bluetooth module

Servo rightServo; // adds the right servo
Servo leftServo; // adds the left servo

char command;

void setup() {
  Serial.begin(9600);//starts the serial monitor on android device
  mySerial.begin(9600);//sets up the remote controll app
  Serial.println("You're connected via Bluetooth");//prints this as soon as you are connected via bluetooth
  rightServo.attach(13); // attaches the servo to pin 13
  leftServo.attach(12); // attaches the servo to pin 12
  pinMode(trigPin, OUTPUT);// set the trig pin to output (Send sound waves)
  pinMode(echoPin, INPUT);// set the echo pin to input (recieve sound waves)

}

void loop() {
  if (mySerial.available())//check if information is being transmitted through the app
  {
    command = (mySerial.read()); //reads the information being transmitted through the app
    if (command == '1') //if the number 1 is transmited "up arrow" the following code is transmitted
    {
      Serial.println("Auto Aid Cart Moving Forward");
      rightServo.writeMicroseconds(1700); //right servo moves forward
      leftServo.writeMicroseconds(1300);//left servo moves forward
    }

    else if (command == '2') //if the number 2 is transmited "down arrow" the following code is transmitted
    {
      Serial.println("Auto Aid Cart Moving Backward");
      rightServo.writeMicroseconds(1300); //right servo moves backward
      leftServo.writeMicroseconds(1700);//left servo moves backward
    }

    else if (command == '3') //if the number 3 is transmited "right arrow" the following code is transmitted
    {
      Serial.println("Auto Aid Cart Turns Right");
      rightServo.writeMicroseconds(1700); //right servo moves forward causing it to turn right
      leftServo.writeMicroseconds(1700);//left servo moves backward causing it to turn right
    }

    else if (command == '4') //if the number 4 is transmited "left arrow" the following code is transmitted
    {
      Serial.println("Auto Aid Cart Turns Left");
      rightServo.writeMicroseconds(1300); //right servo moves backward causing it to turn left
      leftServo.writeMicroseconds(1300);//left servo moves forward causing it to turn left
    }
    else if (command == '5') //if the number 5 is transmited " letter x" or "triangle" or "circle" or "square" the following code is transmitted
    {
      Serial.println("Auto Aid Cart Has Been Stopped");
      rightServo.writeMicroseconds(1500); //stops right servo
      leftServo.writeMicroseconds(1500);//stops left servo
    }
    else if (command == '6') //if the number 5 is transmited "select" the following code is transmitted
    {
      long duration, distance; // start the scan
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2); // delays are required for a succesful sensor operation.
      digitalWrite(trigPin, HIGH);

      delayMicroseconds(10); //this delay is required as well!
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration / 2) / 29.1; // convert the distance to centimeters.

      if (distance < 25) { //if distance is less than 25cm
        rightServo.write(90);
        leftServo.write(90);
      }

      else {

        rightServo.attach(13);
        leftServo.attach(12);//we are redeclaring the revo has to attach because in the lopp we will disconect it again and again
        delay(15);
        rightServo.write(180);
        leftServo.write(0);
        delay(5770);//servo goes straight for 5.7 seconds
        rightServo.detach();
        leftServo.detach();
        delay(200);//the servo disconects for0.2 seconds
        rightServo.attach(13);
        leftServo.attach(12);
        delay(15);// the servo attaches again
        rightServo.write(0);
        leftServo.write(0);
        delay(500);//servo turns left for 0.5 seconds
        rightServo.detach();
        leftServo.detach();
        delay(200);//servo disconects for 0.2 seconds
        rightServo.attach(13);
        leftServo.attach(12);
        delay(15);//servo re attcaches
        rightServo.write(180);
        leftServo.write(0);
        delay(2770);//servo goes forward for 2.77 seconds
        rightServo.detach();
        leftServo.detach();//servo disconnects

      }
    }
  }
}


