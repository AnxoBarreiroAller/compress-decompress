#ifndef COMPRESS_H
#define COMPRESS_H


#include "compress-decompress.h"

/*--------------------------------------------*
    Struct, Enums and Defines declaration 
----------------------------------------------*/
BYTE g_alphabetTable[MAX_ALPHABET_ELEMENTS];
uint8_t g_alphabetTableSize = 0;
/*------------------------------*
        Method declaration 
--------------------------------*/
void cda_processCompress(char *input, char *output);

static void cda_createAlphabetTable(BYTE* i_data_p,long dataSize, BYTE* o_table, uint8_t o_tableSize);

#endif