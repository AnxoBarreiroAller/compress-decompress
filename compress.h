#ifndef COMPRESS_H
#define COMPRESS_H


#include "compress-decompress.h"

/*--------------------------------------------*
    Struct, Enums and Defines declaration 
----------------------------------------------*/
static BYTE g_alphabetTable[MAX_ALPHABET_ELEMENTS];
static uint8_t g_alphabetTableSize = 0;



/*------------------------------*
        Method declaration 
--------------------------------*/

/*
* fn        cda_processCompress(char *input, char *output)
*
* brief     processes all necessary methods to to perfomr byte compression
*
*  param [input]  *input    file input adress
*
*  param [input]  *output   file output adress
*/
void cda_processCompress(char *input, char *output);

/*
* fn        cda_createAlphabetTable(BYTE* i_data_p,long dataSize, BYTE* o_table, uint8_t* o_alphabetTableSize,uint8_t* o_translatedData_p)
*
* brief     creates the alphabet index table
*
*  param [input]  i_data_p              Input data
*
*  param [input]  dataSize              Size of the data array
*
*  param [output] o_table               Index table
*
*  param [output] o_alphabetTableSize           Size of the index table
*
*  param [output] o_translatedData_p    translateg data array
*/
static void cda_createAlphabetTable(BYTE* i_data_p,long dataSize, BYTE* o_table, uint8_t* o_alphabetTableSize,uint8_t* o_translatedData_p);




/*
*  fn        cda_errorMaxAlphElements(long num, long size)
*
*  brief     Throws error if index table is overflowed
*
*  param [input]  num     Element where the error was generated
*
*  param [input]  size    total array size.
*
*/
static void cda_errorMaxAlphElements(long num, long size);



/*
*  fn        cda_bitCompression(long size,BYTE* i_alphabetTable,uint8_t* alphabetTableSize,uint8_t *translatedData,char* outputData,uint8_t bibiteCompressSize);
*
*  brief     Creates the compressed file
*
*  param [input]  size                Total array size.
*
*  param [input]  i_alphabetTable     Alphabet index table
*
*  param [input]  alphabetTableSize   Size of the alphabet table
*
*  param [input]  translatedData      Translate table array
*
*  param [input]  outputData          output data adress
*
*  param [input]  biteCompressSize    Size of the compression data.
*/
static void cda_bitCompression(long size,BYTE* i_alphabetTable,uint8_t* alphabetTableSize,uint8_t *translatedData,char* outputData,uint8_t biteCompressSize);

/*
* fn        cda_headerWrite(BYTE* i_alphabetTable, uint8_t* alphabetTableSize,  FILE* outfile);
*
*  brief     Creates the header for the compressed file
*
*  param [input]  i_alphabetTable     Alphabet index table
*
*  param [input]  alphabetTableSize   Size of the alphabet table
*
*  param [input]  outfile             output file.
*/
static void cda_headerWrite(BYTE* i_alphabetTable, uint8_t* alphabetTableSize,  FILE* outfile);

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