#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <stdio.h>
#include "compress-decompress.h"

/*--------------------------------------------*
    Struct, Enums and Defines declaration 
----------------------------------------------*/
static BYTE g_alphabetTable[MAX_ALPHABET_ELEMENTS];

/*------------------------------*
        Method declaration 
--------------------------------*/
void cda_processDecompress(char *input, char *output);

static void cda_oneBitDecompression(long compressedDataSize,BYTE* alphabetTable,uint8_t tableSize,char* data,char* output);

static void cda_twoBitDecompression(long compressedDataSize,BYTE* alphabetTable,uint8_t tableSize,char* data,char* output);

static void cda_threeBitDecompression(long compressedDataSize,BYTE* alphabetTable,uint8_t tableSize,char* data,char* output);

static void cda_fourBitDecompression(long compressedDataSize,BYTE* alphabetTable,uint8_t tableSize,char* data,char* output);

static void cda_write2binary(int i_number,FILE* outfile);

#endif