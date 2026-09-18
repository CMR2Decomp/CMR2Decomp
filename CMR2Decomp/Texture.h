#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "GenericFileLoader.h"
#include "../third_party/dx7sdk-7001/include/ddraw.h"

struct Texture {
    void*                   buffer;
    USHORT                  textureId;
    BYTE                    field_0x2[134];
    BYTE                    field_0x134[140];
    IDirectDrawSurface7*    pSurface;
    BYTE                    field_288[612];
};

struct TextureInfo {
    DDSURFACEDESC2 ddsd;
    BYTE field_0x7c;
    BYTE field_0x7d;
    BYTE field_0x7e;
    BYTE field_0x7f;
    BYTE field_0x80;
    BYTE field_0x81;
    BYTE field_0x82;
    BYTE field_0x83;
};

class CTexture {
public:
    static Texture* FindLoadTexture(GenericFile* pFile, char* textureName, bool *didLoadTexture, LPVOID param4, bool param5, unsigned int flag);
};

#endif
