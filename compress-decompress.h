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

typedef enum
{
    ONE_BIT=0,
    TWO_BIT,
    THREE_BIT,
    FOUR_BIT
}compressedSize_t;

/*------------------------------*
        Method declaration 
--------------------------------*/
/*
*  fn        cvoid cda_printHelp();
*
*  brief     Prints Usage and help
*
*/
void cda_printHelp();
/*
*  fn        cda_getFileSize(char* file_p, long* o_size)
*
*  brief     calculates the total file length
*
*  param [input]  file_p     file name
*
*  param [output]  o_size    file size.
*/
void cda_getFileSize(char* file_p, long* o_size);

/*
*  fn        cda_readFile(char* file_p, long i_size, BYTE* o_data_p);
*
*  brief     calculates the total file length
*
*  param [input]  file_p     file name
*
*  param [output]  o_size    file size.
*/
void cda_readFile(char* file_p, long i_size, BYTE* o_data_p);

#endif