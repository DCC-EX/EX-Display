#ifndef EX_SCREEN_H
#define EX_SCREEN_H

// EX-Screen.h

#define DEBUG

uint8_t currentScreenID = 0;

// ALL Touch panels and wiring are DIFFERENT.  The touch screen needs to be calibrated
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

// variables to indicate what needs doing to display the screen
bool ScreenChanged[MAX_SCREENS];
bool PrintInProgress=false;
byte NextRowToPrint=0;
byte NextScreenLine=0;

namespace SCREEN
{

    void TFT_Startup();
    void showmsgXY(int x, int y, int sz, const char *msg);
    void TFT_DrawHeader();
    void testprint(byte lines);
    void setScreenRows(uint8_t rowId);
    void CheckScreens();
    void StartScreenPrint();
    void PrintNoData();
    //void PrintSingleLine(byte screenNo, byte screenRow);
    void PrintALine(int Row, char * text);
    void DisplayScreen();
    void check_touch();

}

#endif