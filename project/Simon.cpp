#include "Simon.h"

SIMON::SIMON(uint8_t* plain, uint8_t* key) 
{
    simon_key_schedule(key, round_keys);
}

void SIMON::simon_key_schedule(uint8_t* key, uint8_t* round_keys) 
{
    round_keys[0] = key[0];
    round_keys[1] = key[1];

    for (int i = 2; i <= NUM_ROUNDS; i++) 
    {
        uint64_t temp = round_keys[i - 1];
        uint64_t rotated = temp >> (WORD_SIZE - 3);
        round_keys[i] = (round_keys[i - 2] ^ rotated ^ temp) ^ ((0xC9 << 2) ^ (0x3ULL << 62));
    }
}




string SIMON::make_return_str(uint8_t x, uint8_t y) 
{
    ostringstream ss;
    ss << hex << setw(4) << setfill('0') << x << setw(4) << setfill('0') << y;
    return ss.str();
}