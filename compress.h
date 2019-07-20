#ifndef COMPRESS_H
#define COMPRESS_H


#include "compress-decompress.h"

/*--------------------------------------------*
    Struct, Enums and Defines declaration 
----------------------------------------------*/
BYTE g_alphabetTable[MAX_ALPHABET_ELEMENTS];
uint8_t g_alphabetTableSize = 0;

typedef enum
{
    ONE_BIT=0,
    TWO_BIT,
    THREE_BIT,
    FOUR_BIT
}compressedSize_t;

/*------------------------------*
        Method declaration 
--------------------------------*/
void cda_processCompress(char *input, char *output);

static void cda_createAlphabetTable(BYTE* i_data_p,long dataSize, BYTE* o_table, uint8_t o_tableSize,uint8_t* o_translatedData_p);

static void cda_errorMaxAlphElements(long num, long size);

static void cda_oneBitCompression(long size,BYTE* i_alphabetTable,uint8_t g_alphabetTableSize,uint8_t *translatedData,BYTE* outputData);

static void cda_twoBitCompression(long size,BYTE* i_alphabetTable,uint8_t g_alphabetTableSize,uint8_t *translatedData,BYTE* outputData);

static void cda_threeBitCompression(long size,BYTE* i_alphabetTable,uint8_t g_alphabetTableSize,uint8_t *translatedData,BYTE* outputData);

static void cda_fourBitCompression(long size,BYTE* i_alphabetTable,uint8_t g_alphabetTableSize,uint8_t *translatedData,BYTE* outputData);

static void cda_fileHeaderTable(BYTE* i_alphabetTable,uint8_t g_alphabetTableSize,BYTE* outputData);



#endif