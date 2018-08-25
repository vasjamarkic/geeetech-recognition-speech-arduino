

#define RED 3     //PWM outputs for RGB colors
#define GREEN 5
#define BLUE 6
byte com = 0; 
int i = 0;    // for switcing colors
int DIM = 1;  // for dimming the LED, 3 steps of luminosity

int REDstatus = 0;
int GREENstatus = 0;
int BLUEstatus = 0;

long time = 0;
long debounce = 200;

int RGBvalues(int R, int G, int B) {
  REDstatus = R;
  GREENstatus = G;
  BLUEstatus = B;
  }

void setup() {
  
  Serial.begin(9600);
  Serial.write(0xAA);
  Serial.write(0x37);
  delay(500);
  Serial.write(0xAA);
  Serial.write(0x21);   // import commands from group 1
  delay(500);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

}

void loop() {
  
  while(Serial.available()) {
  com = Serial.read();
  switch(com) {

      case 0x11://  command 1 WHITE
      RGBvalues(255,255,255);
      break;
      case 0x12:  //command 2 is turn OFF
      RGBvalues(0,0,0);
      break;
      case 0x13: { //command 3 is NEXT color
      i++;
      if (i > 11) {     // if loop completed, go back to first color
        i = 1;
        }
      switch (i) {
        case 1:
        RGBvalues(255,255,0); break;
        case 2:
        RGBvalues(255,128,0); break;
        case 3:
        RGBvalues(255,0,0); break;
        case 4:
        RGBvalues(255,0,128); break;
        case 5:
        RGBvalues(255,0,255); break;
        case 6:
        RGBvalues(128,0,255); break;
        case 7:
        RGBvalues(0,0,255); break;
        case 8:
        RGBvalues(0,128,255); break;
        case 9:
        RGBvalues(0,255,255); break;
        case 10:
        RGBvalues(0,255,128); break;
        case 11:
        RGBvalues(0,255,0); i=0; break;
        }
        }
      break;
      case 0x14: {   //go back change the color
      i--;
      if (i < 0) {              // if loop (backward) completed, go to last color
        i= 11;
        }
      switch (i) {
        case 1:
        RGBvalues(255,255,0); break;
        case 2:
        RGBvalues(255,128,0); break;
        case 3:
        RGBvalues(255,0,0); break;  //RED
        case 4:
        RGBvalues(255,0,128); break;
        case 5:
        RGBvalues(255,0,255); break;   
        case 6:
        RGBvalues(128,0,255); break;
        case 7:
        RGBvalues(0,0,255); break;
        case 8:
        RGBvalues(0,128,255); break;
        case 9:
        RGBvalues(0,255,255); break;
        case 10:
        RGBvalues(0,255,128); break;
        case 11:
        RGBvalues(0,255,0); break;
        }
        }
      break;
      RGBvalues(255,255,0);
      break;
      case 0x15:  //command 5 DIM: three dimm factors: 1, 2, 4!
      DIM=DIM*2;
      if (DIM > 4) {       //after comliting loop, reset to max brightness
        DIM = 1;
        }
      break;
      
   }
   analogWrite(RED, REDstatus/DIM);      //send value PWM to MOSFET
   analogWrite(GREEN, GREENstatus/DIM);
   analogWrite(BLUE, BLUEstatus/DIM);
  }
}
