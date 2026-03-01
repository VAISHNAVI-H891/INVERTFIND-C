#include "inverted.h"

/* Remove extra spaces from start/end */
static void trim(char *s)
{
    while (*s && isspace(*s)) s++;
    char *end = s + strlen(s) - 1;
    while (end >= s && isspace(*end)) *end-- = '\0';
}

/* Free all nodes in hash table */
static void clear_hashtable(hash_table htable[])
{
    for (int i = 0; i < 26; i++)
    {
        main_node *m = htable[i].link;
        while (m)
        {
            sub_node *s = m->s_link;
            while (s)
            {
                sub_node *t = s->sub_link;
                free(s);
                s = t;
            }
            main_node *mt = m->m_link;
            free(m);
            m = mt;
        }
        htable[i].link = NULL;
    }
}

/*
 * ==========================================================================
 * FUNCTION: restore_database_from_backup
 * --------------------------------------------------------------------------
 * Purpose:
 *      Reads a saved file (made by SAVE) and rebuilds the inverted index.
 *
 * What it does:
 *      - Clears old database
 *      - Reads bucket index (#x;)
 *      - Reads each word and its file list
 *      - Recreates all main nodes and sub nodes
 *
 * Returns:
 *      SUCCESS if loaded properly
 *      FAILURE if file missing or corrupted
 * ==========================================================================
 */
int restore_database_from_backup(hash_table htable[], const char *backup)
{
    FILE *fp = fopen(backup, "r");
    if (!fp)
    {
        printf("ERROR: Backup file not found: %s\n", backup);
        return FAILURE;
    }

    clear_hashtable(htable);  // clean previous data

    char line[LINEBUF];
    int current_bucket = -1;

    while (fgets(line, LINEBUF, fp))
    {
        trim(line);

        /* Bucket header like "#7;" */
        if (line[0] == '#')
        {
            sscanf(line, "#%d;", &current_bucket);
            continue;
        }

        if (current_bucket < 0) continue;

        /* Tokenize record line */
        char temp[LINEBUF];
        strcpy(temp, line);

        char *tok = strtok(temp, ";");
        if (!tok) continue;

        char word[MAXW];
        strcpy(word, tok);
        trim(word);

        /* File count */
        tok = strtok(NULL, ";");
        if (!tok) continue;
        int fcount = atoi(tok);

        /* Create main node */
        main_node *m = malloc(sizeof(main_node));
        strcpy(m->word_original, word);
        normalize_keep_punct(m->word_lower, word);
        m->file_count = fcount;
        m->s_link = NULL;

        /* Insert main node at bucket head */
        m->m_link = htable[current_bucket].link;
        htable[current_bucket].link = m;

        /* Read file entries */
        while ((tok = strtok(NULL, ";")) != NULL)
        {
            char file[MAXF];
            strcpy(file, tok);
            trim(file);

            if (file[0] == '#') break;

            char *cnt = strtok(NULL, ";");
            int wcount = atoi(cnt);

            sub_node *s = malloc(sizeof(sub_node));
            strcpy(s->file_name, file);
            s->word_count = wcount;

            s->sub_link = m->s_link;
            m->s_link = s;
        }
    }

    fclose(fp);
    printf("SUCCESS: Restored from '%s'\n", backup);
    return SUCCESS;
}
