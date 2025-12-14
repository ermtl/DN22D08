/*
||
|| @file DN22D08.h
|| @version 1.0
|| @author DanielTronic Labs
|| @contact danieltronic808@gmail.com
||
|| @description
||   This library provides a simple interface to use 
||   a PLC IO RS485 DN22D08 controls the output relays and 
||   multiplexes the 7-segment display to show numerical values.
||
||
|| version 1.1
|| by erMtl 
|| - Interrupt task reorganization without using delay and several improvements including overrun protection
|| - Simplified initialisation (call without parameter for default)
|| - optimisation of the relay function and addition of a readback function (getRelay)
|| - Ability to set the decimal point on the display
|| - RS485 command sending including CRC calculation
||
*/


#ifndef DN22D08_Board
#define DN22D08_Board

const byte hc595_clockPin = A4;  // connect clockPin 595 pin 11
const byte hc595_latchPin = A3;  // connect latchPin 595 pin 12
const byte hc595_OE       = A2;  // connect       OE 595 pin 13
const byte hc595_dataPin  = A5;  // connect  dataPin 595 pin 14

const byte kbd1     = 12;  // button1
const byte kbd2     = 10;  // button2
const byte kbd3     = 8;   // button3
const byte kbd4     = A0;  // button4

const byte input1   = 2;   // Isolated input 1
const byte input2   = 3;   // Isolated input 2
const byte input3   = 4;   // Isolated input 3
const byte input4   = 5;   // Isolated input 4
const byte input5   = 6;   // Isolated input 5
const byte input6   = 7;   // Isolated input 6
const byte input7   = 9;   // Isolated input 7
const byte input8   = 11;  // Isolated input 8

const byte RS485_RD = A1;  // RS485 direction

#endif



#ifndef DN22D08_h
#define DN22D08_h
 
#include "Arduino.h"


 
class DN22D08
{
  public:
    DN22D08();
    void begin();
    void begin(byte latchPin,byte clockPin,byte dataPin,byte oe_595);
    void Init();
    void setKeyboardPins();
    void setKeyboardPins(byte kb1, byte kb2, byte kb3, byte kb4);
    void setInputPins();
    void setInputPins(byte i1, byte i2, byte i3 , byte i4, byte i5, byte i6, byte i7, byte i8);

    void setRS485(int speed);
    void sendRS485(unsigned char *str,unsigned int DataLen);
    void sendModbusRelay (byte device,unsigned int relay,boolean state);


    void setvalue(int value);
    void setvalue(int value,byte dp);
    void relay(byte value,boolean state);
    bool getRelay(byte value);
  private:
    byte _pin;
    byte _clockPin;           //connect 595  pin 11
    byte _latchPin;           //connect 595  pin 12
    byte _oe_595;             //connect 595  pin 13
    byte _dataPin;            //connect 595  pin 14

    byte _DISP_SEG1[10] = {16, 16, 24, 24, 24, 8, 8, 16, 24, 24};
    byte _DISP_SEG2[10] = {218, 128, 26, 152, 192, 216, 218, 144, 218, 208};
    byte _DISP_MUL1[4] = {38, 36, 34, 6};
    byte _DISP_MUL2[4] = {0, 4, 4, 4};
    byte _data[4] = {0, 0, 0, 0};
    byte _dp=0;
    byte _relay=0;
    byte _phase=0;
    bool _in_int=false;

    int _RSpeed;
    unsigned char _buf[16];
};
 
#endif


