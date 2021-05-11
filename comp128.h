#ifndef COMP128_H
#define COMP128_H

#include <stdio.h>
#include <ctype.h>

typedef unsigned char Byte;

/**
 * The main COMP128 function
**/

void A3A8(/* in */ Byte rand[16], /* in */ Byte key[16],
    /* out */ Byte simoutput[12]);

/**
 * A function with a built in key 
**/

void A3A8_Challenge(Byte rand[16], Byte simoutput[12]);

/**
 * A helper function to print hex to string.
**/
static void snprintHex(char* dst, Byte* s, int len)
{
    for (int i = 0; i < len; i++)
    {
        sprintf(dst + (i*2), "%02X", s[i]);
    }
}

/**
 * A helper function print hex to FILE
**/
static void fprintHex(FILE* outf, Byte* s, int len)
{
    for (int i = 0; i < len; i++)
    {
        fprintf(outf, "%02X", s[i]);
    }
}

#define printHex(s, l) fprintHex(stdout, s, l)

/**
 * A helper function to turn a hex char into an int
**/
static int hextoint(char x)
{
    x = toupper(x);
    if ( (x >= 'A') && (x <= 'F') )
    {
        return ( (x - 'A') + 10 );
    }
    else if ( (x >= 'a') && (x <= 'f') )
    {
        return ( (x - 'a') + 10 );
    }
    else if ( (x >= '0') && (x <= '9') )
    {
        return (x - '0');
    }
    return (-1);
}

#endif
