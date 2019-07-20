#ifndef COMPRESS_DECOMPRESS_H
#define COMPRESS_DECOMPRESS_H

/*--------------------------------------------*
    Struct, Enums and defines declaration 
----------------------------------------------*/
typedef enum
{
    NONE = 0,
    COMPRESS,
    ACCESS_COMPRESS,
    DECOMPRESS
}functionality_t;
/*------------------------------*
        Method declaration 
--------------------------------*/
void cda_printHelp();

#endif