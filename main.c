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
                input = argv[i+1U];
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
                output = argv[i+1U];
                ++i;
            }
            

        }
        
    }

    switch (func)
    {
    case NONE:
        fprintf(stderr," No behaviour specified, please choose -compress or -decompress \n");
        exit(EXIT_FAILURE);
        break;
    case COMPRESS:
        fprintf(stderr," Compression selected \n");
        cda_processCompress(input,output);
        break;
    case DECOMPRESS:
        fprintf(stderr," Decompression selected \n");
        cda_processDecompress(input,output);
        break;
     case ACCESS_COMPRESS:
        fprintf(stderr," Access compressed file feature not implemented yet selected \n");
        exit(EXIT_FAILURE);
        break;
     case TESTING:
        fprintf(stderr," Testing feature not implemented yet selected \n");
        exit(EXIT_FAILURE);
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
    fprintf(stderr,"\t -o \t \t\t Path and name of the output file \n");
    
    
    
    exit(EXIT_FAILURE);
}