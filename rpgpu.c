#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

uint16_t pallet[8] = {0b0000011111000000,0b1111100000000000,0b0000000000011111,0b1111100000011111,0b1111111111000000,0b0000011111011111,0b1111111111011111,0xb0000000000100000};
uint8_t tile[25] = {};

// Function to write a new 3-bit value into the array
// TODO: Need to figure out how to store values that extend beyond a single byte.
void write3BitValue(uint8_t* memory, int index, uint8_t value) {
    // Calculate the byte index and bit position
    int byteIndex = 1 + (index * 3) / 8;
    int bitPosition = (index * 3) % 8;

    // Retrieve the byte at the calculated byte index
    uint8_t byte = memory[byteIndex];

    // Create a bitmask to isolate the 3 bits
    uint8_t bitmask = 0b111 << bitPosition;

    // Clear the bits and set the new value
    byte &= ~bitmask;  // Clear the bits
    byte |= (value << bitPosition);  // Set the new value

    // Store the modified byte back into the memory
    memory[byteIndex] = byte;
}

// Function to read a 3-bit value from the array
// TODO: Need to figure out how to retrieve values that extend beyond a single byte.
uint8_t read3BitValue(uint8_t* memory, int index) {
    // Calculate the byte index and bit position
    int byteIndex = 1 + (index * 3) / 8;
    int bitPosition = (index * 3) % 8;

    // Retrieve the byte at the calculated byte index
    uint8_t byte = memory[byteIndex];

    // Create a bitmask to isolate the 3 bits
    uint8_t bitmask = 0b111 << bitPosition;

    // Shift and mask the bits to get the value
    uint8_t value = (byte & bitmask) >> bitPosition;

    return value;
}

uint16_t getRow(uint8_t* memory,int row){
}

int main() {
  stdio_init_all();
  uint32_t pallet_address = &pallet[0];
  uint8_t pixels[64] = {
    1,1,2,3,3,2,1,1,
    1,2,3,7,7,3,2,1,
    2,3,7,4,4,7,3,2,
    3,7,4,3,3,4,7,3,
    3,7,4,3,3,4,7,3,
    2,3,7,4,4,7,3,2,
    1,2,3,7,7,3,2,1,
    1,1,2,3,3,2,1,1,
  };
  for(int i = 0; i<64; i++){
    write3BitValue(tile,i,pixels[i]);
  }
  volatile uint8_t test = read3BitValue(tile,5);
  uint8_t initial_offset = (0<<4);
  uint32_t pallet_offsets[8] = {};
  for(int i = 0; i<8; i++){
    uint8_t pixel_offset = (read3BitValue(tile,i)<<1);
    pallet_offsets[i] = pallet_address+initial_offset+pixel_offset;
  }

  return 0;
}
