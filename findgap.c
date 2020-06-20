/**
 * findgap.c
 * 
 * Author: Joe Grace <joe@w1sk.com>
 * 6/20/2020
 * 
 * This program takes a number as an input. The program will
 * return the largest gap of 0's in the binary representation
 * of the number that has been input.
 * 
 * For example: 
 *      #       In Bindary  Largest Gap of Zeros
 *      9       1001        2
 *      529     1000010001  4
 *      20      10100       1
 *      15      1111        0
 *      32      100000      0
 *
 * The program takes the input number from the command lines arguments.
 * 
 * For example:
 *      ./findgap 529
 * 
 * Will return:
 *      The largest gap is: 4
 * 
 * There are a couple of constants where we can configure how big the array
 * storage needs to be to process a number and find the gap. 
 * 
 * MAX_BITS - For the binary representation of a number, the maximum amount of bits
 * MAX_INPUT_NUMBER - The number of digits in the input number.
 * 
 * To build and run:
 * gcc findgap.c -o findgap && ./findgap 529
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// How many bits wide should our bin rep. be
#define MAX_BITS 1000
#define MAX_INPUT_NUMER 100

// Functions
const int* getBinRep(int inNum);
int findLargestGap(const int* in);

int main(int argc, char *argv[]) 
{
    // Storage for binary rep. of number. 1000 Bits should do it
    const int* binNum;

    // The input
    char input[MAX_INPUT_NUMER];

    // Int. of input
    int number;

    // The result
    int result;

    if (argc < 2) {
        printf("You need to specify a number.\n");
        return 0;
    }

    // Copy from argv to input
    strcpy(input, argv[1]);

    // We need an int of input
    number = atoi(input);

    if (number < 0) {
        printf("Input number must be a positive integer.\n");
        return 0;
    }

    // Get the binary rep of the number
    binNum = getBinRep(number);

    // Finally find the widest gap
    result = findLargestGap(binNum);

    printf("The largest gap is: %d\n", result);

    // We done
    return 0;
}


/**
 * Function to return the binary representation of the int passed
 * 
 * Params: Number to return array of bits
 * 
 * returns char*
 */
const int* getBinRep(int inNum)
{
    char strOfNumber[MAX_INPUT_NUMER];
    int *result = calloc(MAX_BITS, sizeof(int));

    if (result == NULL) {
        printf("Memory could not be alocated");
        return NULL;
    }

    // Here we are going to convert this number to binary representation
    // and we are going to put each digit in result.
    int i = MAX_BITS;
    while(1) {
        if (inNum <= 0) {
            break;
        }

        char bit;

        bit = inNum % 2;
        inNum = floor(inNum / 2);
        result[i] = bit;

        i--;
    }

    return result;
}

/**
 * Function findLargestGap
 * 
 * This function does the meat of the work here, loops through
 * the array passed in, and finds the largest gap of zeros.
 * 
 * Params: cont int* in - The pointer to the array of the binary representation
 *      of the number bneing checked
 * 
 * Returns: int - The largest gap found
 */
int findLargestGap(const int* in)
{
    // If the high order bit is a 1, we probably have an overflow
    if (in[0] == 1) {
        printf("Did not allocate enough memory to find gap.");
        return 0;
    }

    // Main loop through 'bits'
    bool encountedOne = false;
    bool foundFirstBit = false;
    int maxGap = 0;
    int curGapCounter = 0;
    for (int i = 0; i <= MAX_BITS; i++) {
        int curBit = in[i];

        // Speeds through the padded zeroes first
        if (curBit == 0 && encountedOne == false && foundFirstBit == false) {
            continue;
        }

        if (curBit == 1 && foundFirstBit == false) {
            foundFirstBit = true;
        }

        if (encountedOne == false && curBit == 1) {
            encountedOne = true;
            continue;
        }

        if (curBit == 0 && encountedOne == true) {
            curGapCounter++;
        }

        if (curBit == 1 && encountedOne == true) {
            // This is the end of the gap. Is this gap larger than the previous?
            if (curGapCounter > maxGap) {
                maxGap = curGapCounter;
            }

            // Reset counters, 1 flag and continue
            curGapCounter = 0;
            encountedOne = false;
            continue;
        }
    }

    return maxGap;
}