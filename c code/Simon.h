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

void simon_key_schedule(uint8_t* key, uint8_t* round_keys);
void simon_encrypt(int round, uint8_t* round_keys, uint8_t* x, uint8_t* y);
string make_return_str(uint8_t x, uint8_t y);

#endif