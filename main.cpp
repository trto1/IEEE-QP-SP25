#include <Wire.h>
#include <DS3231.h>

//Global constants
#define SEC_IN_HOUR 3600;
#define MAX_HUNGER = 4;
#define MIN_HUNGER = 0;

#define PET_LEFT 30 // box coordinates for the pet (so we can do idle animation)
#define PET_RIGHT 40
#define PET_TOP 50
#define PET_BOTTOM 20

#define HUNGER_LEFT 5 // box coord. for the first heart of hunger bar
#define HUNGER_RIGHT 10
#define HUNGER_TOP 100
#define HUNGER_BOTTOM 90
#define HEART_DISTANCE HUNGER_RIGHT - HUNGER_LEFT

//==============================================

//Global variables
int now = 0;
int lastFedTime = 0;
DS3231 clock;

int hunger = 4;
//==============================================

void setup() {
    //Starting Arduino Communication
    Serial.begin(9600);
    EEPROM.begin();
    if (EEPROM_STARTED) { //aka its not the first time, this is a one-time check
        EEPROM.read (savedHunger, hunger); //the savedHunger might be an address
        EEPROM.read (savedLastFedTime, lastFedTime);
    }
    else {
        welcomeUser(); //just prints a welcome user line and mark eeprom as intialized somehow; might also need to deal with some variables
        //we might be able to add name for the pet if we have time
    }

    // Initializing the LCD Screen
    Config_Init();
    LCD_Init();
    LCD_Clear(WHITE);
    LCD_SetBacklight(100);
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
    Paint_Clear(WHITE);
    Paint_SetRotate(180);

    // Initializing the clock
    Serial.println("Initialize DS3231");;
    clock.begin();
    clock.setDateTime(2025, 5, 16, 4, 20, 0); // Year, Month, Day, Hour, Minute, Second

    //Draw Pet
    drawPet();
    //Deduct Hunger
    deductHunger();
    //Draw Hearts
    drawHungerBar();
}

void loop () {
    idleAnimationPet();
    handleInputs();
    deductHunger();
    if (shutdown) { //this might be a button select thing idk yet
        EEPROM.update (address, valueOfHunger);
        EEPROM.update (address, valueOfLastFedTime);
    }
}



//==============================================

//Button Inputs

void handleInputs () {
    
}

//==============================================

//Clock stuff

void getTime (int& globalTime) {
    globalTime = clock.getDateTime().unixtime;
}

int timePassedInHours () {
    int secondsPassed = now - lastFedTime;
    int hoursPassed = secondsPassed / SEC_IN_HOUR;
    return hoursPassed;
}

//==============================================

// Pet

void drawPet () {
    return;
}

void drawPet2ndState () {
    return;
}

void idleAnimationPet () {
    drawPet();
    Paint_DrawRectangle (PET_LEFT, PET_TOP, PET_RIGHT, PET_BOTTOM, WHITE, DRAW_FILL_FULL); //erase pet in its first state to look like its moving back and forth
    drawPet2ndState();
    Paint_DrawRectangle (); //erase pet in second stage (w/ updated coordinates)
}

//==============================================

//Hunger Bar

void deductHunger () { 
  int hoursPassed = timePassedInHours();
  if (hoursPassed == 0) { //repetitive, but we're running this in a while loop so just ends it early if there's no change in heart
    return;
  }

  int hungerLeft = hunger - (hoursPassed / 3);
  if (hungerLeft < 0) {
    hunger = 0;
    petIsDead ();
  }
  else {
    hunger = hungerLeft;
    getTime (lastFedTime); //this only resets if at least one heart is deducted
    eraseHeartHunger();
  }
}

void drawHungerBar () {
    if (hunger == 0) {
        return;
    }
    for (int i = 1; i <= hunger; i++) {
        addHeartHunger (i);
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
    addHeartHunger (hunger);
  }
  return;
}

void addHeartHunger (int whichHeart) {
    int heartNumber = whichHeart - 1;
    int centerX = (HUNGER_LEFT + HUNGER_RIGHT) / 2 + (HEART_DISTANCE*heartNumber);
    int centerY = (HUNGER_TOP + HUNGER_BOTTOM) / 2 + (HEART_DISTANCE*heartNumber);
    int radius = something();

    Paint_DrawCircle (centerX, centerY, radius, color, DRAW_FILL_FULL); //left and right top arc
    Paint_DrawCircle (); 
    Paint_DrawLine (); //the bottom triangle lines
    Paint_DrawLine();
}

void eraseHeartHunger (int whichHeart) {
    int heartNumber = whichHeart - 1;
    Paint_DrawRectangle (HUNGER_LEFT + (HEART_DISTANCE*heartNumber), HUNGER_TOP + (HEART_DISTANCE*heartNumber), HUNGER_RIGHT + (HEART_DISTANCE*heartNumber), HUNGER_BOTTOM + (HEART_DISTANCE*heartNumber), WHITE, DRAW_FILL_FULL);
}

void petIsDead () {
    Paint_Clear(WHITE);
    Paint_DrawString_EN(x, y, "Pet starved and died", &FontXX, color_background, color_foreground);
    delay (2000);
    Paint_Clear(WHITE);
    Paint_DrawString_EN(x, y, "Restarting the game...", &FontXX, color_background, color_foreground);

    //reset variables
    getTime (lastFedTime);
    hunger = 4;

    drawPet();
    drawHungerBar();
}
//==============================================

