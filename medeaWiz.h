/*
Biblioteca Sprite serial control
by Misael Reyes 


*/
#ifndef  proyectil_MEDEAWIZ_H_
#define  proyectil_MEDEAWIZ_H_

#include <Arduino.h>

#define CMD_REQUEST_NUMBER_OF_FILES   0xCB
#define CMD_HDMI_720P_50              0xD6
#define CMD_HDMI_720P_60              0xD7
#define CMD_HDMI_1080P_24             0xD8
#define CMD_HDMI_1080P_50             0xD9
#define CMD_HDMI_1080P_60             0xDA
#define CMD_HDMI_1080I_50             0xDB
#define CMD_HDMI_1080I_60             0xDC
#define CMD_ADD_E1                    0xE1
#define CMD_ADD_E2                    0xE2
#define CMD_ADD_E3                    0xE3
#define CMD_ADD_E4                    0xE4
#define CMD_ADD_E5                    0xE5
#define CMD_FULL_VOLUME               0xE7
#define CMD_MUTE_KEY                  0xE8
#define CMD_VOLUME_UP                 0xE9
#define CMD_VOLUME_DWN                0xEA
#define CMD_PLAY                      0xEF
#define CMD_PAUSE                     0xF0
#define CMD_FB                        0xF1
#define CMD_FF                        0xF2
#define CMD_PREV                      0xF3
#define CMD_NEXT                      0xF4
#define COMPLETED_PLAY                0xEE
#define LOOP_FILE                     0xFC


//#define serial Serial1


class Sprite
{
  public:
    Sprite();
    Sprite(byte);
    void begin(Stream&);
    void sendCmd(byte command);
    void sendCmd(byte command, byte file);
    void play(byte file);
    void play(void);
    void pause(void);
    void playNext(void);
    void mute(void);
    void playPrevious(void);
    void setFullVolume(void);
    void volUp(void);
    void volDown(void);
    void qTFiles(void);
    void playLoop(byte);
    String sbyte2hex(byte b);
    bool getAnswer(void);
    byte answerSprite(void);

  private:
    Stream* serial;
    byte answerVal;
    byte last_answer;
    byte ansBuf[3];
    bool flagBuf = false;
    byte _addr;
    bool addres = false;
};

#endif
