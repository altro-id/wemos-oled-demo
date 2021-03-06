#include <Wire.h>  // Include Wire if you're using I2C
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library


#define PIN_RESET 255  //
#define DC_JUMPER 0  // I2C Addres: 0 - 0x3C, 1 - 0x3D

//////////////////////////////////
// MicroOLED Object Declaration //
//////////////////////////////////

MicroOLED oled(PIN_RESET, DC_JUMPER);  // I2C Example

/////////////////////////////////////////////
/////  Display CLOCK Declaration  ///////////
////////////////////////////////////////////

// Use these variables to set the initial time
int hours = 11;
int minutes = 50;
int seconds = 30;

unsigned long count=0;

// How fast do you want the clock to spin? Set this to 1 for fun.
// Set this to 1000 to get _about_ 1 second timing.
const int CLOCK_SPEED = 1000;

// Global variables to help draw the clock face:
const int MIDDLE_Y = oled.getLCDHeight() / 2;
const int MIDDLE_X = oled.getLCDWidth() / 2;

int CLOCK_RADIUS;
int POS_12_X, POS_12_Y;
int POS_3_X, POS_3_Y;
int POS_6_X, POS_6_Y;
int POS_9_X, POS_9_Y;
int S_LENGTH;
int M_LENGTH;
int H_LENGTH;

unsigned long lastDraw = 0;

void initClockVariables()
{
  // Calculate constants for clock face component positions:
  oled.setFontType(0);
  CLOCK_RADIUS = min(MIDDLE_X, MIDDLE_Y) - 1;
  POS_12_X = MIDDLE_X - oled.getFontWidth();
  POS_12_Y = MIDDLE_Y - CLOCK_RADIUS + 2;
  POS_3_X  = MIDDLE_X + CLOCK_RADIUS - oled.getFontWidth() - 1;
  POS_3_Y  = MIDDLE_Y - oled.getFontHeight() / 2;
  POS_6_X  = MIDDLE_X - oled.getFontWidth() / 2;
  POS_6_Y  = MIDDLE_Y + CLOCK_RADIUS - oled.getFontHeight() - 1;
  POS_9_X  = MIDDLE_X - CLOCK_RADIUS + oled.getFontWidth() - 2;
  POS_9_Y  = MIDDLE_Y - oled.getFontHeight() / 2;

  // Calculate clock arm lengths
  S_LENGTH = CLOCK_RADIUS - 2;
  M_LENGTH = S_LENGTH * 0.7;
  H_LENGTH = S_LENGTH * 0.5;
}


/////////////////////////////////////////////
/////  Display CUBE Declaration  ///////////
////////////////////////////////////////////

int SCREEN_WIDTH = oled.getLCDWidth();
int SCREEN_HEIGHT = oled.getLCDHeight();

float d = 3;
float px[] = { 
  -d,  d,  d, -d, -d,  d,  d, -d };
float py[] = { 
  -d, -d,  d,  d, -d, -d,  d,  d };
float pz[] = { 
  -d, -d, -d, -d,  d,  d,  d,  d };

float p2x[] = {
  0,0,0,0,0,0,0,0};
float p2y[] = {
  0,0,0,0,0,0,0,0};

float r[] = {
  0,0,0};

#define SHAPE_SIZE 600
// Define how fast the cube rotates. Smaller numbers are faster.
// This is the number of ms between draws.
#define ROTATION_SPEED 0

unsigned long previousMillis; //millis for timer 


/////////////////////////////////////////////
/////  Binary for Bitmap image /////////////
///////////   Altro Logo  /////////////////
//////////////////////////////////////////


//------------------------------------------------------------------------------
// File generated by LCD Assistant
// http://en.radzio.dxp.pl/bitmap_converter/
//------------------------------------------------------------------------------
//This is the array that holds the Bitmap image. The easiest way to convert a bmp
//to an array is to use the LCD Assistant linked above. 


uint8_t altro [] = {
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x01, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0x89, 0x09,
0xFF, 0x41, 0x41, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xF9, 0xF9, 0xF9, 0xF9, 0x09,
0x09, 0xF9, 0xF9, 0xF9, 0xFB, 0x03, 0x01, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0x41, 0x41, 0xFF,
0x01, 0x79, 0x79, 0x79, 0x79, 0x79, 0x79, 0x01, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFF,
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};


