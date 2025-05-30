#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"

#define SEC_IN_HOUR 3600
#define MAX_HUNGER 4
#define MIN_HUNGER 0

#define ADDR_HUNGER 0
#define ADDR_LASTFED 4 // store lastFedTime as 4-byte int


void setup()
{
  Config_Init();
  LCD_Init();
  LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE);
  Paint_SetRotate(180);
  //// Head
  Paint_DrawCircle(80, 150, 40, BLUE, DOT_PIXEL_2X2, DRAW_FILL_FULL);
  Paint_DrawCircle(80, 150, 40, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
  
  // Eyes
  Paint_DrawCircle(65, 140, 5, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);
  Paint_DrawCircle(95, 140, 5, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);
  
  // Smile (just a line or arc – here, a line smile)
  Paint_DrawLine(65, 165, 95, 165, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
  
  Draw_Heart(30, 45, 1);
  Draw_Heart(65, 45, 1);
  Draw_Heart(100, 45, 1);
  Draw_Heart(135, 45, 1);
  Paint_DrawString_EN(30, 5, "HUNGER", &Font24, WHITE, BLACK);

}


void loop()
{
  int startX = 150;               // Original X position of head center
  int amplitude = 90;            // Max distance to move left/right
  unsigned long duration = 7000; // Total animation time in milliseconds
  unsigned long startTime = millis();

  while (millis() - startTime < duration) {
    // Calculate elapsed time and normalized progress (0 to 1)
    unsigned long elapsed = millis() - startTime;
    float t = (float)elapsed / duration;

    // Calculate position using sine wave (smooth back-and-forth motion)
    float angle = t * 2 * PI; // One full oscillation over 7s
    int offsetX = amplitude * sin(angle);
    int x = startX + offsetX;

    // Clear previous frame
    Paint_Clear(WHITE);

    // Draw character at new X position
    // Head
    Paint_DrawCircle(x, 150, 40, BLUE, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawCircle(x, 150, 40, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);

    // Eyes
    Paint_DrawCircle(x - 15, 140, 5, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawCircle(x + 15, 140, 5, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);

    // Smile
    Paint_DrawLine(x - 15, 165, x + 15, 165, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

    // Refresh screen with the new image
    //LCD_2IN_Display(paint_image);

    // Short delay for smoother animation
   // 
  Draw_Heart(30, 45, 1);
  Draw_Heart(65, 45, 1);
  Draw_Heart(100, 45, 1);
  Draw_Heart(135, 45, 1);

  Erase_Heart(30,45,1);
  
  Paint_DrawString_EN(30, 5, "HUNGER", &Font24, WHITE, BLACK);
  //delay(750);
  }
  
}

void drawHeart(int cx, int cy, int scale) {
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


    // Fill heart using triangle fan from the center
    for (int i = 1; i <= N; i++) {
        Paint_DrawLine(cx, cy, px[i - 1], py[i - 1], RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
        Paint_DrawLine(cx, cy, px[i], py[i], RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
        Paint_DrawLine(px[i - 1], py[i - 1], px[i], py[i], RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    }
}

void dead(){
    //// Head
    Paint_DrawCircle(80, 150, 40, BLUE, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawCircle(80, 150, 40, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);

// Eyes
Paint_DrawLine(75, 155, 55, 135, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
Paint_DrawLine(105, 155, 85, 135, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
Paint_DrawLine(75, 135, 55, 155, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
Paint_DrawLine(105, 135, 85, 155, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

// Smile (just a line or arc – here, a line smile)
Paint_DrawLine(65, 165, 95, 165, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

}
void Erase_Heart(int cx, int cy, int scale) {
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


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
