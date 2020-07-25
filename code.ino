#include <Wire.h> 
#include "max6675.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f,20,4);  //sometimes the adress is not 0x3f. Change to 0x27 if it dosn't work.

/*    i2c LCD Module  ==>   Arduino
 *    SCL             ==>     A5
 *    SDA             ==>     A4
 *    Vcc             ==>     Vcc (5v)
 *    Gnd             ==>     Gnd      */

#include <SPI.h>
//We define the SPI pìns
#define MAX6675_CS   10
#define MAX6675_SO   12
#define MAX6675_SCK  13

//Pins
int PWM_pin = 3;
int val;
int x;
//Variables
float temperature_read = 0.0;
int set_temperature ;
float PID_error = 0;
float previous_error = 0;
float elapsedTime, Time, timePrev;
int PID_value = 0;
int thermoDO = 9;
int thermoCS = 10;
int thermoCLK = 13;
long previousMillis = 0; 
long interval = 300;

//PID constants
int kp = 8.8;   int ki = 0.1;   int kd = 1.5;
int PID_p = 0;    int PID_i = 0;    int PID_d = 0;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  pinMode(PWM_pin,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  TCCR2B = TCCR2B & B11111000 | B00000111;
  Time = millis(); 
  lcd.begin();
  lcd.backlight();
  lcd.print("HOT AIR STATION");
  lcd.setCursor(0,1);
  lcd.print("    LOADING..");
  delay(2500);
  lcd.clear();
  lcd.print("  DEVELOPED BY");
  lcd.setCursor(0,1);
  lcd.print("  ELDHO KURIAN");
  delay(2500);
  lcd.clear();
   lcd.print("  CO-FOUNDER");
  lcd.setCursor(0,1);
  lcd.print("  VIPIN RAJ");
  delay(2500);
  lcd.clear();
}


void loop() {

  int prox = digitalRead(2);
  if(prox == LOW){
   // delay(300);
  //lcd.clear();
  
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
   
    previousMillis = currentMillis;   
    
    temperature_read = thermocouple.readCelsius();
    lcd.setCursor(0,1);
    lcd.print("STANDBY MODE    ");
     digitalWrite(6,HIGH);
    
    if(temperature_read > 50){
      analogWrite(5,225);
      lcd.setCursor(0,1);
      
      lcd.print("COOLING MODE    ");
      digitalWrite(8,HIGH);
       digitalWrite(6,LOW);
      
    }else{
      analogWrite(5,0);
       digitalWrite(8,LOW);
      
    }
     set_temperature = analogRead(A1);
    set_temperature = constrain(set_temperature,20,480); 
    val = analogRead(A2);
  
    val=constrain(val,0,200);
    x = val*99/200;
    analogWrite(3,0);
      lcd.setCursor(0,0);
    lcd.print("SET- ");
    lcd.print("T:");
  
    lcd.print(set_temperature);
    lcd.print(" FS:");
    lcd.print(x);
     lcd.print("  ");
      digitalWrite(7,LOW);  
  
  }
  }
  if(prox == HIGH){
    if(x>4){
   digitalWrite(8,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
 // First we read the real value of temperature
  temperature_read = thermocouple.readCelsius();  //get the real temperature in Celsius degrees
  //Next we calculate the error between the setpoint and the real value
  PID_error = set_temperature - temperature_read;
  //Calculate the P value
  PID_p = kp * PID_error;
  //Calculate the I value in a range on +-3
  if(-3 < PID_error <3)
  {
    PID_i = PID_i + (ki * PID_error);
  }

  //For derivative we need real time to calculate speed change rate
  timePrev = Time;                            // the previous time is stored before the actual time read
  Time = millis();                            // actual time read
  elapsedTime = (Time - timePrev) / 1000; 
  //Now we can calculate the D calue
  PID_d = kd*((PID_error - previous_error)/elapsedTime);
  //Final total PID value is the sum of P + I + D
  PID_value = PID_p + PID_i + PID_d;

  //We define PWM range between 0 and 255
  if(PID_value < 0)
  {    PID_value = 0;    }
  if(PID_value > 255)  
  {    PID_value = 225;  }
  //Now we can write the PWM signal to the mosfet on digital pin D3
  analogWrite(PWM_pin,PID_value);
  previous_error = PID_error;     //Remember to store the previous error for next loop.

  delay(130);
  //lcd.clear();
  
  //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SET- ");
    lcd.print("T:");
    //lcd.setCursor(5,0);
    lcd.print(set_temperature);
    lcd.print(" FS:");
    lcd.print(x);
    lcd.print("  ");
    lcd.setCursor(0,1);
    lcd.print("OUT- ");
    lcd.print("T:");
    //lcd.setCursor(11,1);
    lcd.print(temperature_read);
    lcd.print("C");
    lcd.print("   ");
    set_temperature = analogRead(A1);
    set_temperature = constrain(set_temperature,20,480); 
    val = analogRead(A2);
    
    val=constrain(val,0,225);
x = val*99/225;
    val=val/10;
    analogWrite(5,val);
    
}
if(x<4){
  analogWrite(3,0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ERROR:");
  lcd.setCursor(0,1);
  lcd.print("FAN SPEED LOW");
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  temperature_read = thermocouple.readCelsius();
  
  if(temperature_read > 50){
      analogWrite(5,225);
  }else{
    analogWrite(5,0);
  }
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
   val = analogRead(A2);
    
    val=constrain(val,0,225);
    x = val*99/225;
    delay(300);
}

}

}
