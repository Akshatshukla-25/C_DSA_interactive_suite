#ifndef BIT_MANIPULATION_H
#define BIT_MANIPULATION_H

int set_bit(int n, int k);
int clear_bit(int n, int k);
int toggle_bit(int n, int k);
int check_bit(int n, int k);

int count_set_bits(int n);
int is_power_of_two(int n);
void xor_swap(int* a, int* b);

int get_rightmost_set_bit(int n);
int turn_off_rightmost_set_bit(int n);
unsigned int reverse_bits(unsigned int n);

int find_unique(int arr[], int n);

void generate_subsets(int arr[], int n);

void bit_manipulation_demo(void);
void basic_bit_ops_demo(void);
void count_set_bits_demo(void);
void power_of_two_demo(void);
void xor_swap_demo(void);
void rightmost_set_bit_demo(void);
void reverse_bits_demo(void);
void find_unique_demo(void);
void generate_subsets_demo(void);
void bitwise_visualizer_demo(void);

#endif /* BIT_MANIPULATION_H */
