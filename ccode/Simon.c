#include "Simon.h"
/*
void simon_key_schedule(uint8_t* key, uint8_t* round_keys)
{
    round_keys[0] = key[0];
    round_keys[1] = key[1];
    uint8_t temp_1 = 0;
    uint8_t temp_2 = 0;
    for(int i = 2; i < NUM_ROUNDS; i++)
    {
        
        // (S: shift left, ⊕: bitwise XOR, mod: modulo)
        // tmp ← S^−3round_keys[i-1]
        // tmp ← tmp ⊕ S^−1tmp
        // round_keys[i] ← ~round_keys[i-2] ⊕ tmp ⊕ z[(i-m) mod 62] ⊕ 3
        
        temp_1 = round_keys[i-1];
        temp_1 = temp_1 >> 3;
        temp_2 = round_keys[i-1];
        temp_2 = temp_2 >> 1;
        temp_1 = temp_1 ^ temp_2;
        round_keys[i] = ~round_keys[i-2] ^ temp_1 ^ z[(i-2) % 62] ^ 3;
    }
}
*/

void simon_key_schedule(uint8_t key[2][8], uint8_t round_keys[NUM_ROUNDS][8])
{
    for(int i=0; i<8; i++)
    {
        round_keys[0][i] = key[0][i];
        round_keys[1][i] = key[1][i];
    }
    uint32_t temp_1 = 0;
    uint32_t temp_2 = 0;

    //temp_1 = round_keys[i-1];
    for(int i=2;i<NUM_ROUNDS;i++)
    {
        temp_1 = round_keys[i-1][0];
        temp_1 = temp_1 << 8;
        temp_1 = temp_1 | round_keys[i-1][1];
        temp_1 = temp_1 << 8;
        temp_1 = temp_1 | round_keys[i-1][2];
        temp_1 = temp_1 << 8;
        temp_1 = temp_1 | round_keys[i-1][3];
        temp_1 = temp_1 << 8;
        temp_1 = temp_1 | round_keys[i-1][4];
        temp_1 = temp_1 << 8;
        temp_1 = temp_1 | round_keys[i-1][5];
        temp_1 = temp_1 << 8;
        temp_1 = temp_1 | round_keys[i-1][6];
        temp_1 = temp_1 << 8;
        temp_1 = temp_1 | round_keys[i-1][7];
        temp_1 = temp_1 >> 3;
        temp_2 = round_keys[i-1][0];
        temp_2 = temp_2 << 8;
        temp_2 = temp_2 | round_keys[i-1][1];
        temp_2 = temp_2 << 8;
        temp_2 = temp_2 | round_keys[i-1][2];
        temp_2 = temp_2 << 8;
        temp_2 = temp_2 | round_keys[i-1][3];
        temp_2 = temp_2 << 8;
        temp_2 = temp_2 | round_keys[i-1][4];
        temp_2 = temp_2 << 8;
        temp_2 = temp_2 | round_keys[i-1][5];
        temp_2 = temp_2 << 8;
        temp_2 = temp_2 | round_keys[i-1][6];
        temp_2 = temp_2 << 8;
        temp_2 = temp_2 | round_keys[i-1][7];
        temp_2 = temp_2 >> 1;
        temp_1 = temp_1 ^ temp_2;
        round_keys[i][0] = ~round_keys[i-2][0] ^ temp_1 ^ z[(i-2) % 62] ^ 3;
    }
}

void simon_encrypt(int round, uint8_t* round_keys, uint8_t* x, uint8_t* y)
{
    
}

//라운드 키 테스트
int main()
{

}