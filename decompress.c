/* Compress decompress program
    anxo barreiro aller <anxo.barreiro@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#include "decompress.h"

void cda_processDecompress(char *input, char *output)
{

    //local vars
    long size;
    compressedSize_t compressionSize;
    BYTE *data;

    cda_getFileSize(input,&size);


    data= (BYTE*)malloc(size * sizeof(BYTE));
    cda_readFile(input,size, data);
    //get the index size
    uint8_t alphabetTableSize =(uint8_t)(data[0]);
    //reconstruct the alphabet table indexes
    for (uint8_t i = 1; i <= alphabetTableSize; i++)
    {
        g_alphabetTableDecompress[i-1U] = data[i];
    }
    // calculate the total data size
    long compressedDataSize = size - alphabetTableSize -1U;

    if(alphabetTableSize < 3U)       {compressionSize = ONE_BIT;}
    else if (alphabetTableSize < 5U ){compressionSize = TWO_BIT;}
    else if (alphabetTableSize < 9U ){compressionSize = THREE_BIT;}
    else if (alphabetTableSize < 17U){compressionSize = FOUR_BIT;}

    // perform decompression according to the bit compression
    switch (compressionSize)
    {
    case ONE_BIT:
        cda_bitDecompression(compressedDataSize,g_alphabetTableDecompress,alphabetTableSize,data,output,1U);
        break;
    case TWO_BIT:
        cda_bitDecompression(compressedDataSize,g_alphabetTableDecompress,alphabetTableSize,data,output,2U);
        break;
    case THREE_BIT:
        cda_bitDecompression(compressedDataSize,g_alphabetTableDecompress,alphabetTableSize,data,output,3U);
        break;
    case FOUR_BIT:
        cda_bitDecompression(compressedDataSize,g_alphabetTableDecompress,alphabetTableSize,data,output,4U);
        break;
    
    default:
        break;
    }
    //Free alocated data
    free(data);
}

static void cda_bitDecompression(long compressedDataSize,BYTE* alphabetTable,uint8_t alphabetTableSize,BYTE* data,char* output,uint8_t biteCompressSize)
{
    // open output file
    FILE *outfile =fopen(output,"wb");
    //offset to properly read data
    uint8_t offset = alphabetTableSize +1U;

    //local vars
    BYTE leftover = 0;
    uint8_t leftoverSize = 0;
    uint8_t counter = 0;
    int number=0;
    
    for (long i = 0; i < compressedDataSize; i++)
    {

        if(leftoverSize!=0)
        {
            uint8_t localSize = leftoverSize;
            for (uint8_t j = 0; j < localSize; j++)
            {
                if(leftoverSize ==0)
                {
                    leftover = 0;
                    continue;
                }
                if(leftover & 1)
                {
                    
                    if(number!=0)number = number <<1;
                    number++;
                    
                }
                else
                {
                    if(number!=0)number = number <<1;
                }
                leftover = leftover>>1;
                counter++;
                leftoverSize--;

                if (counter == biteCompressSize)
                {
                    //put digits on the proper side of the number to inversion
                    if(number!=0)number =number << (8 -biteCompressSize);
                    //reverse again since the data went thourgh another bit shift pop loop
                    number = (number* 0x0202020202ULL & 0x010884422010ULL) % 1023;
                    cda_write2binary(alphabetTable[(uint8_t)number], outfile);
                    number = 0;
                    counter = 0;
                
                }
                
            }
            
        }
        int current;
        current = (data[i+offset]* 0x0202020202ULL & 0x010884422010ULL) % 1023;

        for (uint8_t j = 0; j < 8; j++)
        {
            if(current & 1)
            {
                if(number!=0)number = number <<1;
                number++;
                
            }
            else
            {
                if(number!=0)number = number <<1;
            }
            current = current>>1;
            counter++;
            
            if (counter == biteCompressSize)
            {
                //reverse again since the data went thourgh another bit shift pop loop
                if(number!=0)number =number <<(8-biteCompressSize);
                number = (number* 0x0202020202ULL & 0x010884422010ULL) % 1023;
                cda_write2binary(alphabetTable[(uint8_t)number], outfile);
                number = 0;
                counter = 0;
            
            }
            if(j==7 && counter!=0)
            {
                if(number!=0)number =number <<(8-counter);
                number = (number* 0x0202020202ULL & 0x010884422010ULL) % 1023;
                leftover=number;
                leftoverSize = counter;
                counter =0;
                number =0;
            }
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