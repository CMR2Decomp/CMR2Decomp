#include "GameInfo.h"
#include "Graphics.h"
#include "Input.h"
#include "Frontend.h"
#include "InstallInfo.h"
#include "FileBuffer.h"
#include "GenericFileLoader.h"
#include "main.h"

#include <stdio.h>

// GLOBAL: CMR2 0x00516134
char gameRegionPoland[9] = "\\Poland\\";
// GLOBAL: CMR2 0x00516140
char gameRegionJapan[8] = "\\Japan\\";
// GLOBAL: CMR2 0x00516148
char gameRegionUSA[6] = "\\Usa\\";
// GLOBAL: CMR2 0x00516150
char gameRegionEurope[9] = "\\Europe\\";

GameInfo CGameInfo::m_gameInfo;
unsigned int CGameInfo::m_gameRegion;
char *CGameInfo::m_gameRegionStrings[4] = {
    gameRegionEurope, gameRegionUSA, gameRegionJapan, gameRegionPoland};

BYTE CGameInfo::m_unk0x00817574;
int CGameInfo::m_unk0x0081a754;

char CGameInfo::m_stringCMR[4] = "cmr";
char CGameInfo::m_stringGameInfoRCF[32] = "%s\\Configuration\\GameInfo.rcf";


// FUNCTION: CMR2 0x004057f0
unsigned char CGameInfo::GetGameLanguage(void)
{
    return m_gameInfo.field_0x14 & 7;
}

// FUNCTION: CMR2 0x00405800
unsigned int CGameInfo::GetGameRegion(void)
{
    return m_gameRegion;
}

// FUNCTION: CMR2 0x00405810
void CGameInfo::SetGameRegion(unsigned int region)
{
    m_gameRegion = region;
}

// FUNCTION: CMR2 0x00405820
char *CGameInfo::GetGameRegionDirectory(void)
{
    return m_gameRegionStrings[m_gameRegion];
}

// FUNCTION: CMR2 0x00405d80
unsigned char CGameInfo::FUN_00405d80(void)
{
    return m_gameInfo.field_0x14 >> 3 & 0x7f;
}

unsigned char CGameInfo::FUN_00405d90(void)
{
    return m_gameInfo.field_0x14 >> 10 & 7;
}

// FUNCTION: CMR2 0x00405c10
unsigned int CGameInfo::GetScreenWidth(void)
{
    return m_gameInfo.screenWidth;
}

// FUNCTION: CMR2 0x00405c30
unsigned int CGameInfo::GetScreenHeight(void)
{
    return m_gameInfo.screenHeight;
}

// FUNCTION: CMR2 0x00405c50
unsigned int CGameInfo::GetColourDepth(void)
{
    return m_gameInfo.screenColourDepth;
}

// FUNCTION: CMR2 0x00405c20
void CGameInfo::SetScreenWidth(unsigned int width)
{
    m_gameInfo.screenWidth = width;
}

// FUNCTION: CMR2 0x00405c40
void CGameInfo::SetScreenHeight(unsigned int height)
{
    m_gameInfo.screenHeight = height;
}

// FUNCTION: CMR2 0x00405c60
void CGameInfo::SetColourDepth(unsigned int depth)
{
    m_gameInfo.screenColourDepth = depth;
}

// FUNCTION: CMR2 0x004f4b40
void CGameInfo::FUN_004f4b40(void)
{
    switch (GetGameRegion())
    {
    case 0:
        m_unk0x0081a754 = 5;
        return;
    case 1:
        m_unk0x0081a754 = 3;
        return;
    case 2:
    case 3:
        m_unk0x0081a754 = 1;
    }
}

// FUNCTION: CMR2 0x00405de0
void CGameInfo::FUN_00405de0(BYTE param1)
{
    m_gameInfo.field_0x14 = ((param1 & 1) << 0x13) | (m_gameInfo.field_0x14 & 0xfff7ffffU);
}

