#include "inverted.h"

/*
 * ==========================================================================
 * FUNCTION: display_database
 * --------------------------------------------------------------------------
 * Purpose:
 *      This function prints the entire inverted index in a clean table form.
 *      For each word, it shows:
 *          - its hash index
 *          - the word itself
 *          - how many files contain the word
 *          - each filename (printed vertically)
 *          - how many times the word appears in each file
 *
 * Why it's needed:
 *      Helps the user see the full database clearly after CREATE or UPDATE.
 *
 * Returns:
 *      SUCCESS always
 * ==========================================================================
 */
int display_database(hash_table htable[])
{
    int shown = 0;

    /* Print table header */
    printf("\n%-6s | %-12s | %-8s | %-12s | %-7s\n",
           "Index", "Word", "F-count", "F-name", "W-count");
    printf("-----------------------------------------------------------------\n");

    /* Go through all buckets (a–z → 0–25) */
    for (int i = 0; i < 26; i++)
    {
        main_node *m = htable[i].link;

        /* Loop through all words in this bucket */
        while (m)
        {
            sub_node *s = m->s_link;
            int first_row = 1;

            /* Each file entry printed on a separate line */
            while (s)
            {
                if (first_row)
                {
                    /* First row prints everything */
                    printf("%-6d | %-12s | %-8d | %-12s | %-7d\n",
                           i,
                           m->word_original,
                           m->file_count,
                           s->file_name,
                           s->word_count
                    );
                    first_row = 0;
                }
                else
                {
                    /* Next rows print only file name + count */
                    printf("%-6s | %-12s | %-8s | %-12s | %-7d\n",
                           "",
                           "",
                           "",
                           s->file_name,
                           s->word_count
                    );
                }

                s = s->sub_link;
            }

            printf("-----------------------------------------------------------------\n");
            shown = 1;
            m = m->m_link;
        }
    }

    if (!shown)
        printf("INFO: Database Empty.\n");

    return SUCCESS;
}
