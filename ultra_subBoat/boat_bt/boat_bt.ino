#include <SoftwareSerial.h>
#include<Servo.h>

Servo servo;
SoftwareSerial btSerial(2, 3);

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

long ultra_val=0;
String rxString = "";


String ult ;
int index ;
float ultra_value ;
long Distance_control ;
int state = 0;
int shutdown_cnt ; 

void loop() {

  servo.write(90);
  //delay(200);
  //servo.detach();

  digitalWrite(MotorA_1, LOW);
  digitalWrite(MotorA_2, LOW);

    if (btSerial.read() > 0){
        state = 1;
    }


  while (state == 1){

  if(btSerial.available()){
  char c = btSerial.read();
  rxString += c;
  }
  //Serial.println(rxString);
  

    if (rxString != "")
    {
      index = rxString.indexOf('@'); //@를 찾아서 인덱스 번호 반환 ex.21@ 이면 '2'
      ult = rxString.substring(0, index); //@ 앞까지의 문자열 반환 +문자열 반환도 하나씩 들어간다 
      
      if(ult.length() == index){ //@앞에까지의 문자열이 다 반환될때 변환
         
         ultra_value = ult.toFloat(); //문자열을 플롯 형태로 반환 
         ultra_val = long(ultra_value);  //플롯을 롱으로 바꾸어서 반환 
       }
     
      Serial.println(ultra_val);  
    
    }

     if(Distance_control != ultra_val){      
        Distance_control = ultra_val ;
     }

     
          if (Distance_control > 25&&ult.length() == index){
          //Serial.println("Motor 80%");
          digitalWrite(MotorA_1, HIGH);
          digitalWrite(MotorA_2, LOW);
          
          }
          else if (Distance_control <= 25 && ultra_val > 20&&ult.length() == index){
          //Serial.println("Motor 50%");
          digitalWrite(MotorA_1, HIGH);
          digitalWrite(MotorA_2, LOW);
          
          }

          else if (Distance_control <= 20 && ultra_val >10&&ult.length() == index){
          //Serial.println("Motor 30%");
          digitalWrite(MotorA_1, HIGH);
          digitalWrite(MotorA_2, LOW);
                     
          }

          else if (Distance_control <= 10&&ult.length() == index){
          Serial.println("Motor STOP");
          digitalWrite(MotorA_1, LOW);
          digitalWrite(MotorA_2, LOW);
          delay(100);
          shutdown_cnt += 1;
          //btSerial.println('C');
          }

         if(shutdown_cnt == 50){
          Serial.println("System Off");
          shutdown_cnt = 0;
          state = 0;
         }

    
        if(index > 0){ //인덱스가 0이상이면 @한번이 들어온것이므로 문자열 초기화 
         rxString="";
      }
        
   }

}
