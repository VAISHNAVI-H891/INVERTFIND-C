#include "inverted.h"

/*
 * FUNCTION: insert_word
 * ----------------------
 * Purpose:
 *      Inserts one cleaned word into the hash table.
 *      If the word already exists → increase count.
 *      If the file already exists for this word → increase file count.
 *      If new word or new file → create new node.
 *
 * Why needed:
 *      This builds the inverted index entry for each word.
 *
 * Inputs:
 *      htable[]  → main hash table
 *      raw       → the raw word read from file
 *      filename  → the file in which the word was found
 *
 * Returns:
 *      Nothing
 */
void insert_word(hash_table htable[], const char *raw, const char *filename)
{
    char lower[MAXW], original[MAXW];

    /* Store original word and clean lowercase word */
    strncpy(original, raw, MAXW - 1);
    original[MAXW - 1] = '\0';

    normalize_keep_punct(lower, raw);   // clean word

    /* If empty after cleaning → skip */
    if (lower[0] == '\0')
        return;

    /* Find correct bucket */
    int idx = get_hash_index(lower);

    main_node *m = htable[idx].link, *prev = NULL;

    /* Search for existing word */
    while (m)
    {
        if (strcmp(m->word_lower, lower) == 0)
            break;     // word already exists
        prev = m;
        m = m->m_link;
    }

    /* If word not found → create new main node */
    if (!m)
    {
        m = malloc(sizeof(main_node));
        if (!m) return;

        strncpy(m->word_original, original, MAXW - 1);
        m->word_original[MAXW - 1] = '\0';

        strncpy(m->word_lower, lower, MAXW - 1);
        m->word_lower[MAXW - 1] = '\0';

        m->file_count = 0;
        m->s_link = NULL;
        m->m_link = NULL;

        if (prev)
            prev->m_link = m;
        else
            htable[idx].link = m;       // first node in bucket
    }

    /* Now handle file list (sub nodes) */
    sub_node *s = m->s_link, *sprev = NULL;

    while (s)
    {
        /* If file already present → increase count */
        if (strcmp(s->file_name, filename) == 0)
        {
            s->word_count++;
            return;
        }
        sprev = s;
        s = s->sub_link;
    }

    /* If file not present → create new subnode */
    s = malloc(sizeof(sub_node));
    if (!s) return;

    strncpy(s->file_name, filename, MAXF - 1);
    s->file_name[MAXF - 1] = '\0';

    s->word_count = 1;
    s->sub_link = NULL;

    /* Insert subnode */
    if (sprev)
        sprev->sub_link = s;
    else
        m->s_link = s;

    m->file_count++;    // Increase number of files containing this word
}

/*
 * FUNCTION: create_database
 * --------------------------
 * Purpose:
 *      Reads every file character-by-character.
 *      Extracts clean words and inserts into hash table.
 *
 * Why needed:
 *      This is the main database creation step of the project.
 *
 * Steps:
 *      - Open each .txt file
 *      - Read characters one by one
 *      - Build word until a non-alphanumeric character is seen
 *      - Then insert the word into hash table
 *
 * Inputs:
 *      htable[]  → main inverted index
 *      files     → linked list of valid file names
 *
 * Returns:
 *      SUCCESS / FAILURE
 */
int create_database(hash_table htable[], Fnode *files)
{
    if (!files)
    {
        printf("ERROR: No files provided.\n");
        return FAILURE;
    }

    printf("INFO: Starting database creation...\n");

    /* Process each file from the linked list */
    for (Fnode *f = files; f; f = f->link)
    {
        printf("INFO: Reading %s\n", f->fname);

        FILE *fp = fopen(f->fname, "r");
        if (!fp)
        {
            printf("ERROR: Cannot open %s. Skipping.\n", f->fname);
            continue;
        }

        char wordbuf[256];
        int c, k = 0;

        /* Read character-by-character */
        while ((c = fgetc(fp)) != EOF)
        {
            if (isalnum(c))  // part of a word
            {
                if (k < 255)
                    wordbuf[k++] = c;
            }
            else             // break between words
            {
                if (k > 0)
                {
                    wordbuf[k] = '\0';
                    insert_word(htable, wordbuf, f->fname);
                    k = 0;
                }
            }
        }

        /* Insert last word, if any */
        if (k > 0)
        {
            wordbuf[k] = '\0';
            insert_word(htable, wordbuf, f->fname);
        }

        fclose(fp);
    }

    printf("SUCCESS: Database created successfully.\n");
    return SUCCESS;
}
