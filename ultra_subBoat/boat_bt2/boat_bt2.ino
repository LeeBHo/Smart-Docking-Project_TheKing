#include <SoftwareSerial.h>
#include<Servo.h>

Servo servo;
SoftwareSerial btSerial(2,3);

int MotorA_1 = 7;
int MotorA_2 = 8;



//pin set up

int servoPin = 5;

void setup()
{
  servo.attach(servoPin); 
  Serial.begin(9600);
  btSerial.begin(9600);

  pinMode(MotorA_1, OUTPUT);
  pinMode(MotorA_2, OUTPUT);
}

long D_data ;
int state=0;


void loop(){  

    servo.write(90);
    //delay(200);
    servo.detach();

    digitalWrite(MotorA_1, LOW);
    digitalWrite(MotorA_2, LOW);
   
   

    if (btSerial.read() > 0){
        state = 1;
    }

 
  while( state == 1)
  {
    if(btSerial.available())
    { 
        
        D_data = btSerial.read();
        Serial.println(D_data);

      
          if (D_data > 25){
          //Serial.println("Motor 80%");
          digitalWrite(MotorA_1, HIGH);
          digitalWrite(MotorA_2, LOW);
          //servo.write(90);
          
          }
          else if (D_data <= 25 && D_data > 20){
          //Serial.println("Motor 50%");
          digitalWrite(MotorA_1, HIGH);
          digitalWrite(MotorA_2, LOW);
          //servo.write(90);
          }

          else if (D_data <= 20 && D_data >10){
          //Serial.println("Motor 30%");
          digitalWrite(MotorA_1, HIGH);
          digitalWrite(MotorA_2, LOW);
          //servo.write(90);           
          }

          else if (D_data <= 10){
          //Serial.println("Motor STOP");
          digitalWrite(MotorA_1, LOW);
          digitalWrite(MotorA_2, LOW);
          //servo.write(90);
          delay(50);
          btSerial.println('C');
        

          }

          if(D_data == 'E')
          {
            delay(50);
            Serial.println("System Stop");
            btSerial.println('F');
            btSerial.flush();
            Serial.flush();
           
            state = 0;
            D_data = 0;           
          }

        
    }
  }
}
