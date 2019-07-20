#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#include "decompress.h"

void cda_processDecompress(char *input, char *output)
{
    long size;
    compressedSize_t compressionSize;
    BYTE *data;

    cda_getFileSize(input,&size);


    data= (BYTE*)malloc(size * sizeof(BYTE));
    cda_readFile(input,size, data);

    uint8_t tableSize =(uint8_t)(data[0]);


    for (uint8_t i = 1; i <= tableSize; i++)
    {
        g_alphabetTable[i-1U] = data[i];
    }
    
    long compressedDataSize = size - tableSize -1U;

    if(tableSize < 3U)       {compressionSize = ONE_BIT;}
    else if (tableSize < 5U ){compressionSize = TWO_BIT;}
    else if (tableSize < 9U ){compressionSize = THREE_BIT;}
    else if (tableSize < 17U){compressionSize = FOUR_BIT;}


    switch (compressionSize)
    {
    case ONE_BIT:
        cda_oneBitDecompression(compressedDataSize,g_alphabetTable,tableSize,data,output);
        break;
    case TWO_BIT:
        cda_twoBitDecompression(compressedDataSize,g_alphabetTable,tableSize,data,output);
        break;
    case THREE_BIT:
        cda_threeBitDecompression(compressedDataSize,g_alphabetTable,tableSize,data,output);
        break;
    case FOUR_BIT:
        cda_fourBitDecompression(compressedDataSize,g_alphabetTable,tableSize,data,output);
        break;
    
    default:
        break;
    }

}

static void cda_oneBitDecompression(long compressedDataSize,BYTE* alphabetTable,uint8_t tableSize,char* data,char* output)
{
    FILE *outfile =fopen(output,"wb");
    uint8_t offset = tableSize +1U;
    
    for (long i = 0; i < compressedDataSize; i++)
    {
        //reverse the byte
        BYTE current;
        current = (data[i+offset]* 0x0202020202ULL & 0x010884422010ULL) % 1023;

        for (uint8_t j = 0; j < 8U; j++)
        {
            if(current & 1)
            {
                cda_write2binary(alphabetTable[1], outfile);
            }
            else
            {
                cda_write2binary(alphabetTable[0], outfile);
            }
            current = current>>1;
            
        }
        
    }
    fclose(outfile);
    
}
static void cda_twoBitDecompression(long compressedDataSize,BYTE* alphabetTable,uint8_t tableSize,char* data,char* output)
{
    FILE *outfile =fopen(output,"wb");
    uint8_t offset = tableSize +1U;
    
    for (long i = 0; i < compressedDataSize; i++)
    {
        //reverse the byte
        BYTE current;
        current = (data[i+offset]* 0x0202020202ULL & 0x010884422010ULL) % 1023;

        for (uint8_t j = 0; j < 4U; j++)
        {
            char index =0;
            for(uint8_t k =0;k <2U;k++)
            {
                if(current & 1)
                {
                    index++;
                    if(k==0)index = index <<1;
                }
                else
                {
                    if(k==0)index = index <<1;
                }
                current = current>>1;
            }
            //reverse again since the data went thourgh another bit shift pop loop
            index = (index* 0x0202020202ULL & 0x010884422010ULL) % 1023;

            cda_write2binary(alphabetTable[(uint8_t)index], outfile);
            
        }
        
    }
    fclose(outfile);
    
}
static void cda_threeBitDecompression(long compressedDataSize,BYTE* alphabetTable,uint8_t tableSize,char* data,char* output)
{
    FILE *outfile =fopen(output,"wb");
    uint8_t offset = tableSize +1U;
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

                if (counter == 3U)
                {
                    //put digits on the proper side of the number to inversion
                    if(number!=0)number =number <<5;
                    //reverse again since the data went thourgh another bit shift pop loop
                    number = (number* 0x0202020202ULL & 0x010884422010ULL) % 1023;
                    cda_write2binary(alphabetTable[(uint8_t)number], outfile);
                    number = 0;
                    counter = 0;
                
                }
                
            }
            
        }
        BYTE current;
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
            
            if (counter == 3U)
            {
                //reverse again since the data went thourgh another bit shift pop loop
                if(number!=0)number =number <<5;
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
static void cda_fourBitDecompression(long compressedDataSize,BYTE* alphabetTable,uint8_t tableSize,char* data,char* output)
{
    FILE *outfile =fopen(output,"wb");
    uint8_t offset = tableSize +1U;
    
    for (long i = 0; i < compressedDataSize; i++)
    {
        //reverse the byte
        BYTE current;
        current = (data[i+offset]* 0x0202020202ULL & 0x010884422010ULL) % 1023;

        for (uint8_t j = 0; j < 2U; j++)
        {
            char index =0;
            for(uint8_t k =0;k <4U;k++)
            {
                if(current & 1)
                {
                    index++;
                    if(k!=3)index = index <<1;
                }
                else
                {
                    if(k!=3)index = index <<1;
                }
                current = current>>1;
            }
            //reverse again since the data went thourgh another bit shift pop loop
            index = (index* 0x0202020202ULL & 0x010884422010ULL) % 1023;

            cda_write2binary(alphabetTable[(uint8_t)index], outfile);
            
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