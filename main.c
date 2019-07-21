/* Compress decompress program
    anxo barreiro aller <anxo.barreiro@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "compress.h"
#include "decompress.h"
#include "compress-decompress.h"

int main (int argc, char* argv[])
{
    //Local variables declaration
    functionality_t func=NONE;
    char* input;
    char* output;
    char* testNumber;

    // Check if enough arguments where passed
    if(argc < 2U)
    {
        fprintf(stderr, "Not enough arguments. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    //  Get the configuratio params.
    for (uint16_t i = 1; i < argc; ++i)
    {
        if(!strcmp(argv[i],"-h")||!strcmp(argv[i],"-help"))
        {
            // Print help
            cda_printHelp();
            exit(EXIT_FAILURE);
        }
        else if(!strcmp(argv[i],"-compress"))
        {
            func = COMPRESS;
        }
        else if (!strcmp(argv[i],"-decompress"))
        {
            func = DECOMPRESS;
        }
        else if (!strcmp(argv[i],"-consult"))
        {
            func = ACCESS_COMPRESS;
        }
        else if (!strcmp(argv[i],"-i"))
        {
            // Get the file location and name
            input = argv[i+1U];
            if(input == NULL)
            {
                // throw error in case of missind data.
                fprintf(stderr," No file input address and name specified, please provide one \n");
                exit(EXIT_FAILURE);
            }
            else
            {
                ++i;
            }
        }
        else if (!strcmp(argv[i],"-o"))
        {
            // Get the file location and name
            output = argv[i+1U];
            if(output == NULL)
            {
                // throw error in case of missind data.
                fprintf(stderr," No file output address and name specified, please provide one \n");
                exit(EXIT_FAILURE);
            }
            else
            {
                ++i;
            }
            

        }
        else if(!strcmp(argv[i],"-testing"))
        {
            func = TESTING;
            testNumber = argv[i+1U];
            if(testNumber == NULL)
            {
                // throw error in case of missind data.
                fprintf(stderr," Please Specify the number of tests to be perforrmed \n");
                exit(EXIT_FAILURE);
            }
            else
            {
                ++i;
            }
            ++i;
        }
        
    }
    //Switch to select funtionality.
    switch (func)
    {
    case NONE:
        fprintf(stderr," No behaviour specified, please choose -compress or -decompress \n");
        exit(EXIT_FAILURE);
        break;
    case COMPRESS:
        fprintf(stderr," Compression selected \n");
        cda_processCompress(input,output);
        exit(EXIT_SUCCESS);
        break;
    case DECOMPRESS:
        fprintf(stderr," Decompression selected \n");
        cda_processDecompress(input,output);
        exit(EXIT_SUCCESS);
        break;
     case ACCESS_COMPRESS:
        fprintf(stderr," Access compressed file feature not implemented yet selected \n");
        exit(EXIT_FAILURE);
        break;
     case TESTING:
        fprintf(stderr," Testing  selected \n");
        cda_testing(testNumber);
        exit(EXIT_SUCCESS);
        break;
    default:
        break;
    }
    
    
    
}



void cda_printHelp()
{
    fprintf(stderr,"HELP for Compress-Decompress program \n \n");
    fprintf(stderr,"Program must be called as ./compress-decompress -OPTION -i PATH_TO_INPUT_FILE -o PATH_TO_INPUT_FILE \n\n");
    fprintf(stderr,"\t -h / - help \t\t Displays help/usage \n");
    fprintf(stderr,"\t -compress \t\t Calls compression algorithm \n");
    fprintf(stderr,"\t -decompress \t\t Calls decompression algorithm \n");
    fprintf(stderr,"\t -accescompress \t Calls Access compresed file algorithm \n");
    fprintf(stderr,"\t -i \t \t\t Path and name of the input file \n");
    fprintf(stderr,"\t -testing \t\t Number of tests to be performed at testing folder (no need to specify location)\n");
    
    
    
    
    exit(EXIT_FAILURE);
}

void cda_testing(char* testNumber)
{
    if((uint16_t)(*testNumber) > 64)
    {
        fprintf(stderr,"Exeeded the maximum number of test. Exiting \n");
        exit(EXIT_FAILURE);
    }

    for(uint16_t i = 1; i <= (uint16_t)(*testNumber);++i)
    {
        // genrate the test input name
        char buffer1[64]; // The filename buffer.
        snprintf(buffer1, sizeof(char) * 64, "/home/anxo/compress-decompress/testing/out%i.bin", i);
        char buffer2[64]; // The filename buffer.
        snprintf(buffer2, sizeof(char) * 64, "/home/anxo/compress-decompress/testing/compressed%i.bin", i);
        char buffer3[64]; // The filename buffer.
        snprintf(buffer3, sizeof(char) * 64, "/home/anxo/compress-decompress/testing/decompressed%i.bin", i);
        //process compression
        cda_processCompress(buffer1,buffer2);
        // process decompression
        cda_processDecompress(buffer2,buffer3);

        //open files and compare them
        FILE* file1 = fopen(buffer1,"rb");
        if (!file1)
        {  
            fprintf(stderr,"FAILED TO OPEN FILE\n"); 
            exit(EXIT_FAILURE);
        }
        FILE* file2 = fopen(buffer3,"rb");
        if (!file2)
        {  
            fprintf(stderr,"FAILED TO OPEN FILE\n"); 
            exit(EXIT_FAILURE);
        }
        cda_compareBinary(file1, file2, i);
        
    }
    exit(EXIT_SUCCESS);

}

void cda_compareBinary(FILE *file1, FILE *file2,uint16_t testNum)
{
    char char1, char2;
    int equal = 0;

    while (((char1 = fgetc(file1)) != EOF) &&((char2 = fgetc(file2)) != EOF))
    {
        if (char1 == char2)
        {
            equal = 1;
            continue;
        }
        else
        {
            fseek(file1, -1, SEEK_CUR);
            equal = 0;
            break;
        }
    }

    if (equal == 0)
    {
        printf("Files of test %u are not equal :  Divergence found at %ld\n",testNum, ftell(file1)+1);
    }
    else
    {
        printf("Files of test %u are equal\n ", testNum);
    }
}