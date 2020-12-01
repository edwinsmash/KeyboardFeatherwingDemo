#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define display_i2c_address 0x3c
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//I2C Config
#define token_i2c_addr 8

byte received_data[] = {};

void receiveEvent(int len)
{
  // Read while data received
  Serial.println("===START TRANSMISSION===");

  int counter = 0;

  while (Wire.available())
  {
    byte b = Wire.read();
    received_data[counter] = b;
    counter++;
  }
  Serial.println("Done Receiving.");
  Serial.print("Length of Received Data: ");
  Serial.println(counter);
  Serial.println("Received Data: ");
  for (int i = 0; i < counter; i++)
  {
    Serial.print(i);
    Serial.print("    ");
    Serial.println(received_data[i], HEX);
  }
  Serial.println("===END TRANSMISSION===");
  delay(1000);
  Serial.println("===START DISPLAY===");
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(24, 14);
  display.print("DATA");
  display.display();
  Serial.println("===END DISPLAY===");
  delay(1000);
}

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(24, 14);
  display.print("SETUP");
  display.display();

  Serial.println();
  Serial.println("ONLINE.");
  Serial.println();

  delay(2000);

  Wire.begin(8);
  Wire.onReceive(receiveEvent); // register event
}

void loop()
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(24, 14);
  display.print("WAIT");
  display.display();
  delay(500);
}