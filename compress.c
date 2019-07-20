#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#include "compress.h"

void cda_processCompress(char *input, char *output)
{
    long size;
    
    cda_getFileSize(input, size);

    BYTE data[size];

    cda_readFile(input,size,data);

    cda_createAlphabetTable(data,size, g_alphabetTable, g_alphabetTableSize);
    

}


cda_createAlphabetTable(BYTE* i_data_p,long dataSize, BYTE* o_table, uint8_t o_tableSize)
{
    for (long i = 0; i < ; i++)
    {
        /* code */
    }
    

}