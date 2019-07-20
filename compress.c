#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "compress.h"

void cda_processCompress(char *input, char *output)
{
    long size;
    
    cda_getFileSize(input, size);

    BYTE *data;
    *data= (BYTE*)malloc(size * sizeof(BYTE));
    uint8_t translatedData[size];
    *translatedData= (uint8_t*)malloc(size * sizeof(uint8_t));
    cda_readFile(input,size,data);

    cda_createAlphabetTable(data,size, g_alphabetTable, g_alphabetTableSize, translatedData);
    


    free(data);
    free(translatedData);

}


cda_createAlphabetTable(BYTE* i_data_p,long dataSize, BYTE* o_table, uint8_t o_tableSize, uint8_t* o_translatedData_p)
{
    //Init table Size.
    o_table[0] = i_data_p[0];
    o_tableSize = 1U;
    o_translatedData_p[0] = 0U;


    for (long i = 1; i < dataSize; i++)
    {
        bool newItem = true;
        uint8_t item = 0;
        for (uint8_t j = 0; j < o_tableSize; j++)
        {
            if(i_data_p[i] == o_table[j])
            {
                newItem = false;
                item = j;
            }

            if(newItem)
            {
                o_table[o_tableSize] = i_data_p[i];
                o_translatedData_p[i] = o_tableSize; 
                ++o_tableSize;
            }
            else
            {
                o_translatedData_p[i] = item;
            }
        }
    }
}