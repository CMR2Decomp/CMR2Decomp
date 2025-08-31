#ifndef _BFL_H
#define _BFL_H

typedef struct _BFLHeader
{
    char ident[4];             // always CMPR
    unsigned long archiveSize; // size of BFL minus the header
} BFLHeader;

typedef struct _BFLFileList
{
    int fileSize;
    int fileOffset;
    int fileNameLength;
    // char fileName[12];
} BFLFileList;

#endif
