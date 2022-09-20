#include "BMP.h"
#include <cmath>
#include <iostream>

#define COLOR 255, 0, 0, 0

static BMP g_bmp(800, 800, false);

int GetWidth() { return g_bmp.bmp_info_header.width; }

int GetHeight() { return g_bmp.bmp_info_header.height; }

void SetPixel(uint32_t x0, uint32_t y0, uint8_t R, uint8_t G, uint8_t B,
              uint8_t A) {

  // Prevent boundary error
  if (x0 < 0 || y0 < 0 || x0 >= GetWidth() || y0 >= GetHeight()) {
    return;
  }

  g_bmp.set_pixel(x0, y0, B, G, R, A);
}

void FlipAndDraw(int originX, int originY, int x, int y) {
  SetPixel(originX + x, originY + y, COLOR);
  SetPixel(originX + x, originY - y, COLOR);
}

// Midpoint Ellipse algorithm based off of Geeks for Geeks example:
// https://www.geeksforgeeks.org/midpoint-ellipse-drawing-algorithm/
// Ellipse formula: 0 = b²x² + a²y² - a²b²
void MidpointEllipse(int centerX, int centerY, int a, int b) {
  int x = 0;
  int y = b;

  // START Region 1 -----------------------------------------------------------

  // Fig. 1: Prediction for region 1
  // p1 = f(x+1, y–0.5) // Plug in ellipse formula
  //    = b²(x+1)² + a²(y-0.5)² - a²b²
  //    = b²(x² + 2x + 1) + a²(y² - y + 0.25) - a²b²

  // Since x=0 and y=b formula can be rewritten as:
  // p1 = b²(0 + 0 + 1) + a²(b² - b + 0.25) - a²b²
  //    = b² + a²b² - a²b + a²0.25 - a²b²
  //    = b² - a²b + a²0.25
  int p1 = (b * b) - (a * a * b) + (a * a * 0.25);

  // Slope of ellipse (from
  // https://www.includehelp.com/computer-graphics/mid-point-ellipse-algorithm.aspx)
  // dx/dy = - (2b²x / 2a²y ) = -1
  int dx = 2 * b * b * x; // Numerator of slope
  int dy = 2 * a * a * y; // Denominator of slope

  while (dx < dy) {
    // Loop until the end of region 1 (slope is -1)
    FlipAndDraw(centerX, centerY, x, y);

    if (p1 < 0) {
      // (x,y) is inside of ellipse. Draw East pixel.
      x++;

      dx = 2 * b * b * x; // Update slope numerator

      // p1 + b²(2x+3) = p1 + 2b²x - 3b² = p1 + dx + 3b²
      p1 = p1 + dx + (3 * b * b); // Update prediction

    } else {
      // (x,y) is outside the ellipse. Draw SouthEast pixel.
      x++;
      y--;

      dx = 2 * b * b * x; // Update slope numerator
      dy = 2 * a * a * y; // Update slope denominator

      p1 = p1 + dx - dy + (b * b); // Update prediction
    }
  }
  // END Region 1   -----------------------------------------------------------

  // START Region 2 -----------------------------------------------------------

  // Prediction for region 2
  // p2 = f(x+0.5, y-1)
  //    = b²(x+0.5)² + a²(y-1)² - a²b²
  int p2 = ((b * b) * ((x + 0.5) * (x + 0.5))) +
           ((a * a) * ((y - 1) * (y - 1))) - (a * a * b * b);

  while (y >= 0) {
    // Region 2 ends when Y hits the x-axis
    FlipAndDraw(centerX, centerY, x, y);

    if (p2 > 0) {
      // (x,y) is outside of the ellipse. Draw south pixel.

      // Increment south
      y--;

      dy = 2 * a * a * y;     // Update slope denominator
      p2 = p2 + (a * a) - dy; // Update prediction

    } else {

      // Increment southeast
      y--;
      x++;

      dx = 2 * b * b * x;          // Update slope numerator
      dy = 2 * a * a * y;          // Update slope denominator
      p2 = p2 + dx - dy + (a * a); // Update prediction
    }
  }
  // END Region 2   -----------------------------------------------------------
}

int main() {
  g_bmp.fill_region(0, 0, 800, 800, 0, 0, 0, 0);
  int ra = 12 * 64;
  int rb = 6 * 64;
  MidpointEllipse(0, 400, ra, rb);
  g_bmp.write("output.bmp");
}
