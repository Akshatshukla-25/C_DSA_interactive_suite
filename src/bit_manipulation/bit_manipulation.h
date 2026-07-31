#ifndef BIT_MANIPULATION_H
#define BIT_MANIPULATION_H

/**
 * @brief Sets the k-th bit of integer n to 1.
 * @param n Target 32-bit integer.
 * @param k 0-based bit position (0 to 31).
 * @return Value with k-th bit set.
 */
int set_bit(int n, int k);

/**
 * @brief Clears the k-th bit of integer n to 0.
 * @param n Target 32-bit integer.
 * @param k 0-based bit position (0 to 31).
 * @return Value with k-th bit cleared.
 */
int clear_bit(int n, int k);

/**
 * @brief Toggles (flips) the k-th bit of integer n.
 * @param n Target 32-bit integer.
 * @param k 0-based bit position (0 to 31).
 * @return Value with k-th bit toggled.
 */
int toggle_bit(int n, int k);

/**
 * @brief Checks if the k-th bit of integer n is set.
 * @param n Target 32-bit integer.
 * @param k 0-based bit position (0 to 31).
 * @return 1 if k-th bit is set, 0 otherwise.
 */
int check_bit(int n, int k);

/**
 * @brief Counts the total number of set bits (1s) using Brian Kernighan's algorithm.
 * @param n Target integer.
 * @return Total set bit count.
 */
int count_set_bits(int n);

/**
 * @brief Determines if integer n is a positive power of two.
 * @param n Target integer.
 * @return 1 if power of two, 0 otherwise.
 */
int is_power_of_two(int n);

/**
 * @brief Swaps values of two integers in-place using bitwise XOR without temporary variable.
 * @param a Pointer to first integer.
 * @param b Pointer to second integer.
 */
void xor_swap(int* a, int* b);

/**
 * @brief Isolates the rightmost set bit (lowest 1 bit) of n.
 * @param n Target integer.
 * @return Power of two representing the lowest set bit.
 */
int get_rightmost_set_bit(int n);

/**
 * @brief Turns off the rightmost set bit of n.
 * @param n Target integer.
 * @return Value with lowest set bit cleared.
 */
int turn_off_rightmost_set_bit(int n);

/**
 * @brief Reverses the 32 bits of an unsigned integer.
 * @param n Unsigned 32-bit integer.
 * @return Bit-reversed value.
 */
unsigned int reverse_bits(unsigned int n);

/**
 * @brief Finds the single non-repeating element in an array where all other elements appear twice.
 * @param arr Array of integers.
 * @param n Array length.
 * @return The unique element value.
 */
int find_unique(int arr[], int n);

/**
 * @brief Generates and prints all 2^N subsets of an array using bit masking.
 * @param arr Array of integers.
 * @param n Array length.
 */
void generate_subsets(int arr[], int n);

/** @brief Interactive CLI demo menu for Bit Manipulation. */
void bit_manipulation_demo(void);
/** @brief Interactive sub-demo for basic bitwise operations (set, clear, toggle, check). */
void basic_bit_ops_demo(void);
/** @brief Interactive sub-demo for set bit counting. */
void count_set_bits_demo(void);
/** @brief Interactive sub-demo for power-of-two validation. */
void power_of_two_demo(void);
/** @brief Interactive sub-demo for in-place XOR swap. */
void xor_swap_demo(void);
/** @brief Interactive sub-demo for rightmost set bit operations. */
void rightmost_set_bit_demo(void);
/** @brief Interactive sub-demo for bit reversal. */
void reverse_bits_demo(void);
/** @brief Interactive sub-demo for unique element finding. */
void find_unique_demo(void);
/** @brief Interactive sub-demo for power-set subset generation. */
void generate_subsets_demo(void);
/** @brief Interactive 32-bit terminal grid visualizer demo. */
void bitwise_visualizer_demo(void);

/**
 * @brief Prints binary 32-bit representation of an unsigned integer to stdout.
 * @param n Unsigned 32-bit integer.
 */
void print_binary_32(unsigned int n);

/**
 * @brief Prints 32-bit binary string with specified mask bits highlighted in terminal color.
 * @param n Unsigned 32-bit integer.
 * @param highlight_mask Bitmask indicating which bits to highlight.
 * @param color_code ANSI escape color code string.
 */
void print_binary_32_highlight(unsigned int n, unsigned int highlight_mask, const char* color_code);

#endif /* BIT_MANIPULATION_H */
