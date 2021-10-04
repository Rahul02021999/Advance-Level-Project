#include <Keypad.h>
#include <LiquidCrystal.h>
const int rs = 7, en = 6, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char * password = "A1B2C3D4"; // To increase the passcode length change the numerical to the size after position

int position = 0;

const byte ROWS = 4; // 4 rows
const byte COLS = 4; // 4 columns

char keys[ROWS][COLS] =
{
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
}; //mapping of the keys done w.r.t to the grid keypad

byte rowPins[ROWS] = { 47, 46, 45, 44 }; //connection of rows pins to the Arduino
byte colPins[COLS] = { 40, 41, 42, 43 }; // connection of the columns pins to the Arduino

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int Lock = 5; // Connecting the relay to the 5th pin

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Enter Passcode!");

pinMode(Lock, OUTPUT);
LockedPosition(true);
}

void loop()
{
char key = keypad.getKey();
if (key == '*' || key == '#') //OR operator used to lock the device back again
{
position = 0;
LockedPosition(true);
}
if (key == password[position])
{
position ++;
}
if (position == 8) // change this if you want to increase the password length
{
LockedPosition(false);
}
delay(100);
}
void LockedPosition(int locked)
{
if (locked)
{
digitalWrite(Lock, LOW);
}
else
{
digitalWrite(Lock, HIGH);
}
}
