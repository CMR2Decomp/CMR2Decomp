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