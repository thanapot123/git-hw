#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

const int button_rest = 6;
const int  check_led_1_6 = 5;
const int  check_led_7_9 = 5;
//const int sv = 8;
const int BUZZER = 9;
const int lamp_g = 10;
const int lamp_ng = 7;
const int signal_start = 2;
//const int signal_up = 7;
const int relay_check_in = 13;
const int relay_check_out = 13;
const int sensor_jig = 3;
const int relay_jig = 4;
const int check_start = 12;
const int relay_start = 11;

int g = 0,ng = 0; //สถานะชิ้นงาน 
int check = 0; //ตัวแปรsignal_start
int check1_6 = 0;
int button_rst = 0;
int count = 0; //ตัวนับเวลา
int i;
int check_lamp_show = 0;
int sum_=0;
int sensor_check_j =0;
int check_ = 0;
bool check_j = 0;
int res1 = 0;
int check_h = 0;

bool check_s = 0;
bool lamp = 0;


//int check_led_=0;

//eeprom
byte val0;
byte val1;
byte val2;

LiquidCrystal_I2C lcd(0x27, 20, 4);
//LiquidCrystal_I2C lcd(A1,A2);


void setup()
{
  Serial.begin(115200);
  //input
pinMode(button_rest, INPUT);
pinMode(signal_start, INPUT);
pinMode(check_led_1_6, INPUT);
pinMode(check_led_7_9, INPUT);
pinMode(sensor_jig, INPUT);
pinMode(check_start, INPUT);

  //output
pinMode(BUZZER, OUTPUT);
pinMode(lamp_g, OUTPUT);
pinMode(lamp_ng, OUTPUT);
//pinMode(signal_up, OUTPUT);
pinMode(relay_check_in, OUTPUT);
pinMode(relay_check_out, OUTPUT);
pinMode(relay_jig, OUTPUT);
pinMode(relay_start, OUTPUT);




//แสดงผลบนจอLCD
lcd.init();
lcd.begin(16,2);
lcd.backlight(); 

lcd.setCursor(0, 0);
lcd.print("Total");
lcd.setCursor(8, 0);
lcd.print(val2);
lcd.setCursor(0, 1);
lcd.print("G:");
lcd.setCursor(5, 1);
lcd.print(val0);
lcd.setCursor(7, 1);
lcd.print("NG:");
lcd.setCursor(13, 1);
lcd.print(val1);
/*
EEPROM.put(0, g);
EEPROM.put(1, ng);
EEPROM.put(2, sum_);
//digitalWrite(relay_jig, LOW);
*/
}
//การทำงานของระบบ
void loop(){
  //digitalWrite (BUZZER, LOW);
  //digitalWrite (lamp_g , LOW); 
 // digitalWrite (lamp_ng , LOW); 
/*
  int signal_start = Serial.read();
Serial.println("signalstart = ");
Serial.println(signal_start);
*/
//check_start_();
check_h_();
check_sensor_jig();
signalstart();
checkled1_6();
checkled7_9();
lamp_();
//.BUZZER_();
//signalup();
sw_rst_();
/*
EEPROM.put(sizeof(g), val0);
EEPROM.put(sizeof(ng), val1);
EEPROM.put(sizeof(sum_), val2);

EEPROM.get(0,val0);
EEPROM.get(1,val1);
EEPROM.get(2,val2);

Serial.println(val0);
Serial.println(val1);
Serial.println(val2);
*/


EEPROM.update(0 , g);
EEPROM.update(1 , ng);
EEPROM.update(2 , sum_);
val0 = EEPROM.read(0);
val1 = EEPROM.read(1);
val2 = EEPROM.read(2);
Serial.println(val0);
Serial.println(val1);
Serial.println(val2);


 sum_ = val0+val1;
    lcd.setCursor(8, 0);
    lcd.print(val2);
    lcd.setCursor(6, 1);
    lcd.print(val0);
    lcd.setCursor(12, 1);
    lcd.print(val1);

}
/*
void check_start_(){
  if((digitalRead(check_start) == LOW){
      check_s = 1;
      delay(10);
      Serial.println("check_start_LOW");
  }
  else if(digitalRead(check_start == HIGH)){
      check_s = 0;
  }
}
*/
void check_h_(){
  delay(10);
    if((digitalRead(sensor_jig) == LOW)){
      check_h = 1;
      //digitalWrite(lamp_g, HIGH);
      delay(10);
  }
   else if(digitalRead(sensor_jig == HIGH)){
      check_h = 0;
      check_s = 0;
      check_j = 0;
      //digitalWrite(lamp_ng, LOW); 
      //digitalWrite(lamp_g, LOW);
      
  }
  Serial.println("check_h ::");
  Serial.println(check_h);
}

