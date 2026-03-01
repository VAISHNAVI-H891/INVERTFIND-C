#include "inverted.h"

/*
 * ==========================================================================
 * FUNCTION: save_database
 * --------------------------------------------------------------------------
 * Purpose:
 *      Saves the entire inverted index into a text file.
 *      This saved file can be used later for UPDATE/RESTORE.
 *
 * How it saves:
 *      #index;
 *      word; file_count; file1; count1; file2; count2; ...; #
 *
 * Returns:
 *      SUCCESS if saved
 *      FAILURE if file cannot open
 * ==========================================================================
 */
int save_database(hash_table htable[], char *outfile)
{
    FILE *fp = fopen(outfile, "w");
    if (!fp)
    {
        printf("ERROR: Unable to open %s\n", outfile);
        return FAILURE;
    }

    /* Loop through every bucket */
    for (int idx = 0; idx < 26; idx++)
    {
        main_node *m = htable[idx].link;
        if (!m) continue;

        fprintf(fp, "#%d;\n", idx);  // print bucket header

        /* Print all words under this bucket */
        while (m)
        {
            fprintf(fp, "%s; %d;",
                    m->word_original, m->file_count);

            /* Print file entries */
            sub_node *s = m->s_link;
            while (s)
            {
                fprintf(fp, " %s; %d;", s->file_name, s->word_count);
                s = s->sub_link;
            }

            fprintf(fp, " #\n"); // end of word

            m = m->m_link;
        }
    }

    fclose(fp);
    printf("SUCCESS: Saved database to '%s'\n", outfile);
    return SUCCESS;
}
