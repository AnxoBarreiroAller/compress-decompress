#ifndef COMPRESS_DECOMPRESS_H
#define COMPRESS_DECOMPRESS_H


/*--------------------------------------------*
    Struct, Enums and defines declaration 
----------------------------------------------*/
#define BYTE unsigned char
#define MAX_ALPHABET_ELEMENTS 16U

typedef enum
{
    NONE = 0,
    COMPRESS,
    ACCESS_COMPRESS,
    DECOMPRESS,
    TESTING
}functionality_t;


/*------------------------------*
        Method declaration 
--------------------------------*/
void cda_printHelp();

void cda_getFileSize(char* file_p, long o_size);
void cda_readFile(char* file_p, long i_size, BYTE* o_data_p);

#endif