// FUNCTION: CMR2 0x00510410
void CGameInfo::FUN_00510410(void)
{
    memset(&m_gameInfo, 0, sizeof(m_gameInfo));
    m_gameInfo.magicNumber = 0x11;

    strcpy(m_gameInfo.field_0x3950, CMain::m_logFileBlankLine);
    strcpy(m_gameInfo.field_0x3965, CMain::m_logFileBlankLine);

    m_gameInfo.field_0x3980 = 8;
    m_gameInfo.field_0x3990 = 8;
    m_gameInfo.field_0x9c = (m_gameInfo.field_0x9c & 0xffc11157U) | 0x11154;
    m_gameInfo.field_0x18 = (m_gameInfo.field_0x18 & 0xfcffffffU) | 0xbc000000;
    m_gameInfo.field_0x1c = (m_gameInfo.field_0x1c & 0xfff33d19U) | 0x33518;
    m_gameInfo.field_0x14 = (m_gameInfo.field_0x14 & 0x807627ffU) | 0x42400;
    m_gameInfo.field_0x397c = 10;
    m_gameInfo.field_0x3984 = 6;
    m_gameInfo.field_0x3988 = 3;
    m_gameInfo.field_0x398c = 0x1e;

    FUN_00510570();

    m_gameInfo.field_0x98 = 4;
    m_gameInfo.field_0x9a = 0;
    m_gameInfo.field_0x18 = (m_gameInfo.field_0x18 & 0xfff93264) | 0x40393264;

    FUN_00406010(&m_gameInfo.field_0xa4);
    FUN_00406010(&m_gameInfo.field_0x1368);
    FUN_00406010(&m_gameInfo.field_0x262c);

    m_gameInfo.field_0x14 = m_gameInfo.field_0x14 & 0x7fffffff;
}

// FUNCTION: CMR2 0x00510570
void CGameInfo::FUN_00510570(void)
{
    m_gameInfo.field_0x88 = 0x18000;
    m_gameInfo.field_0x8c = 0x68000;
    m_gameInfo.field_0x94 = 0x2d;
    m_gameInfo.field_0x90 = 0xe0000;
}