// Use these variables to set the initial time
void setup()
{
  oled.begin();     // Initialize the OLED
  oled.clear(PAGE); // Clear the display's internal memory
  oled.clear(ALL);  // Clear the library's display buffer
  oled.display();   // Display what's in the buffer (splashscreen)

  initClockVariables();  //call declaration clock display
}

void loop()
{
  //typing word  "WEMOS OLED DEMO by ALTRO"
  oled.setFontType(0);  // Set font to type 0
  oled.clear(PAGE);     // Clear the page
  oled.setCursor(0, 15); // Set cursor to top-left
  oled.print("WEMOS OLED   DEMO    by ALTRO");
  oled.display();
  delay(5000);

  //typing word  "Clock Demo"
  oled.clear(ALL);     // Clear the page
  oled.clear(PAGE);     // Clear the page
  oled.setCursor(10, 15); // Set cursor to top-left
  oled.print("CLOCK      DEMO");
  oled.display();
  delay(2000);
  
  //Display clock for 10s
  oled.clear(ALL);
  oled.clear(PAGE);     // Clear the page
  drawFace();
  drawArms(hours, minutes, seconds);
  oled.display(); // display the memory buffer drawn
  while (count <=10){
    if (lastDraw + CLOCK_SPEED < millis())
    {
      lastDraw = millis();
      // Add a second, update minutes/hours if necessary:
      updateTime();

      // Draw the clock:
      oled.clear(PAGE);  // Clear the buffer
      drawFace();  // Draw the face to the buffer
      drawArms(hours, minutes, seconds);  // Draw arms to the buffer
      oled.display(); // Draw the memory buffer
     count++; 
    }
    delay(300);
  }
  count=0;

  //typing word  "Cube Demo"
  oled.clear(PAGE);     // Clear the page
  oled.setCursor(10, 15); // Set cursor to top-left
  oled.print("CUBE       DEMO");
  oled.display();
  delay(2000);

  
 //Display Cube 3D Rotate for 15s 
  previousMillis = millis();
  oled.clear(PAGE);     // Clear the page
  oled.display();
  while(millis() - previousMillis <= 15000) { 
  drawCube();
  delay(ROTATION_SPEED);
  }

  //typing word  "Bitmap Demo"
  oled.clear(ALL);     // Clear the page
  oled.clear(PAGE);     // Clear the page
  oled.setCursor(10, 15); // Set cursor to top-left
  oled.print("BITMAP       DEMO");
  oled.display();
  delay(2000);
  

  //Display drawing image Bitmap 
  oled.clear(ALL);//clear the screen before we draw our image
  oled.drawBitmap(altro);//call the drawBitmap function and pass it the array from above
  oled.display();//display the imgae 
  delay(4000);

  //Display sensor measurement
   previousMillis = millis();
   while(millis() - previousMillis <= 9000) { 
   float randNumber = random(0,9);
   float Temp = randNumber/10 + 27.0;
   unsigned char randNumber_hum = random(0,9);
   unsigned char Hum = randNumber_hum + 70;
   oled.clear(PAGE);     // Clear the page
   oled.setCursor(10, 0); // Set cursor to top-left
   oled.print("Sensor      Values");
   oled.setCursor(0, 28); // Set cursor to top-left
   oled.print("TEMP:");
   oled.print(Temp);
   oled.print("HUM:  ");
   oled.print(Hum);
   oled.print("%");
   
   oled.display();
   delay(500);
  }
}


/////////////////////////////////////////////
/////  Display Cube 3D function /////////////
////////////////////////////////////////////

