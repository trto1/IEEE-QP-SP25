#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"

//Global constants
int HUNGER_FREQUENCY = 3;

//Global variable
int hunger = 4; 

void setup() {
  Config_Init();
  LCD_Init();
  LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE);
  Paint_SetRotate(180);

  deductHunger ();
}

void loop(){
  //handleInputs() should realistically call and handle all of the changes with hunger
  handleInputs();
  checkHunger(); 
  //this is the code to save previous and other thing when user shut the machine down
  if (shutdown) {
    saveHungerToEEPROM ();
    saveLastFedTimeToEEPROM ();
  }
}

void deductHunger () { //consider combine this with getHoursPassed if we can
  int hoursPassed = timePassedInHours();
  int hungerLeft = hunger - (hoursPassed / 3);
  if (hungerLeft < 0) {
    hunger = 0;
    PetISDead ();
  }
  else {
    hunger = hungerLeft
  }
}


void feedPet () {
  if (hunger >= MAX_HUNGER){
    Serial.println("Tamagotchi is already full!"); //this is for testing/tracking. once it works we can make this an actual air bubble on the display screen
  }
  else {
    hunger++;
    getTime (lastFedTime); //effectively resets the timer everytime the pet is fed
    Serial.println("Tamagotchi ate a meal!"); 
    addHeartsToHungerBar (hunger);
  }
  return;
}

void addHeartsToHungerBar () {
  // there should be a set of coordinates that we can set

  
}

