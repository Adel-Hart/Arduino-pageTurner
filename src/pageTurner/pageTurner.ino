#include <BleKeyboard.h>

const int timeInterval = 500;

const int statusLed = 14; //status led pin 
const int btn_pageNext = 4;
const int btn_pagePrev = 2;
/**
 * this keys are illustrated in arduino "keyboard" library.
 * check them out on this site.
 * https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
 * 
 * 
 * i use app "ScorePDF" on ipad os.
 * this app's protocol follow this on below
 * --------
 * pageUp, leftArrowKey, upArrowKey -> move prev page.
 * pageDown, rightArrowKey, downArrowKey -> move next page.
 * 
 * source : https://enoiu.com/en/app/scorepdf/
 * --------
 * 
 * 
 * 
 * led status on below
 * ---------
 * blinking fast -> not connected
 * off -> connected
 * blink once -> pressed
 * ---------
 *  - dev -
 */



BleKeyboard bleKeyBoard("TurnerPedal", "OK-d", 100);

int criteriaTime = 0;



void setup(){
  
  pinMode(statusLed, OUTPUT);
  
  bleKeyBoard.begin();
  Serial.begin(115200);

  criteriaTime = millis();
 }

 
void turnNext(){ //send a command means "pageDown"
  bleKeyBoard.write(KEY_PAGE_DOWN);  
}

void turnPrev(){ //send a command means "pageUp"
  bleKeyBoard.write(KEY_PAGE_UP );
}

void led_blinking(){ //blinking led while waitng connect, !! use delay 1000ms(1s) !!
  digitalWrite(statusLed, HIGH);
  delay(500);
  digitalWrite(statusLed, LOW);
  delay(500);
}

void led_pop(){ //blink led once for display pressed, !! use delay 100ms (0.1s) !!
  digitalWrite(statusLed, HIGH);
  delay(100);
  digitalWrite(statusLed, LOW);
}





void loop(){
  
  while(!bleKeyBoard.isConnected()){
    led_blinking();
  } //loop while connected, function "blinking" delays 1000ms (1s)

  if(millis() >= criteriaTime + timeInterval){

    
    if(digitalRead(btn_pageNext)){
      Serial.println("next");
      turnNext();
      led_pop();
      criteriaTime = millis();
    }
    else if(digitalRead(btn_pagePrev)){
      Serial.println("Prev");
      turnPrev();
      led_pop();
      criteriaTime = millis();
      }

      
  }
  
}
