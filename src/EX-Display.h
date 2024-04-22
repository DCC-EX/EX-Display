#ifndef EX_DISPLAY_h
#define EX_DISPLAY_H

// EX-Display.h

#define DEBUG

byte THIS_SCREEN_NUM = 0;

#define FONT_SIZE 2.5 // Adjust font size as needed
#define CHAR_WIDTH (6 * FONT_SIZE) // Width of a single character in pixels

// Set this following string to the header you require.  This is displayed at the top of the screen
#define HDDR_SIZE  25




// ALL Touch panels and wiring is DIFFERENT.  The touch screen needs to be calibrated
// See the README files for how to run the calibration routine and
// copy-paste results from TouchScreen_Calibr_native.ino into the lines below.
// These settings are for the McuFriend 2.8" shield in Portrait tft.screenRotaion(0)

//const byte XP = 7, XM = A1, YP = A2, YM = 6;
//const int TS_LEFT=899,TS_RT=122,TS_TOP=100,TS_BOT=898;
//const int TS_LEFT=122,TS_RT=899,TS_TOP=100,TS_BOT=898;

// Define some colours for the display

#define BLACK   0x0000U
#define RED     0xF800U
#define GREEN   0x07E0U
#define CYAN    0x07FFU
#define MAGENTA 0xF81FU
#define YELLOW  0xFFE0U
#define WHITE   0xFFFFU
//#define YELLOW  0xE0U
//#define WHITE   0xFFU
//const uint16_t YELLOW = 0xFFE0U;
//const uint16_t WHITE = 0xFFFFU;


/*#if defined(ESP32)
  #define YELLOW ~YELLOW
  #define WHITE ~WHITE
#endif*/

// A structure to store the screen lines.
struct DisplayStruct
{
  bool inuse=false;
  byte row=0;
  char text[MAX_LINE_LENGTH]=" ";
} DisplayLines[MAX_SCREENS][MAX_ROWS];

// variables to indicate what needs doing to display the screen
bool ScreenChanged[MAX_SCREENS] = {false,false};
//bool ScreenDrawn=false
bool PrintInProgress=false;
byte NextRowToPrint=0;
byte NextScreenLine=0;
long timestamp=0;
long screencount=0;
bool StartupPhase = true;

void TFT_Startup();
//void showmsgXY(int x, int y, byte sz, char colour, char *msg);
void showmsgXY(int x, int y, byte sz, uint16_t color, char *msg);

void TFT_DrawHeader();
void testprint(byte lines);
void ParseData(String message);
void StartScreenPrint();
//void PrintNextLine();
void PrintSingleLine(byte screenNo, byte screenRow);
void PrintALine();
void DisplayScreen();


#endif