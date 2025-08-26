#ifndef _FILE_BUFFER_H
#define _FILE_BUFFER_H

void *__stdcall AllocateLockedMemoryOfSize(size_t size);
void __stdcall FreeGenericFileBuffer(void *buffer);

#endif