// FUNCTION: CMR2 0x00406010
void CGameInfo::FUN_00406010(GameInfo0xa4 *param1)
{
    char cVar1;
    int *puVar2;
    int iVar3;
    int uVar4;
    int uVar5;
    int *puVar6;
    GameInfo0xa4 *pGVar7;
    GameInfo0xa4 *puVar7;
    int *puVar8;
    int loop2;
    int iVar9;
    int loop1;
    int someLoopLimit;
    short (*pasVar10)[10];
    short *psVar11;
    int *puVar12;
    GameInfo0xa4SubStruct12 *pGVar13;
    GameInfo0xa4SubStruct8 *pGVar14;
    short (*local_10)[10];
    unsigned int *local_c;
    int local_8;
    int local_4;
    GameInfo0xa4 *pGameInfo0xa4;
    int bitMask;
    int *bitMask2;
    char *cmrString;
    char *cmrString2;

    pGameInfo0xa4 = param1;
    bitMask = (int)&param1->firstLoop[0].flags;
    loop1 = 3;
    do
    {
        loop2 = 5;
        bitMask2 = (int *)bitMask;
        do
        {
            uVar4 = 0xffffffff;
            cmrString = CGameInfo::m_stringCMR;
            do
            {
                cmrString2 = cmrString;
                if (uVar4 == 0)
                    break;
                uVar4 = uVar4 - 1;
                cmrString2 = cmrString + 1;
                cVar1 = *cmrString;
                cmrString = cmrString2;
            } while (cVar1 != '\0');
            uVar4 = ~uVar4;
            puVar6 = (int *)(cmrString2 + -uVar4);
            puVar12 = bitMask2 + -1;
            for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1)
            {
                *puVar12 = *puVar6;
                puVar6 = puVar6 + 1;
                puVar12 = puVar12 + 1;
            }
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1)
            {
                *(char *)puVar12 = (char)*puVar6;
                puVar6 = (int *)((int)puVar6 + 1);
                puVar12 = (int *)((int)puVar12 + 1);
            }
            *bitMask2 = *bitMask2 & 0xffffc000 | 0x3c000;
            bitMask = (unsigned int)(bitMask2 + 3);
            loop2 = loop2 + -1;
            *(unsigned char *)(bitMask2 + 1) = 0;
            *(unsigned char *)((int)bitMask2 + 6) = 0;
            bitMask2 = (int *)bitMask;
        } while (loop2 != 0);
        loop1 = loop1 + -1;
    } while (loop1 != 0);
    someLoopLimit = 0xcb;
    local_10 = param1->rallyStageRecordSplits + 10;
    puVar2 = (int *)&param1->secondLoop[0].flags;
    local_c = &param1->rallyStageRecordTimes[10].value;
    do
    {
        local_8 = 3;
        do
        {
            iVar9 = 5;
            puVar8 = puVar2;
            do
            {
                uVar4 = 0xffffffff;
                cmrString = CGameInfo::m_stringCMR;
                do
                {
                    cmrString2 = cmrString;
                    if (uVar4 == 0)
                        break;
                    uVar4 = uVar4 - 1;
                    cmrString2 = cmrString + 1;
                    cVar1 = *cmrString;
                    cmrString = cmrString2;
                } while (cVar1 != '\0');
                uVar4 = ~uVar4;
                puVar2 = puVar8 + 3;
                puVar6 = (int *)(cmrString2 + -uVar4);
                pGVar13 = (GameInfo0xa4SubStruct12 *)(puVar8 + -1);
                for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1)
                {
                    *(unsigned int *)pGVar13->ident = *puVar6;
                    puVar6 = puVar6 + 1;
                    pGVar13 = (GameInfo0xa4SubStruct12 *)&pGVar13->flags;
                }
                for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1)
                {
                    pGVar13->ident[0] = (char)*puVar6;
                    puVar6 = (int *)((int)puVar6 + 1);
                    pGVar13 = (GameInfo0xa4SubStruct12 *)(pGVar13->ident + 1);
                }
                *puVar8 = *puVar8 & 0xffffff80;
                puVar8[1] = 360000;
                iVar9 = iVar9 + -1;
                *puVar8 = *puVar8 & 0xffff87ff | 0x780;
                puVar8 = puVar2;
            } while (iVar9 != 0);
            local_8 = local_8 + -1;
        } while (local_8 != 0);
        iVar9 = 0;
        do
        {
            uVar4 = 0xffffffff;
            cmrString = CGameInfo::m_stringCMR;
            do
            {
                cmrString2 = cmrString;
                if (uVar4 == 0)
                    break;
                uVar4 = uVar4 - 1;
                cmrString2 = cmrString + 1;
                cVar1 = *cmrString;
                cmrString = cmrString2;
            } while (cVar1 != '\0');
            uVar4 = ~uVar4;
            cmrString = cmrString2 + -uVar4;
            puVar8 = (int *)(param1->firstLoop[0].ident + (iVar9 + someLoopLimit) * 8 + -4);
            for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1)
            {
                *puVar8 = *(char *)cmrString;
                cmrString = cmrString + 4;
                puVar8 = puVar8 + 1;
            }
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1)
            {
                *(char *)puVar8 = *cmrString;
                cmrString = cmrString + 1;
                puVar8 = (int *)((int)puVar8 + 1);
            }
            uVar4 = *(unsigned int *)(param1->firstLoop[0].ident + (iVar9 + someLoopLimit) * 8);
            puVar6 = (int *)(param1->firstLoop[0].ident + (iVar9 + someLoopLimit) * 8);
            *puVar6 = uVar4 & 0xffffff80;
            if (iVar9 == 10)
            {
                uVar4 = uVar4 & 0xffaee000 | 0x2ee000;
                puVar6 = (int *)local_c;
            }
            else
            {
                uVar4 = uVar4 & 0xffddc000 | 0x5dc000;
            }
            iVar9 = iVar9 + 1;
            *puVar6 = uVar4;
        } while (iVar9 < 0xb);
        iVar9 = 0;
        do
        {
            if (iVar9 == 10)
            {
                iVar3 = 0;
                pasVar10 = local_10;
                do
                {
                    (*pasVar10)[0] = (short)iVar3 * 12000;
                    iVar3 = iVar3 + 1;
                    pasVar10 = (short (*)[10])(*pasVar10 + 1);
                } while (iVar3 < 10);
            }
            else
            {
                iVar3 = 0;
                psVar11 = (short *)((int)param1 + (iVar9 + someLoopLimit) * 0x14 + -0x6c8);
                do
                {
                    *psVar11 = (short)iVar3 * 6000;
                    iVar3 = iVar3 + 1;
                    psVar11 = psVar11 + 1;
                } while (iVar3 < 10);
            }
            iVar9 = iVar9 + 1;
        } while (iVar9 < 0xb);
        someLoopLimit = someLoopLimit + 0xb;
        local_10 = local_10 + 0xb;
        local_c = local_c + 0x16;
    } while (someLoopLimit < 0x123);
    local_4 = 3;
    puVar2 = (int *)&param1->thirdLoop[0].flags;
    do
    {
        param1 = (GameInfo0xa4 *)0x3;
        do
        {
            iVar9 = 5;
            puVar8 = puVar2;
            do
            {
                uVar4 = 0xffffffff;
                cmrString = CGameInfo::m_stringCMR;
                do
                {
                    cmrString2 = cmrString;
                    if (uVar4 == 0)
                        break;
                    uVar4 = uVar4 - 1;
                    cmrString2 = cmrString + 1;
                    cVar1 = *cmrString;
                    cmrString = cmrString2;
                } while (cVar1 != '\0');
                uVar4 = ~uVar4;
                puVar2 = puVar8 + 3;
                puVar6 = (int *)(cmrString2 + -uVar4);
                pGVar13 = (GameInfo0xa4SubStruct12 *)(puVar8 + -1);
                for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1)
                {
                    *(unsigned int *)pGVar13->ident = *puVar6;
                    puVar6 = puVar6 + 1;
                    pGVar13 = (GameInfo0xa4SubStruct12 *)&pGVar13->flags;
                }
                for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1)
                {
                    pGVar13->ident[0] = (char)*puVar6;
                    puVar6 = (int *)((int)puVar6 + 1);
                    pGVar13 = (GameInfo0xa4SubStruct12 *)(pGVar13->ident + 1);
                }
                iVar9 = iVar9 + -1;
                *puVar8 = *puVar8 & 0xffff0280 | 0x280;
                puVar8 = puVar2;
            } while (iVar9 != 0);
            param1 = (GameInfo0xa4 *)((int)param1[-1].arcadeRecordSplits[8] + 0xb);
        } while (param1 != NULL);
        local_4 = local_4 + -1;
    } while (local_4 != 0);
    puVar6 = (int *)&pGameInfo0xa4->arcadeRecordTimes[0].value;
    puVar7 = (GameInfo0xa4 *)pGameInfo0xa4->arcadeRecordSplits;
    param1 = (GameInfo0xa4 *)0x3;
    do
    {
        iVar9 = 3;
        do
        {
            uVar4 = 0xffffffff;
            cmrString = CGameInfo::m_stringCMR;
            do
            {
                cmrString2 = cmrString;
                if (uVar4 == 0)
                    break;
                uVar4 = uVar4 - 1;
                cmrString2 = cmrString + 1;
                cVar1 = *cmrString;
                cmrString = cmrString2;
            } while (cVar1 != '\0');
            uVar4 = ~uVar4;
            puVar12 = (int *)(cmrString2 + -uVar4);
            pGVar14 = (GameInfo0xa4SubStruct8 *)(puVar6 + -1);
            for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1)
            {
                *(unsigned int *)pGVar14->ident = *puVar12;
                puVar12 = puVar12 + 1;
                pGVar14 = (GameInfo0xa4SubStruct8 *)&pGVar14->value;
            }
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1)
            {
                pGVar14->ident[0] = (char)*puVar12;
                puVar12 = (int *)((int)puVar12 + 1);
                pGVar14 = (GameInfo0xa4SubStruct8 *)(pGVar14->ident + 1);
            }
            iVar3 = 0;
            *puVar6 = *puVar6 & 0xffaee000 | 0x2ee000;
            pGVar7 = puVar7;
            do
            {
                puVar7 = (GameInfo0xa4 *)(pGVar7->firstLoop[0].ident + 2);
                *(short *)pGVar7->firstLoop[0].ident = (short)iVar3 * 6000;
                iVar3 = iVar3 + 1;
                pGVar7 = puVar7;
            } while (iVar3 < 6);
            puVar6 = puVar6 + 2;
            iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
        param1 = (GameInfo0xa4 *)((int)param1[-1].arcadeRecordSplits[8] + 0xb);
        if (param1 == NULL)
        {
            return;
        }
    } while (true);
}

