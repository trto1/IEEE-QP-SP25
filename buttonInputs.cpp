// define HIGH and INPUT (maybe library constants?)
// include the libraries for digitalRead
// what's button1,2,3Pin??

//Global variable
bool feed = false; //bool for selecting feed symbol

// constants won't change. They're used here to set pin numbers:
const int button1Pin = 2;  // the number of the pushbutton pin
const int button2Pin = 3;
const int button3Pin = 4;

// variables will change:
int button1State = 0;  // variable for reading the pushbutton status
int button2State = 0;
int button3State = 0;

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
}



// I think we can only have one void loop(), so this part needs to be merged with main.cpp
void loop() { 
  // read the state of the pushbutton value:
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (button1State == HIGH) { // next?
    // do whatever we want
  } else {
    // do other stuff
  }
  
  if (button2State == HIGH) {
    // do whatever we want
  } else {
    // do other stuff
  }
  
  if (button3State == HIGH) { //im assuming this is enter
    //make a beep sound here?
    if (feed == true) {
      feedPet();
    }
  } 
}

