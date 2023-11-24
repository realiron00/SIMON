#pragma once
#ifndef SIMON_H
#define SIMON_H

#define WORD_SIZE 64
#define KEY_SIZE 128
#define NUM_ROUNDS 68
#define KEY_WORDS 2

#include <stdio.h>
#include <stdint.h>
#include <string.h>

void simon_key_schedule(uint64_t* key, uint64_t* round_keys);
void simon_encrypt(int round, uint64_t* round_keys, uint64_t* x, uint64_t* y);
//0b10101111011100000011010010011000101000010001111110010110110011
uint8_t z[WORD_SIZE-2] =
{
    0b1, 0b0, 0b1, 0b0, 0b1, 0b1, 0b1, 0b1, 
    0b0, 0b1, 0b1, 0b1, 0b0, 0b0, 0b0, 0b0, 
    0b0, 0b0, 0b1, 0b1, 0b0, 0b1, 0b0, 0b0, 
    0b1, 0b0, 0b0, 0b1, 0b1, 0b0, 0b0, 0b0, 
    0b1, 0b0, 0b1, 0b0, 0b0, 0b0, 0b0, 0b1, 
    0b0, 0b0, 0b0, 0b1, 0b1, 0b1, 0b1, 0b1, 
    0b1, 0b0, 0b0, 0b1, 0b0, 0b1, 0b1, 0b0, 
    0b1, 0b1, 0b0, 0b0, 0b1, 0b1
};
#endif