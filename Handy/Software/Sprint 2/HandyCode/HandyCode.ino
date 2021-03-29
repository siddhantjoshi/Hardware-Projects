// int duration, distance;
// digitalWrite(HCSR04_PIN_TRIG, LOW); 
// delay(2);
// digitalWrite(HCSR04_PIN_TRIG, HIGH); 
// delay(10);
// digitalWrite(HCSR04_PIN_TRIG, LOW);

// duration = pulseIn(HCSR04_PIN_ECHO, HIGH);
// distance = (duration/2) * 0.0343 ;
// if (distance >= 10 || distance <= 2 ) {

// digitalWrite(SOLENOIDVALVE1_PIN, LOW);
// digitalWrite(SOLENOIDVALVE2_PIN, LOW);

// Pin Definitions
#define waterSolonied  2
#define liquidSolonied  3
#define HCSR04_PIN_TRIG  5
#define HCSR04_PIN_ECHO 4
#define redLED 6

//Option Button
#define optionButton1 7
#define optionButton2 8
#define optionButton3 9

//Variable's decleared
int optionButton1State = 0, optionButton2State = 0, optionButton3State = 0;

// blink Red LED
void blinkLED(){
  digitalWrite(redLED, HIGH);
  delay(1000);
}

// detected Liquid
boolean liquidDetected(){
  return true;
}

// detected Water
boolean waterDetected(){
  return true;
}

// Solonied  for Water
void waterSoloniedON(int waterSolonieddelay){
  if(waterDetected()){
    digitalWrite(waterSolonied, HIGH);
    delay(waterSolonieddelay);
    digitalWrite(waterSolonied, LOW);
    return true;  
  }else{
    digitalWrite(liquidSolonied, LOW);
    digitalWrite(waterSolonied, LOW);
    return false;
  }
}

// Solonied  for Qiquid
void liquidSoloniedON(int liquidSolonieddelay){
  if(liquidDetected()){
    digitalWrite(liquidSolonied, HIGH);
    delay(liquidSolonieddelay);
    digitalWrite(liquidSolonied, LOW);  
  }else{
    digitalWrite(liquidSolonied, LOW);
    digitalWrite(waterSolonied, LOW);
    return false;
  }
}

// Detect Hand
boolean detectHand (){
  return true;  
}

void onlyWater(){
  waterSoloniedON(1000);
}
void onlyLiquid (){
  liquidSoloniedON(1000);
}
void liquidAndWater(){
  waterSoloniedON(1000);
  liquidSoloniedON(1000);
}

int optionChoiced(){
  
  optionButton1State = digitalRead(optionButton1);
  optionButton2State = digitalRead(optionButton2);
  optionButton3State = digitalRead(optionButton3);
  if(optionButton1State == HIGH ){
    return 1;
  }else if(optionButton2State == HIGH ){
    return 2;
  }else if(optionButton3State == HIGH ){
    return 3;
  }
}

void setup() {
  Serial.begin (9600);
  
  pinMode(liquidSolonied, OUTPUT);
  pinMode(waterSolonied, OUTPUT);
  pinMode(HCSR04_PIN_TRIG, OUTPUT);
  pinMode(HCSR04_PIN_ECHO, INPUT);
  pinMode(redLED, OUTPUT);
  
  pinMode(optionButton1, INPUT);
  pinMode(optionButton2, INPUT);
  pinMode(optionButton3, INPUT);
}

void loop() {

  if(detectHand()){
    switch(optionChoiced()){
      case 1:onlyWater();
      break;
      
      case 2:onlyLiquid();
      break;
      
      case 3:liquidAndWater();
      break;

      default: blinkLED();
    }
  }

}
