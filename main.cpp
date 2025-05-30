#include <Wire.h>
#include <DS3231.h>
#include <EEPROM.h>
#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"

//Global constants
#define SEC_IN_HOUR 3600
#define MAX_HUNGER 4
#define MIN_HUNGER 0

#define ADDR_HUNGER 0
#define ADDR_LASTFED 4 // store lastFedTime as 4-byte int

// #define PET_LEFT 30 // box coordinates for the pet (so we can do idle animation)
// #define PET_RIGHT 40
// #define PET_TOP 50
// #define PET_BOTTOM 20

// #define HUNGER_LEFT 5 // box coord. for the first heart of hunger bar
// #define HUNGER_RIGHT 10
// #define HUNGER_TOP 100
// #define HUNGER_BOTTOM 90
// #define HEART_DISTANCE HUNGER_RIGHT - HUNGER_LEFT

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
    if (EEPROM.read(100) == 1) { //aka its not the first time, this is a one-time check
        EEPROM.get (ADDR_HUNGER, hunger); 
        EEPROM.get(ADDR_LASTFED, lastFedTime);
    }
    else {
        welcomeUser(); //just prints a welcome user line and mark eeprom as intialized somehow; might also need to deal with some variables
        hunger = MAX_HUNGER;
        getTime(lastFedTime);
        EEPROM.put(ADDR_HUNGER, hunger);
        EEPROM.put(ADDR_LASTFED, lastFedTime);
        EEPROM.write(100, 1); // initialization flag
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
    if (digitalRead(FEED_BUTTON_PIN) == LOW) {
        feedPet();
        delay(500);
    }
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
    //// Head
    Paint_DrawCircle(80, 150, 40, BLUE, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawCircle(80, 150, 40, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    // Eyes
    Paint_DrawCircle(65, 140, 5, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawCircle(95, 140, 5, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    // Smile (just a line or arc – here, a line smile)
    Paint_DrawLine(65, 165, 95, 165, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
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
    int cx = (HUNGER_LEFT + HUNGER_RIGHT) / 2 + (HEART_DISTANCE * heartNumber);
    int cy = (HUNGER_TOP + HUNGER_BOTTOM) / 2;
    eraseHeartHunger (cx, cy, 1);
  }
}

void drawHungerBar() {
    if (hunger == 0) return;
    for (int i = 1; i <= hunger; i++) {
        int heartNumber = i - 1;
        int cx = (HUNGER_LEFT + HUNGER_RIGHT) / 2 + (HEART_DISTANCE * heartNumber);
        int cy = (HUNGER_TOP + HUNGER_BOTTOM) / 2;
        addHeartHunger(cx, cy, 1);
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

    int heartNumber = hunger - 1;
    int cx = (HUNGER_LEFT + HUNGER_RIGHT) / 2 + (HEART_DISTANCE * heartNumber);
    int cy = (HUNGER_TOP + HUNGER_BOTTOM) / 2;
    addHeartHunger(cx, cy, 1);
  }
  return;
}

void addHeartHunger (int cx, int cy, int scale) {
    const int N = 120;      // number of segments around the heart
    int x_prev = 0, y_prev = 0;
    int x_curr = 0, y_curr = 0;

    for (int i = 0; i <= N; i++) {
        float t = 2 * PI * i / N;
        // Parametric heart curve:
        float hx = 16 * pow(sin(t), 3);
        float hy = 13 * cos(t)
                 - 5 * cos(2 * t)
                 - 2 * cos(3 * t)
                 -     cos(4 * t);

        // Scale and translate into pixel coordinates
        x_curr = cx + int(hx * scale);
        y_curr = cy - int(hy * scale);

        if (i > 0) {
            Paint_DrawLine(
                x_prev, y_prev,
                x_curr, y_curr,
                RED,
                DOT_PIXEL_1X1,
                LINE_STYLE_SOLID
            );
        }

        x_prev = x_curr;
        y_prev = y_curr;
    }

}

void eraseHeartHunger(int cx, int cy, int scale) {
    const int N = 120;  // Number of points around the heart
    int px[N + 1], py[N + 1];

    // Generate points along the heart shape
    for (int i = 0; i <= N; i++) {
        float t = 2 * PI * i / N;
        float hx = 16 * pow(sin(t), 3);
        float hy = 13 * cos(t) - 5 * cos(2 * t)
                 - 2 * cos(3 * t) - cos(4 * t);
        px[i] = cx + int(hx * scale);
        py[i] = cy - int(hy * scale);
    }

    // Erase heart by redrawing in background color (e.g., WHITE)
    for (int i = 1; i <= N; i++) {
        Paint_DrawLine(cx, cy, px[i - 1], py[i - 1], WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
        Paint_DrawLine(cx, cy, px[i], py[i], WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
        Paint_DrawLine(px[i - 1], py[i - 1], px[i], py[i], WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    }
}

void petIsDead() {
    Paint_Clear(WHITE);
    Paint_DrawString_EN(10, 50, "Pet starved and died", &Font16, WHITE, RED);
    delay(2000);
    Paint_Clear(WHITE);
    Paint_DrawString_EN(10, 50, "Restarting the game...", &Font16, WHITE, BLACK);
    delay(2000);

    getTime(lastFedTime);
    hunger = MAX_HUNGER;

    drawPet();
    drawHungerBar();
}

