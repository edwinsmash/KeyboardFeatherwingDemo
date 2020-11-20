#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include <BBQ10Keyboard.h>
#include <Adafruit_NeoPixel.h>

//Adafruit M4 Feather specific pins
#define VBATPIN A6
#define ONBOARD_PIXEL_PIN 8
#define FEATHERWING_PIXEL_PIN 11

//Neopixels
Adafruit_NeoPixel onboard_pixel(1, ONBOARD_PIXEL_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel fw_pixel(1, FEATHERWING_PIXEL_PIN, NEO_GRB + NEO_KHZ800);

//Display Settings
//Display is X=320, Y=240
#define TFT_CS 9
#define TFT_DC 10
Adafruit_ILI9341 tft(TFT_CS, TFT_DC);

BBQ10Keyboard keyboard;

char read_next_key()
{
  while (keyboard.keyCount() == 0)
  {
    ;
  }
  const BBQ10Keyboard::KeyEvent key = keyboard.keyEvent();
  if (key.state == BBQ10Keyboard::StatePress)
  {
    char c = key.key;
    Serial.print("(Function:    ");
    Serial.print(c);
    Serial.print("    ");
    Serial.print(c, HEX);
    Serial.println(")");
    return c;
  }
}

void button_1()
{
  char key_pressed = read_next_key();
  Serial.print("Button 1 Function:    ");
  Serial.print(key_pressed);
  Serial.print("    ");
  Serial.println(key_pressed, HEX);
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    fw_pixel.begin();
    fw_pixel.setBrightness(8);
    fw_pixel.setPixelColor(0, 255, 0, 0);
    fw_pixel.show();
  }

  Serial.println("===ONLINE===");

  Wire.begin();

  keyboard.begin();
  keyboard.setBacklight(0.5f);

  fw_pixel.begin();
  fw_pixel.setBrightness(8);
  fw_pixel.setPixelColor(0, 0, 255, 64);
  fw_pixel.show();
}

void loop()
{
  char key_pressed = read_next_key();
  switch (key_pressed)
  {
    //These are the four buttons on the top row
  case 0x06: // Button 1
    Serial.println("Button 1 Pressed");
    button_1(); //Drops into function
    break;
  case 0x11: // Button 2
    Serial.println("Button 2 Pressed");
    break;
  case 0x07: // Button 3
    Serial.println("Button 3 Pressed");
    break;
  case 0x12: // Button 4
    Serial.println("Button 4 Pressed");
    break;
  }
}

//Button Row
//  1   0x06
//  2   0x11
//  3   0x07
//  4   0x12
//
//Center Knob
// Press  0x05
// Left   0x03
// Right  0x04
// Up     0x01
// Down   0x02
