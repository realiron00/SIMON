#include "Simon.h"

void simon_key_schedule(uint8_t* key, uint8_t* round_keys)
{
    round_keys[0] = key[0];
    round_keys[1] = key[1];
    uint8_t temp_1 = 0;
    uint8_t temp_2 = 0;
    for(int i = 2; i < NUM_ROUNDS; i++)
    {
        /*
        (S: shift left, ⊕: bitwise XOR, mod: modulo)
        tmp ← S^−3round_keys[i-1]
        tmp ← tmp ⊕ S^−1tmp
        round_keys[i] ← ~round_keys[i-2] ⊕ tmp ⊕ z[(i-m) mod 62] ⊕ 3
        */
        temp_1 = round_keys[i-1];
        temp_1 = temp_1 >> 3;
        temp_2 = round_keys[i-1];
        temp_2 = temp_2 >> 1;
        temp_1 = temp_1 ^ temp_2;
        round_keys[i] = ~round_keys[i-2] ^ temp_1 ^ z[(i-2) % 62] ^ 3;
    }
}

void simon_encrypt(int round, uint8_t* round_keys, uint8_t* x, uint8_t* y)
{
    
}

//라운드 키 테스트
int main()
{
    uint8_t key[KEY_WORDS][WORD_SIZE] = 
    {
        {
            0x80, 0x79, 0x78, 0x77, 0x76, 0x75, 0x74,
            0x73, 0x72, 0x71, 0x70, 0x6F, 0x6E, 0x6D,
            0x6C, 0x6B
        }, 
        {
            0x60, 0x69, 0x68, 0x67, 0x66, 0x65, 0x64,
            0x63, 0x62, 0x61, 0x60, 0x5F, 0x5E, 0x5D,
            0x5C, 0x5B
        }
    };
    uint8_t round_keys[NUM_ROUNDS][WORD_SIZE] = {0, };
}