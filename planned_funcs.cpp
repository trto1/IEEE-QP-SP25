
// void checkHunger(){
//   if (hunger <= MIN_HUNGER && !isBeeping) {
//     beepAlert();
//   } 
//   else if (hunger > 0 && isBeeping) {
//     stopBeep();
//   }
// }

//======================================================================

// drawing a smiley face?
// if (toggle) {
//     // Head
//     Paint_DrawCircle(80, 80, 40, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);


//     // Eyes
//     Paint_DrawCircle(65, 70, 5, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);
//     Paint_DrawCircle(95, 70, 5, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);


//     // Smile (just a line or arc – here, a line smile)
//     Paint_DrawLine(65, 95, 95, 95, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
//   }
//   else {
//     //HEAD
//     Paint_DrawCircle(85,80,40, Black, DOT_PIXEL_2x2, DRAW_FILL_EMPTY);
//     //eyes
//     Paint_DrawCircle(70,70,5, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
//     Paint_DrawCircle(100,70,5, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
//     //MOUTH
//     Paint_DrawCircle(85,100,10, DOT_PIXEL_2X2, DRAW_FILL_FULL);
//     Paint_DrawCircle(85,100,10, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
//   }
//   LCD_Display();
//   toggle = !toggle;
//   delay(1000);

//======================================================================

// void Updatedisplay() {
//   Paint_clear(WHITE);
//   drawPet();          
//   drawText();       
//   drawHungerBar();   
//   drawHappinessBar();
//   LCD_Display(image);
// }