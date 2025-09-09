#include "AIHelper.h"
#include "GameInfo.h"
#include "RallyData.h"

// GLOBAL: CMR2 0x005166b4
char g_aiNames[15][20] = {
    "mcrae",
    "erikson",
    "dugas",
    "baca",
    "tizot",
    "aikita",
    "huber",
    "ingauld",
    "jonsson",
    "truman",
    "jones",
    "kastis",
    "candido",
    "cooper",
    "utzman"};

// FUNCTION: CMR2 0x00407f80
int CAIHelper::FUN_00407f80(int id)
{
    unsigned char uVar1;

    if ((id < 0) || (5 < id))
        id = 0;

    uVar1 = CGameInfo::FUN_00405d90();
    if (uVar1 == 2)
        return id;

    uVar1 = CGameInfo::FUN_00405d90();
    if (uVar1 == 1)
        return id + 5;

    return id + 10;
}

// FUNCTION: CMR2 0x00407ec0
char *CAIHelper::GetNameForID(int id)
{
    unsigned int uVar1;
    unsigned int uVar2;
    int iVar3;

    uVar1 = CGameInfo::FUN_00405d80();
    if (uVar1 != 5)
    {
        if (CGameInfo::FUN_00405d80() != 6)
        {
            if (CGameInfo::FUN_00405d80() != 7)
            {
                if (id < 0 || id > 15)
                    id = 0;

                return g_aiNames[id];
            }
        }
    }

    uVar2 = RallyDataState();
    uVar2 = CAIHelper::FUN_00407f80(id - (unsigned char)uVar2);
    return g_aiNames[uVar2];
}
