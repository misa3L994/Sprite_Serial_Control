/*

*/
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

Sprite::Sprite() {}
Sprite::Sprite(byte addr)
{
  _addr = addr;
  addres = true;
}

void Sprite :: begin(Stream &s)
{
  serial = &s;
}
void Sprite :: sendCmd(byte command)
{
  byte Send_buf[2] = {0};
  String mp3send = "";

  delay(10);

  if (addres)
  {
    Send_buf[0] = _addr;
    Send_buf[1] = command;

    for (int i = 0; i < 2; i++) {
      serial->write(Send_buf[i]);
      mp3send += sbyte2hex(Send_buf[i]);
    }

  } else {
    Send_buf[0] = command;
    serial->write(Send_buf[0]);
    mp3send += sbyte2hex(Send_buf[0]);
  }

  Serial.print("Sending: ");
  Serial.println(mp3send);

}
void Sprite :: sendCmd(byte command, byte file)
{
  byte Send_buf[3] = {0};
  String mp3send = "";

  delay(10);

  if (addres) {

    Send_buf[0] = _addr;
    Send_buf[1] = command;
    Send_buf[2] = file;

    for (int i = 0; i < 3; i++) {
      serial->write(Send_buf[i]);
      mp3send += sbyte2hex(Send_buf[i]);
    }
  }  else {
    Send_buf[0] = command;
    Send_buf[1] = file;

    for (int i = 0; i < 2; i++) {
      serial->write(Send_buf[i]);
      mp3send += sbyte2hex(Send_buf[i]);
    }
  }
  Serial.print("Sending: ");
  Serial.println(mp3send);

}
void Sprite :: play(byte file)
{
  sendCmd(file);
}
void Sprite :: mute(void)
{
  sendCmd(CMD_MUTE_KEY);
}
void Sprite :: play(void)
{
  sendCmd(CMD_PLAY);
}
void Sprite :: pause(void)
{
  sendCmd(CMD_PAUSE);

}
void Sprite :: playNext(void)
{
  sendCmd(CMD_NEXT);
}
void Sprite :: playPrevious(void)
{
  sendCmd(CMD_PREV);
}
void Sprite :: volUp(void)
{
  sendCmd(CMD_VOLUME_UP);
}
void Sprite :: volDown(void)
{
  sendCmd(CMD_VOLUME_DWN);
}
void Sprite :: qTFiles(void)
{
  sendCmd(CMD_REQUEST_NUMBER_OF_FILES);
}
void Sprite :: setFullVolume(void)
{
  sendCmd(CMD_FULL_VOLUME);

}
void Sprite :: playLoop(byte file)
{
  sendCmd(LOOP_FILE, file);
}
String Sprite::sbyte2hex(byte b)
{
  String shex;

  shex = "0X";

  if (b < 16) shex += "0";
  //Serial.print(b, HEX);
  shex += String(b, HEX);
  //Serial.print(" ");
  shex += " ";
  return shex;
}

byte Sprite :: answerSprite(void)
{
  byte answer = 0x00;

  if (getAnswer())// si hay una respuesta nueva
  {

    if (flagBuf)
    {
      flagBuf = false;
      answer = ansBuf[2];
      return answer;
    }
    answer = answerVal;

    /*
      switch (answerVal)
      {
        default:
          answer = answerVal;
          break;
        case CMD_PLAY:
          answer = CMD_PLAY;
          break;
        case CMD_PAUSE:
          answer = CMD_PAUSE;
          break;
        case CMD_PREV:
          answer = CMD_PREV;
          break;
        case CMD_NEXT:
          answer = CMD_NEXT;
          break;
        case COMPLETED_PLAY:
          answer = COMPLETED_PLAY;
          break;
      }*/
  }
  //last_answer = answer;
  answerVal = 0;
  return answer;
}
bool Sprite :: getAnswer(void)
{
  byte b;
  bool ok = false;
  if (serial->available())
  {
    b = serial->read();


    if (b == CMD_REQUEST_NUMBER_OF_FILES)
    {
      int i = 0;
      byte a;
      ansBuf[i] = b;
      i++;
      while (serial->available())
      {
        a = serial->read();
        ansBuf[i] = a;
        i++;
      }

      flagBuf = true;
      ok = true;
    }

    if (b != last_answer)
    {
      answerVal = b;
      last_answer = b;
      ok = true;
    }

  }
  return ok;
}
