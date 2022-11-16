#include <Keyboard.h>
#include <Wire.h>
#include <Key.h>
#include <Mouse.h>
#include <Keypad.h>
#include <Encoder.h>

const int rows = 3;               //three rows
const int cols = 4;               //four columns
const int layers = 4;             //number of layers (must be changed is additional layers are added)

int curRow = 0;
int curCol = 0;
int curLayer = 0;

long enc1Pos = -999;
long enc2Pos = -999;

//RGB based colours (use https://www.rapidtables.com/web/color/RGB_Color.html to add a custom colour)
//White   #FFFFFF
int colourWhite[3] = {255, 255, 255};
//Black   #000000
int colourBlack[3] = {0, 0, 0};
//Red     #FF0000
int colourRed[3] = {255, 0, 0};
//Green   #00FF00
int colourGreen[3] = {0, 255, 0};
//Blue    #0000FF
int colourBlue[3] = {0, 0, 255};
//Yellow  #FFFF00
int colourYellow[3] = {255, 255, 0};
//Pink    #FF00FF
int colourPink[3] = {255, 0, 255};
//Orange  #FFA500
int colourOrange[3] = {255, 165, 0};
//*colour name*  *hex value*
//const int colour*colour name*[3] = {*add RGB values here*};


char keys[rows][cols] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', 'A', 'B', 'C'}
};
//    |-----------------------|
//    |- 1 - 2 - 3 - 4 -------|
//    |-----------------------|
//    |- 5 - 6 - 7 - 8 -------|
//    |-----------------------|
//    |- 9 - A - B - C -------|
//    |-----------------------|
//    4 and 8 are the rotary encoders so also include 2 rotation
//    NOTE: rotation on encoder 4 is reserved for changin mode

byte rowPins[rows]  = { 4, 5, 6 };        //pin designations for the rows
byte colPins[cols]  = { 14, 15, 16, 17 };        //pin designations for the columns
byte enc1Pins[2]    = { 18, 19 };          //pin designations for the 1st encoder (key 4)
byte enc2Pins[2]    = { 20, 21 };          //pin designations for the 2nd encoder (key 8)
byte rgbPins[3]     = { 0, 2, 1 };           //pin designations for the RGB LED

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );
Encoder encoder1(enc1Pins[0], enc1Pins[1]);
Encoder encoder2(enc2Pins[0], enc2Pins[1]);

void setup() {
  Serial.begin(9600);

  pinMode(rgbPins[0], OUTPUT);
  pinMode(rgbPins[1], OUTPUT);
  pinMode(rgbPins[2], OUTPUT);

  Keyboard.begin();
}

void loop() {
  char key = keypad.getKey();
  
//================Layer Definitions==================
//this section uses a switch case to define the 
//different layers, more layers can be added by 
//altering the "layer" variable, adding a new case 
//to this section

  switch (curLayer) {
    default:
      curLayer = 0;
    case 0:
      setColour( colourRed );     //sets the colour for the current layer
  
//================Macro Definitions=================
//Macro keys can be coded by using a mix of button 
//combinations, mouse functions and the "windows run" 
//short cut check the keyboard.h and mouse.h refernce 
//pages for more details
//https://www.arduino.cc/reference/en/language/functions/usb/keyboard/
//https://www.arduino.cc/reference/en/language/functions/usb/mouse/
//
//additional functionality can be gained by using 
//"autohotkey" https://www.autohotkey.com/
//this software provides additional functionality
//that was not included in this version of the code
//
//for additional keyboard shotcuts check this wiki
//https://en.wikipedia.org/wiki/Table_of_keyboard_shortcuts
//
//have additional macro functionality suggestions?
//or know a library that could add additional functionality
//or other feedback, email: maker.society@hw.ac.uk

//Basic editing keys
      if (key) {
        Serial.println(key);

        switch (key) {
          case '1':               //copy
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('c');
            break;
          case '2':               //paste
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('v');
            break;
          case '3':               //cut
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('x');
            break;
          case '4':               //mode select
            setMode();
            break;
          case '5':               //save
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('s');
            break;
          case '6':               //comment/uncomment
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('/');
            break;
          case '7':               //find
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('f');
            break;
          case '8':               //quick switch
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.press(KEY_TAB);
            break;
          case '9':               //undo
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('z');
            break;
          case 'A':               //redo
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('y');
            break;
          case 'B':               //save and quit
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('s');
            delay(100);
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('q');
            break;
          case 'C':               //open adruino IDE
            Keyboard.press(KEY_LEFT_GUI); 
            Keyboard.press('r'); 
            delay(150);
            //tp quick start a program enter the location of the .exe
            //file into this line
            //IMPORTANT: use forward slashes and not backslashes
            Keyboard.println( "g:/Laptop/Arduino/arduino.exe" );
            break;
        }
      }

      delay(100); Keyboard.releaseAll();
      break;

    case 1:
      setColour(colourGreen);     //sets the colour for the current layer
  
//================Macro Definitions=================

      if (key) {
        Serial.println(key);

        switch (key) {
          case '1':
            break;
          case '2':
            break;
          case '3':
            break;
          case '4':
            setMode();
            break;
          case '5':
            break;
          case '6':
            break;
          case '7':
            break;
          case '8':
            break;
          case '9':
            break;
          case 'A':
            break;
          case 'B':
            break;
          case 'C':
            break;
        }
      }

      delay(100); Keyboard.releaseAll();
      break;

    case 2:
      setColour(colourBlue);     //sets the colour for the current layer
  
//================Macro Definitions=================

      if (key) {
        Serial.println(key);

        switch (key) {
          case '1':
            break;
          case '2':
            break;
          case '3':
            break;
          case '4':
            setMode();
            break;
          case '5':
            break;
          case '6':
            break;
          case '7':
            break;
          case '8':
            break;
          case '9':
            break;
          case 'A':
            break;
          case 'B':
            break;
          case 'C':
            break;
        }
      }

      delay(100); Keyboard.releaseAll();
      break;

    case 3:
      setColour(colourPink);     //sets the colour for the current layer
  
//================Macro Definitions=================

      if (key) {
        Serial.println(key);

        switch (key) {
          case '1':
            break;
          case '2':
            break;
          case '3':
            break;
          case '4':
            setMode();
            break;
          case '5':
            break;
          case '6':
            break;
          case '7':
            break;
          case '8':
            break;
          case '9':
            break;
          case 'A':
            break;
          case 'B':
            break;
          case 'C':
            break;
        }
      }

      delay(100); Keyboard.releaseAll();
      break;
  }
}

