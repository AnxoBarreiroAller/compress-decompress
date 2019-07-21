/* Compress decompress program
    anxo barreiro aller <anxo.barreiro@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "compress.h"

void cda_processCompress(char *input, char *output)
{

    //Local Vars
    long size;
    compressedSize_t compressionType;
    BYTE *data;
    uint8_t *translatedData;
    // Get the total file size
    cda_getFileSize(input, &size);

    // allocate memory for the data array
    data= (BYTE*)malloc(size * sizeof(BYTE));
    
    translatedData= (uint8_t*)malloc(size * sizeof(uint8_t));
    
    
    cda_readFile(input,size,data);

    cda_createAlphabetTable(data,size, g_alphabetTable, &g_alphabetTableSize, translatedData);
    // get the correct memory size to be used in order to maximize compression
    if(g_alphabetTableSize < 3U)       {compressionType = ONE_BIT;}
    else if (g_alphabetTableSize < 5U ){compressionType = TWO_BIT;}
    else if (g_alphabetTableSize < 9U ){compressionType = THREE_BIT;}
    else if (g_alphabetTableSize < 17U){compressionType = FOUR_BIT;}
    


    //Select the correct compression Algorithm
    switch (compressionType)
    {
    case ONE_BIT:
        cda_bitCompression(size,g_alphabetTable,&g_alphabetTableSize,translatedData,output,1U);
        break;
    case TWO_BIT:
        cda_bitCompression(size,g_alphabetTable,&g_alphabetTableSize,translatedData,output,2U);
        break;
    case THREE_BIT:
        cda_bitCompression(size,g_alphabetTable,&g_alphabetTableSize,translatedData,output,3U);
        break;
    case FOUR_BIT:
        cda_bitCompression(size,g_alphabetTable,&g_alphabetTableSize,translatedData,output,4U);
        break;
    
    default:
        break;
    }

    

    // free malloced arrays
    free(data);
    free(translatedData);


}


static void cda_createAlphabetTable(BYTE* i_data_p,long dataSize, BYTE* o_table, uint8_t* o_alphabetTableSize, uint8_t* o_translatedData_p)
{
    //Init table Size.
    o_table[0] = i_data_p[0];
    *o_alphabetTableSize = 1U;
    o_translatedData_p[0] = 0U;

    for (long i = 1; i < dataSize; i++) // Go thorough all file elements
    {
        bool newItem = true;
        uint8_t item = 0;
        for (uint8_t j = 0; j < *o_alphabetTableSize; j++)
        {
            if(i_data_p[i] == o_table[j])// Check if it is a new element
            {
                newItem = false;
                item = j;
            }
        }

        if(newItem)
        {
            // add new elements to index
            o_table[*o_alphabetTableSize] = i_data_p[i];
            o_translatedData_p[i] = *o_alphabetTableSize; 
            ++ (*o_alphabetTableSize);
            if(*o_alphabetTableSize >= MAX_ALPHABET_ELEMENTS)cda_errorMaxAlphElements(i, dataSize);
        }
        else
        {
            // translate data according to index
            o_translatedData_p[i] = item;
        }
    }
}

static void cda_errorMaxAlphElements(long num, long size)
{
    // create error for too many elements
    fprintf(stderr,"ERROR: Alphabet consist on more than 16 elemements");
    fprintf(stderr,"ERROR: Execution stopped at byte %ld of %ld total bytes",num,size);
    exit(EXIT_FAILURE);

}

static void cda_bitCompression(long size,BYTE* i_alphabetTable,uint8_t* alphabetTableSize, uint8_t *translatedData, char* outputData,uint8_t biteCompressSize)
{
    //open file an dwrite header
    FILE *outfile =fopen(outputData,"wb");
    cda_headerWrite( i_alphabetTable, alphabetTableSize,  outfile);
    // local vars
    uint8_t buffer =0;
    int number=0;
    uint16_t leftover = 0;
    uint8_t leftoverSize =0;

    //go trough all data
    for (long i = 0; i < size; i++)
    {
        //check if any data was left un assigned form previous byte.
        if(leftoverSize!=0)
        {
            uint8_t localSize =leftoverSize;
            //go through leftover data
            for(uint8_t k =0; k<localSize;k++)
            {
                if(leftoverSize ==0)
                {
                    leftover = 0;
                    continue;
                }
                if(buffer == 8U)continue;
                // only move data if there is anything to move (prevent weird beahviours)
                //push bit
                if(number!=0)number = number<<1;
                // is the las item is a 1 add it
                if(leftover & 1)number++;
                //pop bit
                leftover = leftover >>1;
                //reduce size
                leftoverSize--;
                // increment write buffer
                buffer++;
                if (buffer == 8U || i >= size-1U)
                {
                    cda_writeBuffer(size, &number,&buffer,i,outfile);
                }
            }
        }
        // once leftover is depleted
        // get a new item form the list.
        if(buffer < 8U)
        {
            uint8_t localValue = translatedData[i];
            for(uint8_t j=0; j <biteCompressSize;j++)
            {
                if(number!=0)number =number<<1;
                if(localValue & 1)number++;
                localValue = localValue >>1;
                buffer++;
                if(buffer == 8U)
                {
                    if(j<biteCompressSize-1U)
                    {
                        leftover = localValue;
                        leftoverSize = (biteCompressSize-1U)-j;
                    }
                    break;
                }
            }
        }

        if (buffer == 8U || i >= size-1U)
        {
            cda_writeBuffer(size, &number,&buffer,i,outfile);
        }
        
    }
    
    fclose(outfile);
   
}

static void cda_writeBuffer(long size, int* number, uint8_t* buffer,long i,FILE* outfile)
{
// write to file
        // ensure data is properly located
        if(i >= size-1U && *buffer != 8U)*number = *number << (8U-*buffer);
        cda_write2binary(*number,outfile);
        *number = 0;
        *buffer = 0;
}

static void cda_write2binary(int i_number,FILE* outfile)
{

    BYTE b = i_number & 0xFF;
    fwrite(&b, 1, 1,outfile);
}

static void cda_headerWrite(BYTE* i_alphabetTable, uint8_t* alphabetTableSize,  FILE* outfile)
{
    // first byte is the size of the reference table.
    
    BYTE b = *alphabetTableSize & 0xFF;
    fwrite(&b, 1, 1, outfile);
    // Save the reference table 1 byte per value.
    for (uint8_t i = 0; i < *alphabetTableSize; i++)
    {
        fwrite(&i_alphabetTable[i], 1, 1, outfile);
    }
}

