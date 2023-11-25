#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Cipher Operation Macros
#define shift_one(x_word) (((x_word) << 1) | ((x_word) >> (word_size - 1)))     // 1 bit left shift
#define shift_eight(x_word) (((x_word) << 8) | ((x_word) >> (word_size - 8)))   // 8 bit left shift
#define shift_two(x_word) (((x_word) << 2) | ((x_word) >> (word_size - 2)))     // 2 bit left shift

#define rshift_three(x) (((x) >> 3) | (((x) & 0x7) << (word_size - 3)))         // 3 bit right shift
#define rshift_one(x)   (((x) >> 1) | (((x) & 0x1) << (word_size - 1)))         // 1 bit right shift

//z_array for key schedule
uint64_t z_array = 0b0011001101101001111110001000010100011001001011000000111011110101; //z_array[2]

// Valid Cipher Parameters
const uint8_t block_size = 128;     //block size
const uint8_t key_size = 128;       //key size
const uint8_t simon_rounds = 68;    //rounds
const uint8_t word_size = 64;       //word size
const uint8_t word_bytes = 8;       //word bytes
const uint16_t key_words = 2;       //key words

/*********************************************************************
 * simon_key_schedule : Generates round key for Simon cipher
 * 
 * input:
 * key: entered key
 * round_keys: stores round keys
*********************************************************************/
void simon_key_schedule(uint8_t* key, uint8_t* round_keys)
{
    // sub_keys : stores sub keys
    uint64_t sub_keys[2] = {0, };
    // Mask to limit a value to a specific bit size
    uint64_t mod_mask = ULLONG_MAX >> (64 - word_size);

    // Divide the input key into word-sized segments to create sub-keys
    for(int i = 0; i < key_words; i++) 
    {
        memcpy(&sub_keys[i], key + (word_bytes * i), word_bytes);
    }

    // Generate round keys
    uint64_t tmp1,tmp2;                 //temporary variables
    uint64_t c = 0xFFFFFFFFFFFFFFFC;    //constant value

    // Store First Key Schedule Entry
    memcpy(round_keys, &sub_keys[0], word_bytes);

    for(int i = 0; i < simon_rounds - 1; i++)
    {
        // tmp1 <- sub_keys[key_words - 1] << 3
        tmp1 = rshift_three(sub_keys[key_words - 1]);

        tmp2 = rshift_one(tmp1);    // tmp2 <- tmp1 << 1
        tmp1 ^= sub_keys[0];        // tmp1 <- tmp1 ^ sub_keys[0]
        tmp1 ^= tmp2;               // tmp1 <- tmp1 ^ tmp2

        tmp2 = c ^ ((z_array >> (i % 62)) & 1);

        tmp1 ^= tmp2;

        // Shift sub_keys to the left by one
        for(int j = 0; j < (key_words - 1); j++)
        {
            sub_keys[j] = sub_keys[j + 1];
        }

        // Apply bitwise AND operation with mod_mask to limit tmp1 to word size
        sub_keys[key_words - 1] = tmp1 & mod_mask;

        // Copy the generated sub-keys to the round_keys array for the current round
        memcpy(round_keys + (word_bytes * (i + 1)), &sub_keys[0], word_bytes);
    }
}

/*********************************************************************
 * simon_encrypt : Encrypts plaintext using Simon cipher
 * 
 * input:
 * round_keys: stores round keys
 * plaintext: entered plaintext
 * ciphertext: stores ciphertext
 *********************************************************************/
void simon_encrypt(uint8_t round, uint8_t* round_keys, uint8_t* plaintext, uint8_t* ciphertext)
{
    uint64_t* y_word = (uint64_t*)ciphertext;           //y_word = left half
    uint64_t* x_word = (((uint64_t*)ciphertext) + 1);   //x_word = right half

    *y_word = *((uint64_t*)plaintext);
    *x_word = *((((uint64_t*)plaintext) + 1));

    uint64_t* round_key_ptr = (uint64_t*)round_keys;   //round_key_ptr = round_keys

    for(int i = 0; i < round; i++)
    {
        //tmp = (x << 1) & (x << 8) ^ y ^ (x << 2)
        uint64_t tmp = (shift_one(*x_word) & shift_eight(*x_word)) ^ *y_word ^ shift_two(*x_word);
        *y_word = *x_word; //y = x
        *x_word = tmp ^ *(round_key_ptr + i); //x = tmp ^ round_key_ptr[i]
    }
}

int main()
{
    // round_keys : stores round keys
    uint8_t round_keys[576];

    // simon128_128_key : test key
    uint8_t simon128_128_key[] = {0x00, 0x01, 0x02, 0x03,0x04, 0x05, 0x06,0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    // simon128_128_plain : test plaintext
    uint8_t simon128_128_plain[] = {0x20, 0x74, 0x72, 0x61, 0x76, 0x65, 0x6c, 0x6c, 0x65, 0x72, 0x73, 0x20, 0x64, 0x65, 0x73, 0x63};

    // simon128_128_cipher : stores ciphertext
    uint8_t simon128_128_cipher[16];

    // Generate round keys
    simon_key_schedule(simon128_128_key, round_keys);
    // Encrypt plaintext
    simon_encrypt(simon_rounds, round_keys, simon128_128_plain, simon128_128_cipher);

    // Print ciphertext
    printf("Cipher: ");
    for(int i = 0; i < 16; i++)
    {
        printf("%02x", simon128_128_cipher[i]);
    }

    //!라운드별 암호문을 받고 싶은 경우
    /*
    uint8_t simon128_128_cipher2[68][16];
    for(int i = 0; i < 68; i++)
    {
        simon_encrypt(i + 1, round_keys, simon128_128_plain, simon128_128_cipher2[i]);
        printf("\nRound %d: ", i + 1);
        for(int j = 0; j < 16; j++)
        {
            printf("%02x", simon128_128_cipher2[i][j]);
        }
        printf("\n");
    }
    */
}