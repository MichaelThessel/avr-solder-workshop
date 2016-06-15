/**
 * Hamming 7,4 encode and decode
 *
 * code based on:
 * https://en.wikipedia.org/wiki/Hamming(7,4)
 */
#include "hamming74.h"

// Generator Matrix
uint8_t G[7][4] = {
    {1, 1, 0, 1},
    {1, 0, 1, 1},
    {1, 0, 0, 0},
    {0, 1, 1, 1},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};

// Parity check matrix
uint8_t H[3][7] = {
    {1, 0, 1, 0, 1, 0, 1},
    {0, 1, 1, 0, 0, 1, 1},
    {0, 0, 0, 1, 1, 1, 1}
};

void hamming74_encode(uint8_t data[4], uint8_t enc[7])
{
    uint8_t i, j;
    for (i = 0; i < 7; i++) {
        enc[i] = 0;
        for (j = 0; j < 4; j++) {
            if (G[i][j] & data[j]) {
                enc[i]++;
            }
        }
    }

    for (i = 0; i < 7; i++) {
        enc[i] = enc[i] % 2 == 0 ? 0 : 1;
    }
}

int hamming74_error_detect(uint8_t enc[7])
{
    uint8_t i, j, z[3] = {0, 0, 0};
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 7; j++) {
            if (H[i][j] & enc[j]) {
                z[i]++;
            }
        }
    }

    for (i = 0; i < 3; i++) {
        z[i] = z[i] % 2 == 0 ? 0 : 1;
    }

    return (z[0] + z[1] * 2 + z[2] * 4) - 1;
}

void hamming74_error_correct(uint8_t enc[7], int pos)
{
    enc[pos] = enc[pos] == 0 ? 1 : 0;
}

bool hamming74_decode(uint8_t enc[7], uint8_t data[4])
{
    uint8_t pos = hamming74_error_detect(enc);

    // No errors found
    if (!pos) {
        hamming74_map(enc, data);
        return true;
    }

    // Try to correct error
    hamming74_error_correct(enc, pos);
    pos = hamming74_error_detect(enc);
    if (!pos) {
        hamming74_map(enc, data);
    }

    return pos == 0;
}

void hamming74_map(uint8_t enc[7], uint8_t data[4]) {
    data[0] = enc[2];
    data[1] = enc[4];
    data[2] = enc[5];
    data[3] = enc[6];
}
