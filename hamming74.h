#include <stdint.h>
#include <stdbool.h>

/**
 * Hamming encode data
 *
 *  data: Data to encode
 *  enc: Encoded data
 */
void hamming74_encode(uint8_t data[4], uint8_t enc[7]);

/**
 * Detect if encoded data contains errors
 *
 *  enc: Encoded data
 *
 *  return: False when the data contains errors; true otherwise
 */
int hamming74_error_detect(uint8_t enc[7]);

/**
 * Correct one bit errors
 *
 *  enc: Encoded data
 *  pos: Positon of error
 */
void hamming74_error_correct(uint8_t enc[7], int pos);

/**
 * Decode Hamming 7,4 encoded data
 *
 *  enc: Encoded data
 *  data: Decoded data
 *
 *  return: True of the data could be decoded without errors; false otherwise
 */
bool hamming74_decode(uint8_t enc[7], uint8_t data[4]);

/**
 * Map encoded data to data
 *
 *  enc: Encoded data
 *  data: Decoded data
 */
void hamming74_map(uint8_t enc[7], uint8_t data[4]);
