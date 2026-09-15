typedef struct IDirect3DVertexBuffer7Vtbl {
    void* QueryInterface;
    void* AddRef;
    void* Release;
    void* Lock;
    void* Unlock;
    void* ProcessVertices;
    void* GetVertexBufferDesc;
    void* Optimize;
    void* ProcessVerticesStrided;
} IDirect3DVertexBuffer7Vtbl;

typedef struct IDirect3DVertexBuffer7 {
    IDirect3DVertexBuffer7Vtbl* lpVtbl;
} IDirect3DVertexBuffer7;

typedef unsigned long DWORD;

#define DD_ROP_SPACE 8

typedef struct DDSCAPS2 {
    DWORD dwCaps;
    DWORD dwCaps2;
    DWORD dwCaps3;
    DWORD dwCaps4;
} DDSCAPS2;

typedef struct DDCAPS {
    DWORD    dwSize;                          // 0x000
    DWORD    dwCaps;                          // 0x004
    DWORD    dwCaps2;                         // 0x008
    DWORD    dwCKeyCaps;                      // 0x00c
    DWORD    dwFXCaps;                        // 0x010
    DWORD    dwFXAlphaCaps;                   // 0x014
    DWORD    dwPalCaps;                       // 0x018
    DWORD    dwSVCaps;                        // 0x01c
    DWORD    dwAlphaBltConstBitDepths;        // 0x020
    DWORD    dwAlphaBltPixelBitDepths;        // 0x024
    DWORD    dwAlphaBltSurfaceBitDepths;      // 0x028
    DWORD    dwAlphaOverlayConstBitDepths;    // 0x02c
    DWORD    dwAlphaOverlayPixelBitDepths;    // 0x030
    DWORD    dwAlphaOverlaySurfaceBitDepths;  // 0x034
    DWORD    dwZBufferBitDepths;              // 0x038
    DWORD    dwVidMemTotal;                   // 0x03c
    DWORD    dwVidMemFree;                    // 0x040
    DWORD    dwMaxVisibleOverlays;            // 0x044
    DWORD    dwCurrVisibleOverlays;           // 0x048
    DWORD    dwNumFourCCCodes;                // 0x04c
    DWORD    dwAlignBoundarySrc;              // 0x050
    DWORD    dwAlignSizeSrc;                  // 0x054
    DWORD    dwAlignBoundaryDest;             // 0x058
    DWORD    dwAlignSizeDest;                 // 0x05c
    DWORD    dwAlignStrideAlign;              // 0x060
    DWORD    dwRops[DD_ROP_SPACE];            // 0x064
    DDSCAPS2 ddsCaps;                         // 0x084
    DWORD    dwMinOverlayStretch;             // 0x094
    DWORD    dwMaxOverlayStretch;             // 0x098
    DWORD    dwMinLiveVideoStretch;           // 0x09c
    DWORD    dwMaxLiveVideoStretch;           // 0x0a0
    DWORD    dwMinHwCodecStretch;             // 0x0a4
    DWORD    dwMaxHwCodecStretch;             // 0x0a8
    DWORD    dwReserved1;                     // 0x0ac
    DWORD    dwReserved2;                     // 0x0b0
    DWORD    dwReserved3;                     // 0x0b4
    DWORD    dwSVBCaps;                       // 0x0b8
    DWORD    dwSVBCKeyCaps;                   // 0x0bc
    DWORD    dwSVBFXCaps;                     // 0x0c0
    DWORD    dwSVBRops[DD_ROP_SPACE];         // 0x0c4
    DWORD    dwVSBCaps;                       // 0x0e4
    DWORD    dwVSBCKeyCaps;                   // 0x0e8
    DWORD    dwVSBFXCaps;                     // 0x0ec
    DWORD    dwVSBRops[DD_ROP_SPACE];         // 0x0f0
    DWORD    dwSSBCaps;                       // 0x110
    DWORD    dwSSBCKeyCaps;                   // 0x114
    DWORD    dwSSBFXCaps;                     // 0x118
    DWORD    dwSSBRops[DD_ROP_SPACE];         // 0x11c
    DWORD    dwMaxVideoPorts;                 // 0x13c
    DWORD    dwCurrVideoPorts;                // 0x140
    DWORD    dwSVBCaps2;                      // 0x144
    DWORD    dwNLVBCaps;                      // 0x148
    DWORD    dwNLVBCaps2;                     // 0x14c
    DWORD    dwNLVBCKeyCaps;                  // 0x150
    DWORD    dwNLVBFXCaps;                    // 0x154
    DWORD    dwNLVBRops[DD_ROP_SPACE];        // 0x158
    DWORD reserved;
} DDCAPS, *LPDDCAPS;                          // ends at 0x178 = 376 bytes

struct DDEnumDeviceBufferEntry
{
    GUID *pGUID;                    // 0x00
    GUID guid;                      // 0x04

    DWORD capFlag80000;             // 0x14
    DWORD capRender16Bit;           // 0x18
    DWORD capFlag1;                 // 0x1C
    DWORD capFlag200;               // 0x20

    DWORD capTextureFilter1;        // 0x24
    DWORD capTextureFilter2;        // 0x28
    DWORD hasZBuffer;               // 0x2C
    DWORD zBufferBitDepth;          // 0x30
    DWORD capTextureFilter3;        // 0x34
    DWORD capHardwareRasterization; // 0x38
    DWORD unknown3C;                // 0x3C
};