// ขา 3
void check_sensor_jig(){
delay(10);
  Serial.print("check_s : ");
  Serial.println(check_s);
  if((check_h == 1)&&(check_s == 0)){
    delay(100);
    digitalWrite(relay_jig, HIGH);
    Serial.println("relay_play");
    delay(50);
    check_s = 1;
    //check_ =0;
    
  }

  else if(digitalRead(sensor_jig) == HIGH){
    Serial.println("sensor_jig /HIGH/");
   // check_ = 1; 
   digitalWrite(relay_start, LOW);
  // check_s = 1;

  }
}

//รับสัณญาณจาก jig ขา 2 
void signalstart(){
  //delay(200);
  
  if((digitalRead(signal_start) == LOW)&&(check_j == 0)){
      check=1;
      check_j = 1;
      Serial.print("/LOW/void signal_start = ");
      Serial.println(signal_start);
      Serial.println(check);
      delay(50);
      digitalWrite(lamp_g, LOW);
      digitalWrite(lamp_ng, LOW);

  } 
  else if(digitalRead(signal_start) == HIGH){
      Serial.print("/HIGH/void signal_start = ");
      Serial.println(signal_start);
     // digitalWrite (BUZZER, LOW);
      //digitalWrite (lamp_g , LOW); 
      //check_j = 1;
    //check_s =0;
    digitalWrite(relay_start, LOW);
    check= 0;
      //digitalWrite (lamp_ng , LOW);
  }
  /*
  else if ((digitalRead(signal_start) == HIGH)&&(check_s == 1)){

       digitalWrite(relay_jig, LOW);
    check_j = 1;
    check_s =0;
  }
     */   
  
  
}

//เช็คสถานะไฟled
void checkled1_6(){
/*
    if(digitalRead(check_led) == LOW){
      check_led_=1;
      Serial.print("/LOW/void check_led = ");
      Serial.println(check_led);
      Serial.print("check_led=");
      Serial.println(check_led_);
    }
    if(digitalRead(check_led) == HIGH){
      check_led_=2;
      Serial.print("/LOW/void check_led = ");
      Serial.println(check_led);
      Serial.print("check_led=");
      Serial.println(check_led_);
    }*/
  
  //Serial.println(check_led_1_6);
  //Serial.println(check_led_7_9);
  delay(50);
Serial.println("chack_led : ");
Serial.println(check_led_1_6);
  if((check == 1)&&(digitalRead(check_led_1_6) == LOW)){
delay(1000);
      Serial.println("/check 1-6 : G");
      check=0;
      digitalWrite(relay_check_in, HIGH);
      digitalWrite(relay_check_out, HIGH);
      check1_6 = 1;
     delay(1000);
      
  }
  else if((check == 1)&&(digitalRead(check_led_1_6) == HIGH)){
    delay(1000);
      check_lamp_show = 20;
      Serial.println("/check 1-6 : NG");
      Serial.print("check LAMP : ");
      Serial.println(check_lamp_show);
      check=0;
      delay(1000);
      lamp = 2;
  }
     
}
void checkled7_9(){
  Serial.println("led_1-6 : ");
  Serial.println(check1_6);
  delay(50);
delay(10);
  if((check1_6 == 1)&&(digitalRead(check_led_7_9) == LOW)){
    delay(1000);
      check_lamp_show = 10;
      Serial.println("/check 7-9 : G");
      Serial.print("check LAMP : ");
      Serial.println(check_lamp_show);
      check1_6=0;
      delay(1000);
      digitalWrite(relay_check_in, LOW);
      digitalWrite(relay_check_out, LOW);
      lamp = 1;
  }
  else if((check1_6 == 1)&&(digitalRead(check_led_7_9) == HIGH)){
    delay(1000);
      check_lamp_show = 20;
      Serial.println("/check 7-9 : NG");
      Serial.print("check LAMP : ");
      Serial.println(check_lamp_show);
      check1_6=0;
      delay(1000);
     digitalWrite(relay_check_in, LOW);
      digitalWrite(relay_check_out, LOW);
      lamp = 2;
  }

}
//แสดงสถานะไฟ
void lamp_(){

    
  if(check_lamp_show == 10){
      g++;
      val0++;
      
      digitalWrite(lamp_g, HIGH);
      Serial.print("G = ");
      Serial.println(val0);  
      EEPROM.update(0, g);
      lcd.setCursor(4, 1);
      lcd.print(val0);
      check_lamp_show = 0;
      check=0;
      digitalWrite(relay_jig, LOW);
      delay(200);

       digitalWrite(BUZZER, HIGH);
      delay(100);
      digitalWrite(BUZZER, LOW);
      delay(100);
      Serial.println("Buzzer_g");
      //digitalWrite(lamp_g, HIGH);
      
      //check_led_=0;
      
      //digitalWrite(relay_start, HIGH);
      
  }
  else if(check_lamp_show == 20){
      ng++;
      val1++;
      digitalWrite(lamp_ng, HIGH);
      Serial.print("NG = ");
      Serial.println(val1); 
      EEPROM.update(1, ng);
      lcd.setCursor(12, 1);
      lcd.print(val1);  
      check_lamp_show = 0;
      check=0;
      //check_led_=0;

      digitalWrite(BUZZER, HIGH);
      res1 = 1;
      Serial.println("Buzzer_ng");
      delay(200);
  }   


}

