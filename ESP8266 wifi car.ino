#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define RightMotorSpeed 5
#define RightMotorDir   0 
#define LeftMotorSpeed  4
#define LeftMotorDir    2

char auth[] = "WQ-kWE9pEhgmvTkkKL5YKTWWKU2D31Di";  //auth για την εφαρμογή στο κινητό
char ssid[] = "Diko_Mas_wifi";
char pass[] = "densoulew";

int minRange = 312;    //τιμή στο joystick
int maxRange = 712;    // τιμή στο joystick

int minSpeed = 450;     //πρώτη ταχυτητα
int maxSpeed = 1020;    //δευτερη ταχυτητα
int noSpeed = 0;        //κενο



void moveControl(int x, int y)
{

  if(y >= maxRange && x >= minRange && x <= maxRange)   //αν μοχλος πάνω
  {
    digitalWrite(RightMotorDir,HIGH);       //δεξιος τροχος κινηση μπροστα
    digitalWrite(LeftMotorDir,HIGH);        //αριστεροςτροχος κινηση μπροστα
    analogWrite(RightMotorSpeed,maxSpeed);  //δεξιος τροχος ταχυτητα 2
    analogWrite(LeftMotorSpeed,maxSpeed);  //αριστερος τροχος ταχυτητα 2
  }
 
  // move forward right
  else if(x >= maxRange && y >= maxRange)  //αν μοχλος πανω
  {
   digitalWrite(RightMotorDir,HIGH);     //δεξιος τροχός μπροστα
   digitalWrite(LeftMotorDir,HIGH);      //αριστερος τροχος μπροστα
   analogWrite(RightMotorSpeed,minSpeed); //δεξιος τροχος ταχυτητα 1
   analogWrite(LeftMotorSpeed,maxSpeed); //αριστερος τροχος ταχυτητα 2

    
  }

  // move forward left
  else if(x <= minRange && y >= maxRange)   //αν μοχλος πανω
  {
    digitalWrite(RightMotorDir,HIGH);       //δεξιος τροχος μπροστα
    digitalWrite(LeftMotorDir,HIGH);        //αριστερος τροχος μπροστα
    analogWrite(RightMotorSpeed,maxSpeed);  //δεξιος τροχος ταχυτητα 2
    analogWrite(LeftMotorSpeed,minSpeed);   //αριστερος τροχος ταχυτητα 1



    
  }

  // neutral zone
  else if(y < maxRange && y > minRange && x < maxRange && x > minRange) //αν μοχλος στο κεντρο
  {
    analogWrite(RightMotorSpeed,noSpeed);   //δεξιος τροχος ακουνητος
    analogWrite(LeftMotorSpeed,noSpeed);    //αριστερος τροχος ακουνητος

    
  }

 // move back
  else if(y <= minRange && x >= minRange && x <= maxRange)  //αν μοχλος κατω
  {
    digitalWrite(RightMotorDir,LOW);    //δεξιος τροχος πισω
    digitalWrite(LeftMotorDir,LOW);     //αριστερος τροχος πισω
   analogWrite(RightMotorSpeed,maxSpeed); //δεξιος τροχος ταχυτητα 2  
    analogWrite(LeftMotorSpeed,maxSpeed); //αριστερος τροχος ταχυτητα 2

    
  }

  // move back and right
 else if(y <= minRange && x <= minRange)  //αν μοχλος κατω δεξια
  {
   digitalWrite(RightMotorDir,HIGH);      
    digitalWrite(LeftMotorDir,LOW);
    analogWrite(RightMotorSpeed,minSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed); 
    
  }

  // move back and left
  else if(y <= minRange && x >= maxRange)     //αν μοχλος κατω αριστερα
  {
    digitalWrite(RightMotorDir,LOW);          //δεξιος τροχος πισω
    digitalWrite(LeftMotorDir,HIGH);          //αριστερος τροχος μπροστα
    analogWrite(RightMotorSpeed,maxSpeed);    //δεξιος τροχος ταχυτητα 2
    analogWrite(LeftMotorSpeed,minSpeed);     //αριστερος τροχος ταχυτητα 1

    
  }


  // move FORWARD and right                 
 else if(y >= minRange && x <= minRange)    //αν μοχλος πανω αριστερα
  {
   digitalWrite(RightMotorDir,HIGH);      //δεξιος τροχος μπροστα
    digitalWrite(LeftMotorDir,LOW);       //αριστερος τροχος πισω
    analogWrite(RightMotorSpeed,maxSpeed);  //δεξιος τροχος ταχυτητα 2
    analogWrite(LeftMotorSpeed,minSpeed);   //αριστερος τροχος ταχυτητα 1
    
  }

  // move FORWARD and left
  else if(y >= minRange && x >= maxRange)   //αν τροχος πανω αριστερα
  {
    digitalWrite(RightMotorDir,LOW);        //δεξιος τροχος πισω
    digitalWrite(LeftMotorDir,HIGH);        //αριστερος τροχος μπροστα
    analogWrite(RightMotorSpeed,minSpeed);  //δεξιος τροχος ταχυτητα 1
    analogWrite(LeftMotorSpeed,maxSpeed);   //αριστερος τροχος ταχυτητα 2

  }

  
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
 
  // initial settings for motors off and direction forward
  pinMode(RightMotorSpeed, OUTPUT);   //δεξιο μοτερ
  pinMode(LeftMotorSpeed, OUTPUT);    //αριστερο μοτερ
  pinMode(RightMotorDir, OUTPUT); 
  pinMode(LeftMotorDir, OUTPUT);
 
  digitalWrite(RightMotorSpeed, LOW);
  digitalWrite(LeftMotorSpeed, LOW);
  digitalWrite(RightMotorDir, HIGH);
  digitalWrite(LeftMotorDir,HIGH);

 
 }


void loop()
{
 
  Blynk.run();
}


BLYNK_WRITE(V1)
{
  int x = param[0].asInt();
  int y = param[1].asInt();
 /*
  Serial.print("x value is: ");
  Serial.println(x);
  Serial.print("y value is: ");
  Serial.println(y);
 */
  moveControl(x,y);
}
