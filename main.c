#include "comp128.h"

#include <stdio.h>

//Included to address warnings
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void printUsage(FILE* outf, char* argv0)
{
    fprintf(outf, "Usage: %s 0x<rand> 0x<key> \n", argv0);
    fprintf(outf, "  Computes COMP128 for <rand> and <key> \n");
    fprintf(outf, "\n");
    fprintf(outf, "Usage: %s 0x<rand> \n", argv0);
    fprintf(outf, "  Computes COMP128 for <rand> using built in key.\n");
    fprintf(outf, "\n");
    fprintf(outf, "Usage: %s 0x<rand> bytePos [0x<start>] [0x<end>]\n", argv0);
    fprintf(outf, "  Run COMP128 in brute force mode on built in key\n");
    fprintf(outf, "    User passes in a <rand> challenge and the program \n");
    fprintf(outf, "    iterates through all possible 2^16 combinations of values\n");
    fprintf(outf, "    at byte positions bytePos and bytePos+8. \n");
    fprintf(outf, "  [0x<start>] and [0x<end>] are optional. \n");
    fprintf(outf, "  Example: %s 0xCA00000000000000FE00000000000000 0 \n", argv0);
    fprintf(outf, "    Iterates from 0x00000000000000000000000000000000 to \n");
    fprintf(outf, "                  0xFF00000000000000FF00000000000000 \n");
    fprintf(outf, "      and compares the output with that of 0xCA...FE...\n");
    fprintf(outf, "           %s 0xCA00000000000000FE00000000000000 1 0x12 0x34 \n", argv0);
    fprintf(outf, "    Iterates from 0x00120000000000000000000000000000 to \n");
    fprintf(outf, "                  0x003400000000000000FF000000000000 \n");
}

int main(int argc, char **argv)
{
    Byte rand[16] = { 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00};
    Byte rand2[16] = {0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00};
    Byte simoutput[12];
    Byte simoutput2[12];
    int bitPos = 0;
    int start = 0;
    int end = 0;
    int i = 0;
    int j = 0;

    if ( (argc < 2) 
         || (strlen(argv[1]) != 34)
         || (strncmp(argv[1], "0x", 2) != 0)
       ) 
    {
        printUsage(stderr, argv[0]);
        exit(1);
    }

    for (i=0; i<16; i++) 
    {
        rand[i] = (hextoint(argv[1][2*i+2])<<4)
                 | hextoint(argv[1][2*i+3]);
    }

    //first case where we are using built-in key
    if (argc == 2) 
    {
        A3A8_Challenge(rand, simoutput);
        printHex(simoutput, 12);
        printf("\n");
        return (0);
    } 

    //next process the COMP128 base case
    if ( strncmp(argv[2], "0x", 2) == 0 )
    {
        for (i=0; i<16; i++) 
        {
            rand2[i] = (hextoint(argv[2][2*i+2])<<4)
                      | hextoint(argv[2][2*i+3]);
        }

        A3A8(rand, rand2, simoutput);
        printHex(simoutput, 12);
        printf("\n");
        return (0);
    }
        
    //if its the other option
    bitPos = (argv[2][0] - '0');
    if ( (bitPos < 0) || (bitPos > 7) )
    {
        printUsage(stderr, argv[0]);
        exit(1);
    }

    if (argc >= 4)
    {
        if (strncmp(argv[3], "0x", 2) != 0)
        {
            printUsage(stderr, argv[0]);
            exit(1);
        }

        start = (hextoint(argv[3][2])<<4)
               | hextoint(argv[3][3]);
    }
    else
    {
        start = 0x00;
    }

    if (argc == 5)
    {
        if (strncmp(argv[4], "0x", 2) != 0)
        {
            printUsage(stderr, argv[0]);
            exit(1);
        }

        end = (hextoint(argv[4][2])<<4)
             | hextoint(argv[4][3]);
    }
    else
    {
        end = 0xFF;
    }

    A3A8_Challenge(rand, simoutput);

    for (i = start; i <= end ; i++)
    {
        for (j = 0; j < 0x100; j++)
        {
            rand2[bitPos] = i;
            rand2[bitPos+8] = j;
            if (rand[bitPos] == rand2[bitPos] && rand[bitPos+8] == rand2[bitPos+8])
            {
                continue;
            }
            A3A8_Challenge(rand2, simoutput2);
            if (memcmp(simoutput, simoutput2, 12) == 0)
            {
                printHex(rand, 16);
                printf("\n");
                printHex(simoutput, 12);
                printf("\n");
                printHex(rand2, 16);
                printf("\n");
                printHex(simoutput2, 12);
                printf("\n");
                return 0;
            }
        }
    }
    return 1;
} 

