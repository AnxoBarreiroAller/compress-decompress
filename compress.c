#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "compress.h"

void cda_processCompress(char *input, char *output)
{
    long size;
    compressedSize_t compressionSize;
    BYTE *data;
    uint8_t *translatedData;
    
    cda_getFileSize(input, size);

    
    data= (BYTE*)malloc(size * sizeof(BYTE));
    
    translatedData= (uint8_t*)malloc(size * sizeof(uint8_t));
    
    
    cda_readFile(input,size,data);

    cda_createAlphabetTable(data,size, g_alphabetTable, g_alphabetTableSize, translatedData);
    
    if(g_alphabetTableSize < 3U)       {compressionSize = ONE_BIT;}
    else if (g_alphabetTableSize < 5U ){compressionSize = TWO_BIT;}
    else if (g_alphabetTableSize < 9U ){compressionSize = THREE_BIT;}
    else if (g_alphabetTableSize < 17U){compressionSize = FOUR_BIT;}
    // The outputSize represents the length in bytes of the output file, 4 bits for the tableSize
    //  tableSize bytes for the index table reference and (compresionSize * size)/(8) bytes for the actual compressed data
    long outputSize = 1U + g_alphabetTableSize + ceil(((uint8_t)(compressionSize) +1U)*size/8);
    BYTE *outputData;
    outputData= (BYTE*)malloc(outputSize * sizeof(BYTE));
    
    switch (compressionSize)
    {
    case ONE_BIT:
        cda_oneBitCompression(size,g_alphabetTable,g_alphabetTableSize,translatedData,outputData);
        break;
    case TWO_BIT:
        cda_twoBitCompression(size,g_alphabetTable,g_alphabetTableSize,translatedData,outputData);
        break;
    case THREE_BIT:
        cda_threeBitCompression(size,g_alphabetTable,g_alphabetTableSize,translatedData,outputData);
        break;
    case FOUR_BIT:
        cda_fourBitCompression(size,g_alphabetTable,g_alphabetTableSize,translatedData,outputData);
        break;
    
    default:
        break;
    }

    


    free(data);
    free(translatedData);
    free(outputData);

}


static void cda_createAlphabetTable(BYTE* i_data_p,long dataSize, BYTE* o_table, uint8_t o_tableSize, uint8_t* o_translatedData_p)
{
    //Init table Size.
    o_table[0] = i_data_p[0];
    o_tableSize = 1U;
    o_translatedData_p[0] = 0U;

    for (long i = 1; i < dataSize; i++) // Go thorough all file elements
    {
        bool newItem = true;
        uint8_t item = 0;
        for (uint8_t j = 0; j < o_tableSize; j++)
        {
            if(i_data_p[i] == o_table[j])// Check if it is a new element
            {
                newItem = false;
                item = j;
            }

            if(newItem)
            {
                o_table[o_tableSize] = i_data_p[i];
                o_translatedData_p[i] = o_tableSize; 
                ++o_tableSize;
                if(o_tableSize >= MAX_ALPHABET_ELEMENTS)cda_errorMaxAlphElements(i, dataSize);
            }
            else
            {
                o_translatedData_p[i] = item;
            }
        }
    }
}

static void cda_errorMaxAlphElements(long num, long size)
{
    fprintf(stderr,"ERROR: Alphabet consist on more than 16 elemements");
    fprintf(stderr,"ERROR: Execution stopped at byte %ld of %ld total bytes",num,size);
    exit(EXIT_FAILURE);

}


static void cda_oneBitCompression(long size,BYTE* i_alphabetTable,uint8_t g_alphabetTableSize, uint8_t *translatedData, BYTE* outputData)
{

}

static void cda_twoBitCompression(long size,BYTE* i_alphabetTable,uint8_t g_alphabetTableSize, uint8_t *translatedData, BYTE* outputData)
{

}

static void cda_threeBitCompression(long size,BYTE* i_alphabetTable,uint8_t g_alphabetTableSize, uint8_t *translatedData, BYTE* outputData)
{

}

static void cda_fourBitCompression(long size,BYTE* i_alphabetTable, uint8_t g_alphabetTableSize, uint8_t *translatedData, BYTE* outputData)
{

}



    