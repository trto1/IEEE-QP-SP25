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
    // Initializing the LCD Screen
    Config_Init();
    LCD_Init();
    LCD_Clear(WHITE);
    LCD_SetBacklight(100);
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
    Paint_Clear(WHITE);
    Paint_SetRotate(180);

    // Initializing the clock
    Serial.begin(9600);
    Serial.println("Initialize DS3231");;
    clock.begin();
    // Manual (Year, Month, Day, Hour, Minute, Second)
    clock.setDateTime(2025, 5, 16, 4, 20, 0);

    //Draw Pet
    drawPet();
    //Draw Hearts
    drawHungerBar();
}





void loop () {
    handleInputs();
}



//==============================================

//Button Inputs

void handleInputs () {
    
}

//==============================================

//Clock stuff

/** 
 * Get the current time
 * @param: globalTime refers to which global variable to update,
 *         now or lastFeedTime
*/
void getTime (int& globalTime) {
    globalTime = clock.getDateTime().unixtime;
}

int timePassedInHours () {
    int secondsPassed = now - lastFedTime;
    int hoursPassed = secondsPassed / SEC_IN_HOUR;
    return hoursPassed;
}

//==============================================

//Hunger Bar
void drawHungerBar () {
    if (hunger == 0) {
        return;
    }
    for (int i = 1; i <= hunger; i++) {
        addHeart (i);
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

void addHeart (int whichHeart) {
    int heartNumber = whichHeart - 1;
    int centerX = (HUNGER_LEFT + HUNGER_RIGHT) / 2 + (HEART_DISTANCE*heartNumber);
    int centerY = (HUNGER_TOP + HUNGER_BOTTOM) / 2 + (HEART_DISTANCE*heartNumber);
    int radius = something();

    Paint_DrawCircle (centerX, centerY, radius, color, DRAW_FILL_FULL); //left and right top arc
    Paint_DrawCircle (); 
    Paint_DrawLine (); //the bottom triangle lines
    Paint_DrawLine();
}

void eraseHeart (int whichHeart) {
    int heartNumber = whichHeart - 1;
    Paint_DrawRectangle(HUNGER_LEFT + (HEART_DISTANCE*heartNumber), HUNGER_TOP + (HEART_DISTANCE*heartNumber), HUNGER_RIGHT + (HEART_DISTANCE*heartNumber), HUNGER_BOTTOM + (HEART_DISTANCE*heartNumber), WHITE, DRAW_FILL_FULL);
}
//==============================================

