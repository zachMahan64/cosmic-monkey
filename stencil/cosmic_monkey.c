#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * INSTRUCTIONS:
 * Note, you're going to need a C compiler to test your code. This is different
 * for each operating system, so feel free to ask a team member for help if
 * you're stuck.
 * ---------------------------------------------------------------------------
 * DISCLAIMER: This code is very UNIX/Linux specific. It abides by the
 * coding/safety standards expected on PVDXos, but it NOT a 1-to-1
 * correspondance with the code pushed to the satellite.
 */

// CHECK_FOR_ERRORS MACRO, currently assumes only bad code is -1 (works here)

#ifdef DEBUG
#define CHECK_FOR_ERRORS(exit_code, fn_name)                                   \
  if (exit_code == -1) {                                                       \
    exit_code |= printf(                                                       \
        "[ERROR] in \"%s\", cosmic monkey ran into an issue, code: %d\n",      \
        fn_name, exit_code);                                                   \
  }
#else
#define CHECK_FOR_ERRORS(exit_code, fn_name)
#endif

/**
 * int32_t cosmic_monkey(void* data, size_t size)
 *
 * \brief Randomly selects a bit within `data` to flip, and flips the bit.
 *
 * The function should:
 *    - Randomly select a byte and a bit within that byte to flip (using rand()
 * seeded by srand()).
 *    - Print which byte and bit are being flipped (for debugging purposes).
 *    - Flip the selected bit using XOR.
 *
 * Prarametres:
 * \param data : The pointer to the data block to be mutated.
 * \param size : The size of the data block in bytes.
 *
 * Returns:
 * \return int32_t : 0 upon success
 */

int32_t cosmic_monkey(void *data, size_t size) {
  // TODO :
  //  Implement the cosmic_monkey function, which should flip random bits in
  //  the input data block. Feel free to use the internet(and ChatGPT) to
  //  learn about the necessary operations.

  if (size == 0) {
    return -1;
  }

  size_t byte_to_select = rand() % size;
  size_t bit_to_flip = rand() % 8;
  uint8_t mask = 0x01 << bit_to_flip;
  ((uint8_t *)data)[byte_to_select] = ((uint8_t *)data)[byte_to_select] ^ mask;
  return 0;
}

/**
 * int32_t print_bytes(void *data, size_t size);
 *
 * \brief Given a pointer to arbitrary data and a size, prints the data as a hex
 * array
 *
 * Parametres:
 * \param data : The pointer to the data block to be printed.
 * \param size : The size of the data block in bytes.
 *
 * Returns:
 * \return int32_t : a status code, int32_t to comply with status codes returned
 *                   by printf
 */

int32_t print_bytes(void *data, size_t size) {
  // TODO:
  //  Implement the print_bytes function to visualize the data in
  //  hexadecimal format before and after the mutation.
  // HINT: run `man 3 printf` in the terminal
  if (size == 0) {
    return -1;
  }
  int exit_code = 0;
  for (size_t i = 0; i < size; i++) {
    exit_code |= printf("%x ", ((uint8_t *)data)[i]);
  }
  exit_code |= printf("\n");
  CHECK_FOR_ERRORS(exit_code, "print_bytes");
  return exit_code;
}

/**
 * int main(void)
 *
 * \brief Program entry point; runs cosmic monkey program
 *
 * Parametres:
 * N/A
 *
 * Return:
 * \return int : 0 upon success, +ve status code otherwise.
 *
 * NOTE: the use of int here as a return type is only to comply with the current
 * Linux standard. Use of ambiguous/unsized `int` types is *strongly*
 * discouraged in PVDXos
 */
int main(void) {
  int32_t exit_code = 0;
  // Example data for testing the Cosmic Monkey
  unsigned char data[4] = {0xFF, 0x00, 0xAA, 0x55};

  // Print original data
  exit_code |= printf("Original data:\n");
  print_bytes(data, sizeof(data));

  // Seed random number generator
  srand((uint32_t)time(NULL));

  // Run the Cosmic Monkey to flip random bits
  exit_code |= cosmic_monkey(data, sizeof(data));

  // Print mutated data
  exit_code |= printf("Mutated data:\n");
  exit_code |= print_bytes(data, sizeof(data));

  CHECK_FOR_ERRORS(exit_code, "main");

  return exit_code;
}
