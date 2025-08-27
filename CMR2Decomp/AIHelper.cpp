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

// STUB: CMR2 0x00407f80
int __stdcall FUN_00407f80(unsigned char param1)
{
    return 0;
}

// FUNCTION: CMR2 0x00407ec0
char *__stdcall AIHelper_GetNameForID(int id)
{
    unsigned int uVar1;
    unsigned int uVar2;
    int uVar3;

    uVar1 = FUN_00405d80();
    if (uVar1 != 5)
    {
        if (FUN_00405d80() != 6)
        {
            if (FUN_00405d80() != 7)
            {
                if (id < 0 || id > 15)
                    id = 0;
                return g_aiNames[id];
            }
        }
    }

    uVar2 = RallyDataState();
    uVar3 = FUN_00407f80(id - (uVar2 & 0xff));
    return g_aiNames[uVar3];
}
