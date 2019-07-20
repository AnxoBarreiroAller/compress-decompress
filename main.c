/* Compress decompress program
    anxo barreiro aller <anxo.barreiro@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "compress.h"
#include "decompress.h"
#include "compress-decompress.h"

int main (int argc, char* argv[])
{
    if(argc < 2U)
    {
        fprintf(stderr, "Not enough arguments. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    for (unit16_t i = 0; i < count; i++)
    {
        /* code */
    }
    
}