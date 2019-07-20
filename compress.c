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
    
    cda_getFileSize(input, &size);

    
    data= (BYTE*)malloc(size * sizeof(BYTE));
    
    translatedData= (uint8_t*)malloc(size * sizeof(uint8_t));
    
    
    cda_readFile(input,size,data);

    cda_createAlphabetTable(data,size, g_alphabetTable, &g_alphabetTableSize, translatedData);
    // get the correct memory size to be used in order to maximize compression
    if(g_alphabetTableSize < 3U)       {compressionSize = ONE_BIT;}
    else if (g_alphabetTableSize < 5U ){compressionSize = TWO_BIT;}
    else if (g_alphabetTableSize < 9U ){compressionSize = THREE_BIT;}
    else if (g_alphabetTableSize < 17U){compressionSize = FOUR_BIT;}
    


    //Select the correct compression Algorithm
    switch (compressionSize)
    {
    case ONE_BIT:
        cda_oneBitCompression(size,g_alphabetTable,&g_alphabetTableSize,translatedData,output);
        break;
    case TWO_BIT:
        cda_twoBitCompression(size,g_alphabetTable,&g_alphabetTableSize,translatedData,output);
        break;
    case THREE_BIT:
        cda_threeBitCompression(size,g_alphabetTable,&g_alphabetTableSize,translatedData,output);
        break;
    case FOUR_BIT:
        cda_fourBitCompression(size,g_alphabetTable,&g_alphabetTableSize,translatedData,output);
        break;
    
    default:
        break;
    }

    

    // free malloced arrays
    free(data);
    free(translatedData);
    exit(EXIT_SUCCESS);


}


static void cda_createAlphabetTable(BYTE* i_data_p,long dataSize, BYTE* o_table, uint8_t* o_tableSize, uint8_t* o_translatedData_p)
{
    //Init table Size.
    o_table[0] = i_data_p[0];
    *o_tableSize = 1U;
    o_translatedData_p[0] = 0U;

    for (long i = 1; i < dataSize; i++) // Go thorough all file elements
    {
        bool newItem = true;
        uint8_t item = 0;
        for (uint8_t j = 0; j < *o_tableSize; j++)
        {
            if(i_data_p[i] == o_table[j])// Check if it is a new element
            {
                newItem = false;
                item = j;
            }
        }

        if(newItem)
        {
            o_table[*o_tableSize] = i_data_p[i];
            o_translatedData_p[i] = *o_tableSize; 
            ++ (*o_tableSize);
            if(*o_tableSize >= MAX_ALPHABET_ELEMENTS)cda_errorMaxAlphElements(i, dataSize);
        }
        else
        {
            o_translatedData_p[i] = item;
        }
    }
}

static void cda_errorMaxAlphElements(long num, long size)
{
    fprintf(stderr,"ERROR: Alphabet consist on more than 16 elemements");
    fprintf(stderr,"ERROR: Execution stopped at byte %ld of %ld total bytes",num,size);
    exit(EXIT_FAILURE);

}


static void cda_oneBitCompression(long size,BYTE* i_alphabetTable,uint8_t* alphabetTableSize, uint8_t *translatedData, char* outputData)
{
    FILE *outfile =fopen(outputData,"wb");
    cda_headerWrite( i_alphabetTable, alphabetTableSize,  outfile);

    uint8_t buffer =0;
    int number=0;

    for (long i = 0; i < size; i++)
    {
        
        
        if(number!=0)number =number<<1;
        number += translatedData[i];
        buffer++;

        if (buffer == 8|| i >= size-1U)
        {
            cda_write2binary(number,outfile);
            number = 0;
            buffer = 0;
        }
        
    }
    
    fclose(outfile);
    
}

static void cda_twoBitCompression(long size,BYTE* i_alphabetTable,uint8_t* alphabetTableSize, uint8_t *translatedData, char* outputData)
{
    FILE *outfile =fopen(outputData,"wb");
    cda_headerWrite( i_alphabetTable, alphabetTableSize,  outfile);
    uint8_t buffer = 0;
    int number = 0;
    for (long i = 0; i < size; i++)
    {
        
        
        
        if(number!=0)number =number<<2;
        number += translatedData[i];
        buffer +=2U;

        if (buffer == 4 || i >= size-1U)
        {
            cda_write2binary(number,outfile);
            number = 0;
            buffer = 0;
        }
        
    }
    
    fclose(outfile);
    
}

static void cda_threeBitCompression(long size,BYTE* i_alphabetTable,uint8_t* alphabetTableSize, uint8_t *translatedData, char* outputData)
{
    FILE *outfile =fopen(outputData,"wb");
    cda_headerWrite( i_alphabetTable, alphabetTableSize,  outfile);
    
    uint8_t buffer =0;
    int number=0;
    uint16_t leftover = 0;
    uint8_t leftoverSize =0;

    for (long i = 0; i < size; i++)
    {
        if(leftoverSize!=0)
        {
            uint8_t localSize =leftoverSize;
            for(uint8_t k =0; k<localSize;k++)
            {
                if(leftover & 1)
                {
                    
                    if(number!=0)number = number<<1;
                    number++;
                    leftover = leftover >>1;
                    leftoverSize--;
                    buffer++;
                    if(buffer == 8U)break;
                }
                else
                {
                    leftover = leftover >>1;
                    if(number!=0)number =number<<1;
                    buffer++;
                    leftoverSize--;
                    if(buffer == 8U)break;
                }
                
            }
        }
        if(buffer < 8U)
        {
            uint8_t localValue = translatedData[i];
            for(uint8_t j=0; j <3U;j++)
            {
                
                if(localValue & 1)
                {
                    if(number!=0)number =number<<1;
                    number++;
                    localValue = localValue >>1;
                    buffer++;
                    if(buffer == 8U)
                    {
                        if(j<2)
                        {
                            leftover = localValue;
                            leftoverSize = 2U-j;
                        }
                        break;
                    }
                }
                else
                {
                    localValue = localValue >>1;
                    if(number!=0)number =number<<1;
                    buffer++;
                    if(buffer == 8U)
                    {
                        if(j<2)
                        {
                            leftover = localValue;
                            leftoverSize = 2U-j;
                        }
                        break;
                    }
                }
                
            }
        }

        if (buffer == 8U || i >= size-1U)
        {
            cda_write2binary(number,outfile);
            number = 0;
            buffer = 0;
        }
        
    }
    
    fclose(outfile);
   
}

static void cda_fourBitCompression(long size,BYTE* i_alphabetTable, uint8_t* alphabetTableSize, uint8_t *translatedData, char* outputData)
{
    FILE *outfile =fopen(outputData,"wb");
    // create the size and index for our data structure.
    cda_headerWrite( i_alphabetTable, alphabetTableSize,  outfile);
    
    //local Vars
    uint8_t buffer =0;
    int number =0;
    
    for (long i = 0; i < size; i++)
    {
        //add the element to the 4 last bits
        //shift the value to make room for the next element
        if(number!=0)number<<4;
        number += translatedData[i];
        
        // update our buffer status
        buffer +=4U;

        // if the buffer is full or we are at the last element write the buffer on the binary output file.
        if (buffer == 8U || i >= size-1U)
        {
            cda_write2binary(number,outfile);
            number = 0;
            buffer = 0;
        }
        
    }
    
    fclose(outfile);
}


static void cda_write2binary(int i_number,FILE* outfile)
{
    //translates the uint number to char
  
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

