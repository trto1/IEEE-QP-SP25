// define HIGH and INPUT (maybe library constants?)
// include the libraries for digitalRead
// what's button1,2,3Pin??

const int button1Pin = 2;  // the number of the pushbutton pin

int button1State = 0;  // variable for reading the pushbutton status
void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(button1Pin, INPUT);
}
void loop() { 
  // read the state of the pushbutton value:
  button1State = digitalRead(button1Pin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (button1State == HIGH) {
    //make a beep sound here?
    if (feed == true) {
      feedPet();
    }
  } 
}