// FUNCTION: CMR2 0x00406560
void CGameInfo::FUN_00406560(void)
{
    memset(m_gameInfo.field_0x38f8, 0x03, sizeof(m_gameInfo.field_0x38f8));
}

// FUNCTION: CMR2 0x00406580
void CGameInfo::FUN_00406580(void) {
    char bVar1;
    int uVar5 = 0;
    int uVar2 = 0;
    char *piVar4 = m_gameInfo.field_0x38f8;
    char *end = m_gameInfo.field_0x38f8 + sizeof(m_gameInfo.field_0x38f8);
    int iVar3 = 0;
    bool bVar6 = false;

    do {
        if ((piVar4 < (m_gameInfo.field_0x38f8 + 44)) && (*piVar4 & 2) != 0) {
            *piVar4 = *piVar4 & 0xfd;
        }

        if (uVar5 < (m_gameInfo.field_0x9c >> 8 & 0xf)) {
            iVar3 = 0;
            do {
                if ((piVar4[iVar3] & 2) != 0) {
                    piVar4[iVar3] = piVar4[iVar3] & 0xfd;
                }
                iVar3 ++;
            } while (iVar3 < 4);

            if (uVar5 < (m_gameInfo.field_0x9c >> 0xc & 0xf)) {
                iVar3 = 4;
                do {
                    if ((piVar4[iVar3] & 2) != 0) {
                        piVar4[iVar3] = piVar4[iVar3] & 0xfd;
                    }
                    iVar3 ++;
                } while (iVar3 < 8);
            
                if ((uVar5 < (m_gameInfo.field_0x9c >> 0x10 & 0xf)) && (m_gameInfo.field_0x9c & 1) != 0) {
                    iVar3 = 8;
                    do {
                        if ((piVar4[iVar3] & 2) != 0) {
                            piVar4[iVar3] = piVar4[iVar3] & 0xfd;
                        }
                        iVar3 ++;
                    } while (iVar3 < 10);
                }
            } 
        }

        uVar2 = uVar5;
        uVar2 = uVar2 & 0x80000001;

        if (uVar2 < 0) {
            uVar2 = uVar2 - 1 | 0xfffffffe;
        }
        
        uVar2++; // idk but its in the asm
        if (uVar2) {
            uVar2 = 1 << (((uVar5 + 1) / 2 - 1) & 0x1f);

            if (((((uVar2 & m_gameInfo.field_0xa0 & 0x1f) != 0) ||
                (uVar2 & m_gameInfo.field_0xa0 >> 5 & 0x1f) != 0) ||
                ((uVar2 & m_gameInfo.field_0xa0 >> 10 & 0x1f) != 0)) && ((piVar4[10] & 2) != 0)
                ) {
                piVar4[10] = piVar4[10] & 0xfd;
            }            
        } else {
            piVar4[10] = 4;
        }
        
        piVar4 = piVar4 + 0xb;
        uVar5++;
    } while (piVar4 < end);
}

