#include "inverted.h"

/*
 * ==========================================================================
 * FUNCTION: search_database
 * --------------------------------------------------------------------------
 * Purpose:
 *      To search for a given word in the inverted index.
 *      If found, it prints:
 *          - how many files it appears in
 *          - each file name
 *          - how many times in that file
 *
 * Steps:
 *      1. Convert search word to lowercase.
 *      2. Find its correct bucket using hash index.
 *      3. Look through that bucket’s words.
 *      4. If match → print details.
 *
 * Returns:
 *      SUCCESS → if found
 *      FAILURE → if not found or invalid word
 * ==========================================================================
 */
int search_database(hash_table htable[], char *word)
{
    char lower[MAXW];
    normalize_keep_punct(lower, word);   // clean the search word

    if (lower[0] == '\0')
    {
        printf("ERROR: Invalid search word.\n");
        return FAILURE;
    }

    int idx = get_hash_index(lower);
    main_node *m = htable[idx].link;

    /* Search through bucket */
    while (m)
    {
        if (strcmp(m->word_lower, lower) == 0)
        {
            printf("FOUND: '%s' is present in %d file(s):\n",
                   m->word_original, m->file_count);

            /* Print file and count */
            sub_node *s = m->s_link;
            while (s)
            {
                printf("  → %s : %d times\n",
                       s->file_name, s->word_count);
                s = s->sub_link;
            }

            return SUCCESS;
        }
        m = m->m_link;
    }

    printf("NOT FOUND: '%s' not in database.\n", word);
    return FAILURE;
}
