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
    uint8_t key[KEY_WORDS] = {0x90041AC92DB746E1, 0x91875EF010371D99};
    uint8_t round_keys[NUM_ROUNDS] = {0, };
    simon_key_schedule(key, round_keys);
    for(int i = 0; i < NUM_ROUNDS; i++)
    {
        printf("%d ", round_keys[i]);
    }
}