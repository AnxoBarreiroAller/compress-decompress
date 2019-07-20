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
    functionality_t func=NONE;
    char* directory;
    if(argc < 2U)
    {
        fprintf(stderr, "Not enough arguments. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    for (uint16_t i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i],"-h"))
        {
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
            directory = argv[i+1U];
            if(directory == NULL)
            {
                fprintf(stderr," No file address and name specified, please provide one \n");
                exit(EXIT_FAILURE);
            }
            else
            {
                /* code */
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
        fprintf(stderr," No behaviour specified, please choose -compress or -decompress \n");
        exit(EXIT_FAILURE);
        break;
    case DECOMPRESS:
        fprintf(stderr," No behaviour specified, please choose -compress or -decompress \n");
        exit(EXIT_FAILURE);
        break;
    
    default:
        break;
    }
    
    
    
}



void cda_printHelp()
{
    fprintf(stderr,"");
}