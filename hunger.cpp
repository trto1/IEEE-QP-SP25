#include "SPI.h"
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"

void setup()
{
Config_Init();
LCD_Init();
LCD_Clear(WHITE);
LCD_SetBacklight(100);
Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
Paint_Clear(WHITE);
Paint_SetRotate(180);
// Head
Paint_DrawCircle(80, 80, 40, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);

// Eyes
Paint_DrawCircle(65, 70, 5, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);
Paint_DrawCircle(95, 70, 5, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);

// Smile (just a line or arc – here, a line smile)
Paint_DrawLine(65, 95, 95, 95, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
}

void timesetup(){
	
}
Code ZIP 
ANIMATING FACE (not finished and probably has errors)
#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"


void setup()
{
  Config_Init();
  LCD_Init();
  LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE);
Paint_SetRotate(180);
}


void drawLOGOS(){
  Paint_DrawLine(75,230,65,200, BLACK, DOT_PIXEL_2X2,LINE_STYLE_SOLID);
  Paint_DrawLine(75,230,85,200, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
  Paint_DrawCircle(65,190,10, RED, DOT_PIXEL_1X1, DRAW_FILL_FILL);
  Paint_DrawCircle(85,190,10, RED, DOT_PIXEL_1X1, DRAW_FILL_FILL);


}


void loop() {
  
}



//Hunger part
int hunger = 4; 





void loop(){
  //handleInputs () should realistically call and handle all of the changes with hunger
  handleInputs();
  //this is the code to save previous and other thing when user shut the machine down
  if (shutdown) {
    getTime (previous);
    saveHungerToEEPROM ();
  }
}


void Updatedisplay() {
  Paint_clear(WHITE);
  drawPet();          
  drawText();       
  drawHungerBar();   
  drawHappinessBar();
  LCD_Display(image);
}


void feedPet () {
  if (hunger >= MAX_HUNGER){
    Serial.println("Tamagotchi is already full!");
  }
  else {
    hunger++;
    Serial.println("Tamagotchi ate a meal!"); //this is for testing/tracking. once it works we can make this an actual air bubble on the display screen
    updateHungerBar ();
  }
  return;
}

void updateHungerBar () {
  // just add/remove hearts;
  // there should be a set of coordinates that we can set
  // for each bar, so that we dont have to 
  // erase everything and redraw
}