void BUZZER_(){
  
  if(digitalRead(lamp_ng) == HIGH){
      digitalWrite(BUZZER, HIGH);
      res1 = 1;
      Serial.println("Buzzer_ng");
      //delay(30000);
  } 
  

  else if(digitalRead(lamp_g) == HIGH){
      digitalWrite(BUZZER, HIGH);
      delay(100);
      digitalWrite(BUZZER, LOW);
      delay(100);
      Serial.println("Buzzer_g");
      digitalWrite(lamp_g, HIGH);
  }

}

//ส่งสัญญาณกลับไปหา Jig
/*
void signalup(){

  if(digitalRead(lamp_g) == HIGH){
    delay(800);
    lamp_g == LOW;
    signal_up == HIGH;
  }
  else if(digitalRead(lamp_ng) == HIGH){
    delay(400);
    signal_up == LOW;
  }
}
*/
//ปุ่ม รีเช็ต
void sw_rst_(){
  delay(10);
 // Serial.println("testtttttt");
   if(digitalRead(button_rest) == LOW){
    Serial.println("rst_1");
    digitalWrite(BUZZER, LOW);
    //digitalWrite(lamp_ng, LOW);                                                                               
    //signal_up == LOW;                 
    //digitalWrite(relay_start, HIGH);
    digitalWrite(relay_jig, LOW);
    check_s =1;
    digitalWrite(relay_check_in, LOW);
    digitalWrite(relay_check_out, LOW);

    res1 = 0;
    delay(500);

     }

     if(digitalRead (button_rest) == LOW){
       delay(300);
      button_rst++;
      Serial.println(button_rst);
      }
     if(button_rst == 3){
      Serial.println("rst_sum");
       digitalWrite(BUZZER, HIGH);
       delay(10);
      digitalWrite(BUZZER, LOW);
      delay(10);
      digitalWrite(BUZZER, HIGH);
       delay(10);
      digitalWrite(BUZZER, LOW);
      digitalWrite(lamp_ng, LOW);
      digitalWrite(lamp_g, LOW);
      //signal_up == LOW;
      g=0;
      ng=0;
      button_rst=0;
      check_lamp_show=0;
      check_s=1;
      //digitalWrite(relay_start, HIGH);
      digitalWrite(relay_jig, LOW);
      digitalWrite(relay_check_in, LOW);
      digitalWrite(relay_check_out, LOW);
      delay(100);
      EEPROM.update(0 , 0);
      EEPROM.update(1 , 0);
      EEPROM.update(2 , 0);
     }
  }
