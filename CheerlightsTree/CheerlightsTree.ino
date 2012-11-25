#include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial xBeeSerial =  SoftwareSerial(8, 9);
String response;

int ledAnalogOne[] = {3, 5, 6}; 
//the three pins of the first analog LED 3 = redPin, 5 = greenPin, 6 = bluePin                                
//These pins must be PWM

//Defined Colors (different RGB (red, green, blue) values for colors
const byte RED[] = {0, 255, 255}; 
const byte ORANGE[] = {172, 251, 255}; 
const byte YELLOW[] = {0, 200, 255}; 
const byte GREEN[] = {255, 0, 255}; 
const byte BLUE[] = {255, 255, 0}; 
const byte CYAN[] = {255, 0, 0}; 
const byte MAGENTA[] = {0, 255, 200}; 
const byte WHITE[] = {0, 50, 150}; 
const byte WARMWHITE[] = {0, 170, 240};
const byte BLACK[] = {255, 255, 255}; //?
const byte PURPLE[] = {100, 255, 160}; 

static uint16_t c;
String lastCommandString = "";
byte lastCommand[] = {255, 255, 255};


void setup() {
  for(int i = 0; i < 3; i++) {   
    pinMode(ledAnalogOne[i], OUTPUT);   //Set the three LED pins as outputs   
  }  
  setColor(ledAnalogOne, BLACK);       //Turn off led 1  
  xBeeSerial.begin(9600);
  xBeeSerial.println("Hello, world? -Arduino");
  Serial.begin(9600);
  delay(100); 
  Serial.flush();
  delay(100);
  Serial.println("Setup completed.");
}

void loop()
{
  updateColor();
  delay(20000);
}

void updateColor()                     // run over and over again
{
  Serial.println("updateColor was called.");
  char charIn;
  xBeeSerial.println("<CheerlightsColor>");
  delay(5000);
  while(xBeeSerial.available()){  //is there anything to read?
    charIn = xBeeSerial.read(); // read a char from the buffer
    if (charIn == ',') {
      Serial.println(response);
      // Light the tree
      if (response=="warmwhite")
      {  
         fadeToColor(ledAnalogOne, lastCommand, WARMWHITE, 10);
         //delay(3000);
         for(int i = 0; i < 3; i++) {   
            lastCommand[i] = WARMWHITE[i];
         }
         lastCommandString = "whitewhite";
      }
      else if (response=="black")
      {  
         fadeToColor(ledAnalogOne, lastCommand, BLACK, 10);  
         for(int i = 0; i < 3; i++) {   
            lastCommand[i] = BLACK[i];
         }  
         lastCommandString = "black";
      }
      else if (response=="red")
      {  
         fadeToColor(ledAnalogOne, lastCommand, RED, 10);  
         for(int i = 0; i < 3; i++) {   
            lastCommand[i] = RED[i];
         }  
         lastCommandString = "red";
      }
      else if (response=="green")
      {  
         fadeToColor(ledAnalogOne, lastCommand, GREEN, 10);  
         for(int i = 0; i < 3; i++) {   
            lastCommand[i] = GREEN[i];
         }  
         lastCommandString = "green";
      }
      else if (response=="blue")
      {  
         fadeToColor(ledAnalogOne, lastCommand, BLUE, 10);  
         for(int i = 0; i < 3; i++) {   
            lastCommand[i] = BLUE[i];
         }  
         lastCommandString = "blue";
      }
      else if (response=="cyan")
      {  
         fadeToColor(ledAnalogOne, lastCommand, CYAN, 10); 
         for(int i = 0; i < 3; i++) {   
            lastCommand[i] = CYAN[i];
         }  
         lastCommandString = "cyan";
      }
      else if (response=="magenta")
      {  
         fadeToColor(ledAnalogOne, lastCommand, MAGENTA, 10);  
         for(int i = 0; i < 3; i++) {   
            lastCommand[i] = MAGENTA[i];
         }  
         lastCommandString = "magenta";  
      }
      else if (response=="yellow")
      {  
         fadeToColor(ledAnalogOne, lastCommand, YELLOW, 10);  
         for(int i = 0; i < 3; i++) {   
            lastCommand[i] = YELLOW[i];
         }  
         lastCommandString = "yellow";  
      }
      else if (response=="purple")
      {  
         fadeToColor(ledAnalogOne, lastCommand, PURPLE, 10);  
         for(int i = 0; i < 3; i++) {   
            lastCommand[i] = PURPLE[i];
         }  
         lastCommandString = "purple";  
      }
      else if (response=="orange")
      {  
         fadeToColor(ledAnalogOne, lastCommand, ORANGE, 10); 
         for(int i = 0; i < 3; i++) {   
            lastCommand[i] = ORANGE[i];
         }  
         lastCommandString = "orange";  
      }
      else if (response=="white")
      {  
         fadeToColor(ledAnalogOne, lastCommand, WHITE, 10);
         for(int i = 0; i < 3; i++) {   
            lastCommand[i] = WHITE[i];
         }  
         lastCommandString = "white";  
      }
      else if (response=="black")
      {  
        fadeToColor(ledAnalogOne, lastCommand, BLACK, 10);
        for(int i = 0; i < 3; i++) {   
            lastCommand[i] = BLACK[i];
        }  
        lastCommandString = "black";  
      }
      else
      {
        Serial.println("No match.");
        //lastCommand = "(no match)";  
      }
      response = "";
      xBeeSerial.println(lastCommandString);
      Serial.println("End of color processing loop");
    } else {
      response += charIn; // append that char to the string response
//      Serial.print(charIn);
//      Serial.println(" added");
//      Serial.print("Response: ");
//      Serial.println(response);
    }  
  }

    
  
} // End loop