void setColour(int *rgb) {
  analogWrite(rgbPins[0], rgb[0]);
  analogWrite(rgbPins[1], rgb[1]);
  analogWrite(rgbPins[2], rgb[2]);
}

//================Encoder functions==================
//This Section uses the encode.h library
//documentation of which can be found at:
// https://www.pjrc.com/teensy/td_libs_Encoder.html

//===============Change layer function===============
//this function is designed to be assigned to a key
//press, so that a the encoder can have an additional
//function.
//while by default it's set to the button of encoder 1
//it can be assigned to any button.
void setMode() {
  char key = keypad.getKey();
  int count = 100;
  int modeSelect = curLayer;
  long newPos = encoder1.read();
  enc1Pos = newPos;

  //This while loop prevents other functions from being
  //used while while the layer is being changed, if the
  //button in the encoder isn't pressed and no change
  //is made for 10 seconds it will cancel the selection.

  while ((key != '4') && (count != 0)) {
    newPos = encoder1.read();

    if (newPos != enc1Pos && newPos > (enc1Pos + 2)) {
      enc1Pos = newPos;
      count = 100;
      modeSelect--;
    }
    if (newPos != enc1Pos && newPos < (enc1Pos - 2)) {
      enc1Pos = newPos;
      count = 100;
      modeSelect++;
    }
  
    //allows the selection to loop
    if (modeSelect < 0) {
      modeSelect = (layers - 1);
    }
    else if (modeSelect > (layers - 1)) {
      modeSelect = 0;
    }
  
    //changes the LED's colour to provide feedback on the current choice.
    //additional cases will need ot be added to account for additional 
    //layers.
    switch (modeSelect) {
      default:
        modeSelect = 0;
      case 0:
        setColour(colourRed);
          break;
      case 1:
        setColour(colourGreen);
        break;
      case 2:
        setColour(colourBlue);
        break;
      case 3:
        setColour(colourPink);
        break;
    }

    delay(100);
    count--;
    key = keypad.getKey();
  }


  //sets the current layer to the chosen layer then
  //changes flashes LED to provide feedback
  if(count != 0){
    curLayer = modeSelect;
  }
  setColour(colourWhite);
  delay(200);
  setColour(colourBlack);
  delay(200);
  setColour(colourWhite);
  delay(200);
}


//================encoder1 function 1================
//==================Volume Control===================
//
//void enc1Mode1() {
//  char key = keypad.getKey();
//  int count = 100;
//  int modeSelect = curLayer;
//  long newPos = encoder1.read();
//  enc1Pos = newPos;
//
//  if (newPos != enc1Pos && newPos > (enc1Pos + 2)) {
//    enc1Pos = newPos;
//  }
//  if (newPos != enc1Pos && newPos < (enc1Pos - 2)) {
//    enc1Pos = newPos;
//  }
//}
