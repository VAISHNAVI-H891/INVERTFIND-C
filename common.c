#include "inverted.h"

/*
 * FUNCTION: get_hash_index
 * -------------------------
 * Purpose:
 *      Finds which bucket (0–25) a word belongs to.
 *      We use the first letter of the word.
 *          a → 0
 *          b → 1
 *          ...
 *          z → 25
 *
 * Why needed:
 *      Helps place each word in the correct hash table slot.
 *
 * Returns:
 *      bucket index (0–25)
 *      returns 0 if word starts with any non-alphabet
 */
int get_hash_index(const char *word)
{
    if (!word || !word[0])
        return 0;   // empty word → send to bucket 0

    char c = (char)tolower((unsigned char)word[0]);

    if (c >= 'a' && c <= 'z')
        return c - 'a';     // convert letter → index

    return 0;               // non-alphabet words go to bucket 0
}

/*
 * FUNCTION: normalize_keep_punct
 * -------------------------------
 * Purpose:
 *      Takes a raw word from the file and cleans it by:
 *          • keeping only alphabet characters
 *          • converting to lowercase
 *          • stopping at punctuation (like . , ! ? -)
 *
 * Why needed:
 *      Ensures "Hello", "hello." and "HELLO," are all treated as "hello".
 *
 * Returns:
 *      Fills 'dst' with the cleaned word
 */
void normalize_keep_punct(char *dst, const char *src)
{
    int j = 0;

    for (int i = 0; src[i] && j < MAXW - 1; i++)
    {
        unsigned char ch = (unsigned char)src[i];

        if (isalpha(ch))
        {
            /* Convert letter to lowercase */
            dst[j++] = (char)tolower(ch);
        }
        else
        {
            /* Stop if punctuation is encountered */
            if (ch == ',' || ch == '.' || ch == '!' || ch == '?' ||
                ch == ';' || ch == ':' || ch == '-')
                break;   // punctuation ends the word

            /* ignore spaces, tabs, etc */
        }
    }

    dst[j] = '\0';  // end the cleaned word
}

/*
 * FUNCTION: is_valid_file
 * ------------------------
 * Purpose:
 *      Checks if a file:
 *          • exists
 *          • is not empty
 *
 * Why needed:
 *      Project should only process valid .txt files with content.
 *
 * Returns:
 *      SUCCESS → file exists and has content
 *      FAILURE → file missing or empty
 */
int is_valid_file(const char *fname)
{
    FILE *fp = fopen(fname, "r");
    if (!fp)
        return FAILURE;     // file not found

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);  // file size in bytes
    fclose(fp);

    return (size > 0) ? SUCCESS : FAILURE;
}
