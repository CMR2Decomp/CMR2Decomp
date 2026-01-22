#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "GenericFileLoader.h"

struct Texture {};

class CTexture {
public:
    static Texture* FindLoadTexture(GenericFile* pFile, char* textureName, bool *didLoadTexture, LPVOID param4, bool param5, unsigned int flag);
};

#endif
