#ifndef _INPUT_H
#define _INPUT_H

#include "../third_party/dx7sdk-7001/include/dinput.h"

class CInput {
public:
    static const GUID m_dInputDevice7;
    static IDirectInput7 *m_lpDirectInput7;

    static BOOL CreateDInput(void);
    static void FUN_0049c0a0(void *param1, void *param2);
    static void FUN_0049fd60(void);    
};

#endif
