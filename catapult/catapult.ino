#include <Servo.h>
Servo lockServo ; 
Servo armServo ; 
Servo trayServo ; 
Servo baseServo ; 

#define lockOpen    110 
#define lockClosed  20 

#define armOpen     140 
#define armArmed    45

#define trayClosed  177
#define trayOpened  172

void rest() {
  sweep(lockServo,lockServo.read(),lockOpen,15) ; 
  sweep(armServo,armServo.read(),armOpen,5) ; 
 }

void prepareToShoot(int armArm) {
  int armshoot;
  armshoot=(180-armArm)/3;
  sweep(lockServo,lockClosed,lockClosed,15) ; 
  sweep(armServo,armshoot,armshoot,5) ; 
  Serial.println("armshoot:");
  Serial.println(armshoot);
}

void shoot() {
  sweep(lockServo,lockServo.read(),lockOpen,15) ; 
}

void sweep ( Servo servo , int from , int to , int speed  ) {
  int pos = 0 ;
  if (from < to) {
    for (pos = from; pos <= to; pos += 1) { 
      servo.write(pos);              
      delay(speed);                       
    }  
  } else {
    for (pos = from; pos >= to; pos -= 1) { 
      servo.write(pos);              
      delay(speed);                       
    }
  }
}


void trayClose(){
  sweep(trayServo,trayServo.read(),trayClosed,22) ; 
}

void trayOpen() {
  sweep(trayServo,trayServo.read(),trayOpened,22) ; 
}

void trayRelease() {
    trayClose() ; 
    trayOpen() ; 
    trayClose() ; 
    delay(2000);
}

void baseMove(int jd) {
  sweep(baseServo,baseServo.read(),jd*90/100+10,15);
}

void setup() {
    /// connect servo motors
    lockServo.attach(3); 
    armServo.attach(5) ; 
    trayServo.attach(6);
    baseServo.attach(9) ;  
    Serial.begin(9600);
}

int auto_run(int jd,int aarm,int shooting)
{
    baseMove(jd);///This is my magic!!
    trayRelease(); 
    prepareToShoot(aarm) ;  
    Serial.println ("auto_runint jd,int aarm,int shooting");
    Serial.println(jd);
    Serial.println(aarm);
    Serial.println(shooting);
    if(shooting>=100){
       Serial.println("shoot");       
       shoot();
       rest();
    }
}

int  mylist[]={0, 0, 0, 0, 0, 0, 0};
int cur=0;
String strshow;
String item;
long itemint;

void loop() {  
    if (Serial.available() > 0) {
        item = Serial.readStringUntil(' ');
        if (String(item).equals(String("A"))) {
            cur = 0;
            Serial.println("A found");
        } else {
          itemint = String(item).toInt();
          cur++;
          Serial.println(cur);
          Serial.println(itemint);
          mylist[(int)(cur - 1)] = itemint;
          if (cur > 5) {
              cur = 5;
          }
       }
    }
    
    if(cur>=3){
     auto_run(mylist[0],mylist[1],mylist[2]);
     cur=0;
    };
}

