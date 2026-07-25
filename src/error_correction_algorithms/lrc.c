#include "error_correction_algorithms.h"
#include "safe_input.h"
#include <stdio.h>
#include <string.h>

/*
 * LRC (Longitudinal Redundancy Check)
 * ------------------------------------
 * Each bit of the LRC is the XOR (even parity) of the corresponding
 * bit column across all data words.  The result is appended to the
 * transmitted block so the receiver can verify integrity.
 */

#define LRC_MAX_ROWS 20
#define LRC_MAX_COLS 64

// lrc_calculate: computes the LRC by XOR-ing each column across all `words`.
// Writes a null-terminated binary string of length `word_len` to `lrc_out`.
void lrc_calculate(const char* const* words, int num_words, int word_len, char* lrc_out)
{
    for (int j = 0; j < word_len; j++)
    {
        int ones = 0;
        for (int i = 0; i < num_words; i++)
        {
            if (words[i][j] == '1')
            {
                ones++;
            }
        }
        lrc_out[j] = (ones % 2 == 0) ? '0' : '1';
    }
    lrc_out[word_len] = '\0';
}

// lrc_verify: returns 1 if the computed LRC matches `received_lrc`, 0 otherwise.
int lrc_verify(const char* const* words, int num_words, int word_len, const char* received_lrc)
{
    char computed_lrc[LRC_MAX_COLS + 1];
    lrc_calculate(words, num_words, word_len, computed_lrc);
    return (strcmp(computed_lrc, received_lrc) == 0) ? 1 : 0;
}
