#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main()
{
    uint64_t z=0b10101111011100000011010010011000101000010001111110010110110011;
    printf("sizeof(uint8_t) = %lu\n", sizeof(uint8_t));
    printf("sizeof(z) = %lu\n", sizeof(z));
    //맨 앞부터 한 비트씩 temp에 저장
    uint8_t temp = 0;
    for(int i = 0; i < 64; i++)
    {
        temp = (z >> (62 - i)) & 0b1;
        printf("%d", temp);
    }
    printf("\n");

    uint8_t t[3][2] = {{0x2, 0x3}, {0x4, 0x5}, {0x6, 0x7}};
    uint32_t t2=0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            t2 = t2 << 8;
            t2 = t2 | t[i][j];
            printf("t2 = %x\n", t2);
        }
    }
    printf("t2 = %x\n", t2);
}