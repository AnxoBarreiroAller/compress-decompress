#ifndef COMPRESS_H
#define COMPRESS_H


#include "compress-decompress.h"

/*--------------------------------------------*
    Struct, Enums and Defines declaration 
----------------------------------------------*/
static BYTE g_alphabetTable[MAX_ALPHABET_ELEMENTS];
static uint8_t g_alphabetTableSize = 0;



/*------------------------------*
        Method declaration 
--------------------------------*/
void cda_processCompress(char *input, char *output);

static void cda_createAlphabetTable(BYTE* i_data_p,long dataSize, BYTE* o_table, uint8_t* o_tableSize,uint8_t* o_translatedData_p);

static void cda_errorMaxAlphElements(long num, long size);

static void cda_oneBitCompression(long size,BYTE* i_alphabetTable,uint8_t* alphabetTableSize,uint8_t *translatedData,char* outputData);

static void cda_twoBitCompression(long size,BYTE* i_alphabetTable,uint8_t* alphabetTableSize,uint8_t *translatedData,char* outputData);

static void cda_threeBitCompression(long size,BYTE* i_alphabetTable,uint8_t* alphabetTableSize,uint8_t *translatedData,char* outputData);

static void cda_fourBitCompression(long size,BYTE* i_alphabetTable,uint8_t* alphabetTableSize,uint8_t *translatedData,char* outputData);

static void cda_headerWrite(BYTE* i_alphabetTable, uint8_t* alphabetTableSize,  FILE* outfile);

static void cda_write2binary(int i_number,FILE* outfile);

static char* cda_convert_str2number(const char* const str, long* out);

#endif