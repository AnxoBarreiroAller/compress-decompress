#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "compress-decompress.h"

void cda_getFileSize(char* file_p, long o_size)
{
   
    FILE *p;
    p = fopen(file_p,"rb");
    fseek (p, 0 , SEEK_END);
    o_size = ftell (p) ;
    rewind (p);
}

void cda_readFile(char* file_p, long i_size, BYTE* o_data_p)
{
    FILE *logFile = fopen("/sd/PCE001.bin","rb");
    if (!logFile)
    {  
        fprintf(stderr,"FAILED TO OPEN FILE\n"); 
        exit(EXIT_FAILURE);
    }
    else 
    { 
        fread((BYTE*)o_data_p,sizeof(BYTE),i_size,logFile); 
    }
}