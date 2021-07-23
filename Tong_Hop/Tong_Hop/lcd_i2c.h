#ifndef LCD_I2C_H
#define LCD_I2C_H
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

void lcd_init()
{
  lcd.init();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   SMART STEWARD    ");
  lcd.setCursor(0, 1);
  lcd.print("0000-00-00 00:00:00 ");
  lcd.setCursor(0, 2);
  lcd.print("PH.NGU 1: 00oC-00%RH");
  lcd.setCursor(0, 3);
  lcd.print("PH.NGU 2: 00oC-00%RH");
}

#endif