// TODO: is this actually gameinfo related?
// FUNCTION: CMR2 0x0049eaf0
DWORD CGameInfo::SetupInputs(void) {
    if (CInput::DInputCreate()) {
        CInput::m_unk0x0059f8cc.field_0x0 = 0;
        CInput::m_unk0x0059f8cc.field_0x1 = 2;
        CInput::m_unk0x0059f8cc.field_0x2 = 0;
        
        int* pField18 = &CInput::m_availableDevices[0].field_0x18;
        int initVal = -1;
        
        do {
            *(pField18 - 6) = initVal;  // -24 bytes = field_0x0
            *pField18 = initVal;         // field_0x18
            pField18 = (int*)((BYTE*)pField18 + 0x50C);
        } while (pField18 < &CInput::m_availableDevices[8].field_0x18); // TODO: is this correct?
        
        CInput::SetupKeyboard();
        CInput::SetupMouse();
        CInput::GetAttachedJoysticks();
    }

    return CInput::m_unk0x0059f8cc.field_0x0 & 0xFF;
}

// FUNCTION: CMR2 0x004ea5e0
bool CGameInfo::LoadGameInfo(void) {
    char *hdPath;
    GameInfo *fileBuffer;
    size_t fileSize;
    int iVar4;
    unsigned int flag, graphicsOptions, uVar6;

    hdPath = CInstallInfo::GetGameHDPath();
    sprintf(CFrontend::m_stringDest, m_stringGameInfoRCF, hdPath);

    fileBuffer = (GameInfo*)CFileBuffer::GetGenericFileBuffer(CFrontend::m_stringDest, TRUE);
    if (fileBuffer == NULL)
        return false;

    // make sure file size is valid and that it has the magic number
    fileSize = CGenericFileLoader::GetGenericFileSize();
    if (fileSize != 0x399c || fileBuffer->magicNumber != 0x11) {
        CFileBuffer::FreeGenericFileBuffer(fileBuffer);
        return false;
    }

    memcpy(&m_gameInfo, fileBuffer, sizeof(GameInfo));

    g_pGraphics->resX = m_gameInfo.screenWidth;
    g_pGraphics->resY = m_gameInfo.screenHeight;
    g_pGraphics->depth = m_gameInfo.screenColourDepth;

    g_pGraphics->isFullscreen = IsFullscreen() & 0xff;

    graphicsOptions = m_gameInfo.unknownGraphicsOptions & 6;


    if (graphicsOptions == 2) {
        g_pGraphics->field913_0x3bc |= 0x8;  // OR with 0x8
    } else if (graphicsOptions == 4) {
        g_pGraphics->field913_0x3bc |= 0x8;
        g_pGraphics->field913_0x3bc |= 0x10;
    } else if (graphicsOptions == 6) {
        g_pGraphics->field913_0x3bc |= 0x8;
        g_pGraphics->field913_0x3bc &= ~0x10;  // Clear bit 4
        g_pGraphics->field913_0x3bc |= 0x80;   // Set bit 7
    }

    g_pGraphics->field917_0x3c0 = FUN_00405ca0();
    
    if (m_gameInfo.unknownGraphicsOptions & (1 << 27))
        g_pGraphics->field913_0x3bc |= 0x04;
    else
        g_pGraphics->field913_0x3bc &= 0xFB;
    
    uVar6 = FUN_00406410(0x11);
    if (uVar6 != 0)
        FUN_004eac50(0x11);

    FUN_004d0590(0);
    CFileBuffer::FreeGenericFileBuffer(fileBuffer);
    
    return true;
}

// FUNCTION: CMR2 0x00405b20
unsigned int CGameInfo::IsFullscreen(void) {
    return m_gameInfo.unknownGraphicsOptions & 1;
}

// FUNCTION: CMR2 0x00405ca0
unsigned int CGameInfo::FUN_00405ca0(void)
{
  return m_gameInfo.unknownGraphicsOptions >> 0x15 & 0xf;
}

int CGameInfo::FUN_00406410(BYTE param1) {
    return 0;
}

int CGameInfo::FUN_004eac50(BYTE param1) {
    return 0;
}

// FUNCTION: CMR2 0x004d0590
void CGameInfo::FUN_004d0590(BYTE param1) {
    m_unk0x00817574 = param1;
}