/* Sets the color of the LED to any RGB Value   led - (int array of three values defining the LEDs pins (led[0] = redPin, led[1] = greenPin, led[2] = bluePin))   color - (byte array of three values defing an RGB color to display (color[0] = new Red value, color[1] = new Green value, color[2] = new Red value*/
void setColor(int* led, byte* color){ 
  
  for(int i = 0; i < 3; i++){             //iterate through each of the three pins (red green blue)   
    analogWrite(led[i], 255 - color[i]);  //set the analog output value of each pin to the input value (ie led[0] (red pin) to 255- color[0] (red input color)                                         
    //we use 255 - the value because our RGB LED is common anode, this means a color is full on when we output analogWrite(pin, 0)                                         
    //and off when we output analogWrite(pin, 255).  
    //Serial.print("Setting:");
    //Serial.println(i);
  }
}

/* A version of setColor that takes a predefined color (neccesary to allow const int pre-defined colors */
void setColor(int* led, const byte* color) { 
  byte tempByte[] = {color[0], color[1], color[2]}; 
  setColor(led, tempByte);
}

/* Fades the LED from a start color to an end color at fadeSpeed   
led - (int array of three values defining the LEDs pins (led[0] = redPin, led[1] = greenPin, led[2] = bluePin))   
startCcolor - (byte array of three values defing the start RGB color (startColor[0] = start Red value, startColor[1] = start Green value, startColor[2] = start Red value   
endCcolor - (byte array of three values defing the finished RGB color (endColor[0] = end Red value, endColor[1] = end Green value, endColor[2] = end Red value   
fadeSpeed - this is the delay in milliseconds between steps, defines the speed of the fade*/ 
void fadeToNumColor(int* led, byte* startColor, byte* endColor, int fadeSpeed) {  
  int changeRed = endColor[0] - startColor[0];                             //the difference in the two colors for the red channel  
  int changeGreen = endColor[1] - startColor[1];                           //the difference in the two colors for the green channel   
  int changeBlue = endColor[2] - startColor[2];                            //the difference in the two colors for the blue channel  
  int steps = max(abs(changeRed),max(abs(changeGreen), abs(changeBlue)));  //make the number of change steps the maximum channel change    
  for(int i = 0 ; i < steps; i++) {                                        //iterate for the channel with the maximum change   
    byte newRed = startColor[0] + (i * changeRed / steps);                 //the newRed intensity dependant on the start intensity and the change determined above   
    byte newGreen = startColor[1] + (i * changeGreen / steps);             //the newGreen intensity   
    byte newBlue = startColor[2] + (i * changeBlue / steps);               //the newBlue intensity   
    byte newColor[] = {newRed, newGreen, newBlue};                         //Define an RGB color array for the new color   
    setColor(led, newColor);                                               //Set the LED to the calculated value   
    delay(fadeSpeed);                                                      //Delay fadeSpeed milliseconds before going on to the next color  
  }  
  setColor(led, endColor);                                                 //The LED should be at the endColor but set to endColor to avoid rounding errors
}

/* A version of fadeToColor that takes predefined colors (neccesary to allow const int pre-defined colors */
void fadeToColor(int* led, const byte* startColor, const byte* endColor, int fadeSpeed) {  
  byte tempByte1[] = {startColor[0], startColor[1], startColor[2]};   
  byte tempByte2[] = {endColor[0], endColor[1], endColor[2]};   
  fadeToNumColor(led, tempByte1, tempByte2, fadeSpeed);
}