void drawCube()
{
  r[0]=r[0]+PI/180.0; // Add a degree
  r[1]=r[1]+PI/180.0; // Add a degree
  r[2]=r[2]+PI/180.0; // Add a degree
  if (r[0] >= 360.0*PI/180.0) r[0] = 0;
  if (r[1] >= 360.0*PI/180.0) r[1] = 0;
  if (r[2] >= 360.0*PI/180.0) r[2] = 0;

  for (int i=0;i<8;i++)
  {
    float px2 = px[i];
    float py2 = cos(r[0])*py[i] - sin(r[0])*pz[i];
    float pz2 = sin(r[0])*py[i] + cos(r[0])*pz[i];

    float px3 = cos(r[1])*px2 + sin(r[1])*pz2;
    float py3 = py2;
    float pz3 = -sin(r[1])*px2 + cos(r[1])*pz2;

    float ax = cos(r[2])*px3 - sin(r[2])*py3;
    float ay = sin(r[2])*px3 + cos(r[2])*py3;
    float az = pz3-150;

    p2x[i] = SCREEN_WIDTH/2+ax*SHAPE_SIZE/az;
    p2y[i] = SCREEN_HEIGHT/2+ay*SHAPE_SIZE/az;
  }

  oled.clear(PAGE);
  for (int i=0;i<3;i++) 
  {
    oled.line(p2x[i],p2y[i],p2x[i+1],p2y[i+1]);
    oled.line(p2x[i+4],p2y[i+4],p2x[i+5],p2y[i+5]);
    oled.line(p2x[i],p2y[i],p2x[i+4],p2y[i+4]);
  }    
  oled.line(p2x[3],p2y[3],p2x[0],p2y[0]);
  oled.line(p2x[7],p2y[7],p2x[4],p2y[4]);
  oled.line(p2x[3],p2y[3],p2x[7],p2y[7]);
  oled.display();
}


/////////////////////////////////////////////
/////  Display Clock function //////////////
////////////////////////////////////////////

void updateTime()
{
  seconds++;  // Increment seconds
  if (seconds >= 60)  // If seconds overflows (>=60)
  {
    seconds = 0;  // Set seconds back to 0
    minutes++;    // Increment minutes
    if (minutes >= 60)  // If minutes overflows (>=60)
    {
      minutes = 0;  // Set minutes back to 0
      hours++;      // Increment hours
      if (hours >= 12)  // If hours overflows (>=12)
      {
        hours = 0;  // Set hours back to 0
      }
    }
  }
}

// Draw the clock's three arms: seconds, minutes, hours.
void drawArms(int h, int m, int s)
{
  double midHours;  // this will be used to slightly adjust the hour hand
  static int hx, hy, mx, my, sx, sy;

  // Adjust time to shift display 90 degrees ccw
  // this will turn the clock the same direction as text:
  h -= 3;
  m -= 15;
  s -= 15;
  if (h <= 0)
    h += 12;
  if (m < 0)
    m += 60;
  if (s < 0)
    s += 60;

  // Calculate and draw new lines:
  s = map(s, 0, 60, 0, 360);  // map the 0-60, to "360 degrees"
  sx = S_LENGTH * cos(PI * ((float)s) / 180);  // woo trig!
  sy = S_LENGTH * sin(PI * ((float)s) / 180);  // woo trig!
  // draw the second hand:
  oled.line(MIDDLE_X, MIDDLE_Y, MIDDLE_X + sx, MIDDLE_Y + sy);

  m = map(m, 0, 60, 0, 360);  // map the 0-60, to "360 degrees"
  mx = M_LENGTH * cos(PI * ((float)m) / 180);  // woo trig!
  my = M_LENGTH * sin(PI * ((float)m) / 180);  // woo trig!
  // draw the minute hand
  oled.line(MIDDLE_X, MIDDLE_Y, MIDDLE_X + mx, MIDDLE_Y + my);

  midHours = minutes / 12; // midHours is used to set the hours hand to middling levels between whole hours
  h *= 5;  // Get hours and midhours to the same scale
  h += midHours;  // add hours and midhours
  h = map(h, 0, 60, 0, 360);  // map the 0-60, to "360 degrees"
  hx = H_LENGTH * cos(PI * ((float)h) / 180);  // woo trig!
  hy = H_LENGTH * sin(PI * ((float)h) / 180);  // woo trig!
  // draw the hour hand:
  oled.line(MIDDLE_X, MIDDLE_Y, MIDDLE_X + hx, MIDDLE_Y + hy);
}

// Draw an analog clock face
void drawFace()
{
  // Draw the clock border
  oled.circle(MIDDLE_X, MIDDLE_Y, CLOCK_RADIUS);

  // Draw the clock numbers
  oled.setFontType(0); // set font type 0, please see declaration in SFE_MicroOLED.cpp
  oled.setCursor(POS_12_X, POS_12_Y); // points cursor to x=27 y=0
  oled.print(12);
  oled.setCursor(POS_6_X, POS_6_Y);
  oled.print(6);
  oled.setCursor(POS_9_X, POS_9_Y);
  oled.print(9);
  oled.setCursor(POS_3_X, POS_3_Y);
  oled.print(3);
}


