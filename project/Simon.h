#pragma once
#ifndef SIMON_H
#define SIMON_H

#define WORD_SIZE 64
#define KEY_SIZE 128
#define NUM_ROUNDS 68
#define KEY_WORDS 2

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

class SIMON {
public:
   SIMON(uint8_t* plain, uint8_t* key);
   void simon_key_schedule(uint8_t* key, uint8_t* round_keys);
   string simon_encrypt(int round);
   uint8_t round_keys[NUM_ROUNDS + 1];
   string make_return_str(uint8_t x, uint8_t y);
   //0b10101111011100000011010010011000101000010001111110010110110011;
};

#endif