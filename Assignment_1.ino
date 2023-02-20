//LED variables
int led1 = 6;
boolean led1Val = false;

int led2 = 5;
boolean led2Val = false;

//button variables
int button1 = 4;
boolean button1Val;

int button2 = 3;
boolean button2Val;

//comparison variables
boolean compare1 = false;
boolean compare2 = true; //set to true so that LED2 will keep blinking unless the button is pressed and held 

//blinking-related variables
unsigned long currentTime;
int blinkRate = 700;
unsigned long lastChange;
boolean isBlinking = false;

//variables for LED1 to turn off after a certain amount of time
unsigned long savedTime;
int timer = 30000; 
boolean turnOn = false;

void setup() {
  //Open serial port
  Serial.begin(9600);

  //Setting LED pin modes
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  //Setting button pin modes
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
}

void loop() {
  //Set currentTime variable to millis()
  currentTime = millis();
  
  //Defining the button value variables
  button1Val = digitalRead(button1);
  button2Val = digitalRead(button2);

  //Linking the button value to the LED value
  if(button1Val == compare1 && button2Val != compare2){   //second comparison is to make sure button1 only works if LED2 is not blinking
    turnOn = true;
    savedTime = currentTime;
  }

  if(button2Val == compare2){
    isBlinking = true;
  }else{
    isBlinking = false;
    //Make sure that when the blinking stops, the LED turns OFF instead of having a chance to stay either ON or OFF
    led2Val = false;
  }

  //Setting the blinking mechanism
  if(currentTime-lastChange >= blinkRate && isBlinking == true){
    led2Val = !led2Val;
    lastChange = currentTime;
  }

  //Setting the timed turn-off action for LED1
  if(currentTime-savedTime <= timer && turnOn == true){
    led1Val = true;
  }else{
    led1Val = false;
  }
  
  //Linking the LED value variables with the correct pins
  digitalWrite(led1, led1Val);
  digitalWrite(led2, led2Val);
}
