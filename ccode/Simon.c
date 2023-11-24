#include "Simon.h"

void simon_key_schedule(uint64_t* key, uint64_t* round_keys)
{
    round_keys[0] = key[0];
    round_keys[1] = key[1];

    uint64_t temp_1 = 0;
    uint64_t temp_2 = 0;

    for(int i = 2; i < NUM_ROUNDS; i++)
    {
        
        // (S: shift left, ⊕: bitwise XOR, mod: modulo)
        // tmp ← S^−3round_keys[i-1]
        // tmp ← tmp ⊕ S^−1tmp
        // round_keys[i] ← ~round_keys[i-2] ⊕ tmp ⊕ z[(i-m) mod 62] ⊕ 3
        
        temp_1 = round_keys[i-1];
        temp_1 = temp_1 >> 3;
        temp_2 = temp_1 >> 1;
        temp_1 = temp_1 ^ temp_2;

        round_keys[i] = ~round_keys[i-2] ^ temp_1 ^ z[(i-2) % 62] ^ 3;
    }
}

void simon_key_schedule(uint8_t key[16], uint8_t round_keys[NUM_ROUNDS][16])
{
    for(int i = 0; i < 2; i++)
    {
        round_keys[0][i] = key[i];
    }

    uint32_t temp_1 = 0;
    uint32_t temp_2 = 0;

    for(int i = 1; i < NUM_ROUNDS; i++)
    {
        // (S: shift left, ⊕: bitwise XOR, mod: modulo)
        // tmp ← S^−3round_keys[i-1]
        // tmp ← tmp ⊕ S^−1tmp
        // round_keys[i] ← ~round_keys[i-2] ⊕ tmp ⊕ z[(i-m) mod 62] ⊕ 3
        
        //temp_1에 round_keys[i-1]을 3비트 오른쪽으로 shift한 값을 저장
        for(int j = 0; j < 4; j++)
        {
            temp_1 = temp_1 << 8;
            temp_1 = temp_1 | round_keys[i-1][j];
        }
    }
}

void simon_encrypt(int round, uint8_t* round_keys, uint8_t* x, uint8_t* y)
{
    
}

//라운드 키 테스트
int main()
{
    uint64_t key[2] = {0x0706050403020100, 0x0f0e0d0c0b0a0908};
    uint64_t round_keys[NUM_ROUNDS];
    simon_key_schedule(key, round_keys);
    for(int i = 0; i < NUM_ROUNDS; i++)
    {
        printf("%d: ", i);
        printf("%016llx\n", round_keys[i]);
    }
    uint64_t plain[2] = {0x6373656420737265, 0x6c6c657661727420};
    printf("encrypt:\n");
    for(int i = 0; i < NUM_ROUNDS; i++)
    {
        simon_encrypt(i, round_keys, &plain[0], &plain[1]);
        printf("%016llx %016llx\n", plain[0], plain[1]);
    }
}