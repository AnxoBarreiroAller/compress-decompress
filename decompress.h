#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <stdio.h>
#include "compress-decompress.h"

/*--------------------------------------------*
    Struct, Enums and Defines declaration 
----------------------------------------------*/
static BYTE g_alphabetTable[MAX_ALPHABET_ELEMENTS];

/*------------------------------*
        Method declaration 
--------------------------------*/

/*
* fn        cda_processDecompress(char *input, char *output)
*
* brief     processes all necessary methods to to perfomr byte decompression and file reconstruction
*
*  param [input]  *input    file input adress
*
*  param [input]  *output   file output adress
*/
void cda_processDecompress(char *input, char *output);
/*
*  fn        cda_bitDecompression(long compressedDataSize,BYTE* alphabetTable,uint8_t alphabetTableSize,char* data,char* output, uint8_t biteCompressSize);
*
*  brief     Creates the decompressed file
*
*  param [input]  size                  Total array size.
*
*  param [input]  alphabetTable         Alphabet index table
*
*  param [input]  alphabetTableSize     Size of the alphabet table
*
*  param [input]  data                  Data array
*
*  param [input]  output                Output data adress
*
*  param [input]  biteCompressSize      Size of the compression data.
*/
static void cda_bitDecompression(long compressedDataSize,BYTE* alphabetTable,uint8_t alphabetTableSize,char* data,char* output, uint8_t biteCompressSize);

/*
*  fn        cda_write2binary(int i_number,FILE* outfile);
*
*  brief     writes data to bionary file
*
*  param [input]  i_number     data to be written
*
*  param [input]  outfile             output file.
*/
static void cda_write2binary(int i_number,FILE* outfile);

#endif