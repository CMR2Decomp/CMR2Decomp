#ifndef _GAME_INFO_H
#define _GAME_INFO_H

typedef unsigned char undefined;

unsigned char GetGameLanguage(void);
unsigned int GetGameRegion(void);

struct GameInfo
{
    unsigned char empty[16];
    int magicNumber; /* Always 0x11 */
    int field2_0x14; /* first byte of this contains language */
    int field3_0x18;
    undefined field4_0x1c;
    undefined field5_0x1d;
    undefined field6_0x1e;
    undefined field7_0x1f;
    undefined field8_0x20;
    undefined field9_0x21;
    undefined field10_0x22;
    undefined field11_0x23;
    int screenWidth;
    int screenHeight;
    int screenColourDepth;
    undefined field15_0x30_field14704_0x399a;
};

#endif
