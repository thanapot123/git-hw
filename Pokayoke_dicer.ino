//กำหนดขา
const int signal_washing = 43;
const int signal_lamp_yellow = 41;
const int signal_detec_blowing = 49;
const int signal_airgun = 47;
const int signal_detec_scaning =45;
const int sw_rst = 53;
const int sw_scaning = 51;
const int relay_drying = 7;
const int relay_scaning = 6;
const int buzzer = 12;
//const int lamp_alam = 12;
const int lamp_washing = 10;
const int lamp_blowing = 9;
const int lamp_drying = 8;
//const int lamp_scaning = 8;
const int lamp_airgun_finished = 11;

//กำหนดตัวแปร
bool signal_washing_start = 0;
int signal_airgun_count = 0;
bool signal_airgun_finished = 0;
bool signal_drying_finished = 0;
int button_rst = 0;

void setup() {

//input
pinMode(signal_washing ,INPUT);
pinMode(signal_lamp_yellow ,INPUT);
pinMode(signal_detec_blowing ,INPUT);
pinMode(signal_airgun ,INPUT);
pinMode(signal_detec_scaning ,INPUT);
pinMode(sw_rst ,INPUT);
pinMode(sw_scaning ,INPUT);

//output
pinMode(buzzer ,OUTPUT);
//pinMode(lamp_alam ,OUTPUT);
pinMode(lamp_washing ,OUTPUT);
pinMode(lamp_blowing ,OUTPUT);
pinMode(lamp_airgun_finished ,OUTPUT);
pinMode(lamp_drying ,OUTPUT);
//pinMode(lamp_scaning ,OUTPUT);
pinMode(relay_drying ,OUTPUT);
pinMode(relay_scaning ,OUTPUT);

Serial.begin(115200);
}

void loop() {
  //delay(1000);
  
  signal_washing_();
  sensor_blowing();
  drying();
  scaning_();
  sw_scaning_();
  sw_rst_();
  /*
  digitalWrite(lamp_washing ,LOW);
    digitalWrite(lamp_blowing ,LOW);
    digitalWrite(lamp_drying ,LOW);
    */
}
void signal_washing_(){
  if(digitalRead(signal_washing) == LOW){

    Serial.print("/LOW/signal_washing_start = ");
    Serial.println(signal_washing_start);
    signal_washing_start = 1;
    digitalWrite(relay_drying ,HIGH);
    Serial.println("next------->blowing");
  }
  else if (digitalRead(signal_washing) == HIGH){
    //signal_washing_start = 0;
     Serial.print("/HIGH/signal_washing_start = ");
     Serial.println(signal_washing_start);
    
     
  }
}

void sensor_blowing(){
  if((digitalRead(signal_detec_blowing) == LOW)&&(signal_washing_start == 1)){

        if(digitalRead(signal_airgun) == LOW){
          delay(400);
          signal_airgun_count++;
          Serial.print("signal_airgun_count :");
          Serial.println(signal_airgun_count);
          
        }

       
        if(signal_airgun_count == 30){
          signal_airgun_count = 0;
          signal_airgun_finished = 1;
          digitalWrite(lamp_airgun_finished ,HIGH);
          digitalWrite(buzzer ,HIGH);
          delay(100);
          digitalWrite(buzzer ,LOW);
          Serial.print("signal_airgun_finished : ");
          Serial.println(signal_airgun_finished);
          Serial.println("next------->drying");
           digitalWrite(relay_drying ,LOW);
        }
       
    //signal_washing_start=0;
   
  }
  else if((digitalRead(signal_detec_blowing) == LOW)&&(signal_washing_start == 0)){
    digitalWrite(buzzer ,HIGH);
   // digitalWrite(lamp_alam ,HIGH);
  digitalWrite(lamp_washing ,HIGH);                                                                                                               
    Serial.print("alam!!!!!!!!1");
  }
}
void drying(){
  if((digitalRead(signal_lamp_yellow) == LOW)&&(signal_airgun_finished == 1)){
    signal_washing_start=0;
    signal_drying_finished = 1;
    delay(100);
    digitalWrite(lamp_airgun_finished ,LOW);
    Serial.println("next------->scaning");
    // signal_airgun_finished = 0;
  }
  else if((digitalRead(signal_lamp_yellow) == LOW)&&(signal_airgun_finished == 0)){
    digitalWrite(buzzer ,HIGH);
    digitalWrite(lamp_washing ,HIGH);
    digitalWrite(lamp_blowing ,HIGH);
    Serial.print("alam!!!!!!!!2");
  }
}
void scaning_(){
  if((digitalRead(signal_detec_scaning) == LOW)&&(signal_drying_finished == 1)){
    digitalWrite(relay_scaning ,HIGH);
    Serial.println("scan test");
    delay(8000);
    digitalWrite(relay_scaning ,LOW);
    Serial.println("-------------------finished--------------------");
    delay(1000);
    digitalWrite(lamp_airgun_finished ,LOW);
    signal_washing_start=0;
    signal_airgun_count = 0;
    signal_airgun_finished = 0;
    signal_drying_finished = 0;
    
  }
 else if((digitalRead(signal_detec_scaning) == LOW)&&(signal_drying_finished == 0)){
    digitalWrite(buzzer ,HIGH);
    digitalWrite(lamp_washing ,HIGH);
    digitalWrite(lamp_blowing ,HIGH);
    digitalWrite(lamp_drying ,HIGH);
    Serial.print("alam!!!!!!!!3");
 }
 
}
/*
void buzzer_(){
}
void lamp_(){
}
*/
void sw_scaning_(){
  if((digitalRead(sw_scaning) == LOW)&&(digitalRead(signal_detec_scaning) == LOW)){
    digitalWrite(relay_scaning ,HIGH);
    delay(50);
    digitalWrite(relay_scaning ,LOW);
    delay(50);
    digitalWrite(relay_scaning ,HIGH);
    delay(50);
    digitalWrite(relay_scaning ,LOW);
    delay(50);
    digitalWrite(relay_scaning ,HIGH);
    delay(50);
    digitalWrite(relay_scaning ,LOW);
    delay(50);
    Serial.println("scaning_m");

  }
  else if((digitalRead(sw_scaning) == LOW)&&(digitalRead(signal_detec_scaning) == HIGH)){
    digitalWrite(relay_scaning ,LOW);
    Serial.println("not scaning");
  }
}
void sw_rst_(){
  if(digitalRead(sw_rst) == LOW){
      //button_rst++;
      Serial.print("button_rst = ");
      Serial.println(button_rst);
      
  
      Serial.println("rs_All");
      button_rst = 0;
      digitalWrite(buzzer ,HIGH);
      delay(200);
      digitalWrite(buzzer ,LOW);
      digitalWrite(lamp_washing ,LOW);
      digitalWrite(lamp_blowing ,LOW);
      digitalWrite(lamp_drying ,LOW);
//      digitalWrite(lamp_scaning ,LOW);
      signal_drying_finished = 0;
      signal_airgun_finished = 0;
      signal_washing_start=0;
      signal_airgun_count = 0;
      delay(500);
      
      
  }
}