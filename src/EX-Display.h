// EX-Display.h

#define DEBUG

#define THIS_SCREEN_NUM 0
#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240

#define FONT_SIZE 2.5 // Adjust font size as needed
#define CHAR_WIDTH (6 * FONT_SIZE) // Width of a single character in pixels

// Set this following string to the header you require.  This is displayed at the top of the screen
#define HDDR_SIZE  25


// ALL Touch panels and wiring is DIFFERENT.  The touch screen needs to be calibrated
// See the README files for how to run the calibration routine and
// copy-paste results from TouchScreen_Calibr_native.ino into the lines below.
// These settings are for the McuFriend 2.8" shield in Portrait tft.screenRotaion(0)

const byte XP = 7, XM = A1, YP = A2, YM = 6;
//const int TS_LEFT=899,TS_RT=122,TS_TOP=100,TS_BOT=898;
const int TS_LEFT=122,TS_RT=899,TS_TOP=100,TS_BOT=898;

// Define some colours for the display

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


void TFT_Begin();
void showmsgXY(int x, int y, byte sz, char colour, char *msg);
void TFT_DrawHeader();
void testprint(byte lines);
void displayMessage(String message);
void ParseData(String message);
