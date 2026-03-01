#include "inverted.h"

/*
 * FUNCTION: has_txt_ext
 * ----------------------
 * Purpose:
 *      Checks if the given filename ends with ".txt"
 *      (not case-sensitive).
 *
 * Why needed:
 *      Only .txt files are allowed for the project.
 *
 * Returns:
 *      1 → valid
 *      0 → invalid
 */
static int has_txt_ext(const char *f)
{
    size_t len = strlen(f);
    if (len < 4) 
        return 0;   // too short to be ".txt"

    return strcasecmp(f + len - 4, ".txt") == 0;
}

/*
 * FUNCTION: validate_and_store_files
 * -----------------------------------
 * Purpose:
 *      - Checks all filenames given in command line.
 *      - Ensures each file:
 *          ✔ has .txt extension
 *          ✔ exists and is not empty
 *          ✔ is not repeated
 *      - All valid files are stored in a linked list (Fnode).
 *
 * Why needed:
 *      Creation of database needs a list of valid files.
 *
 * Returns:
 *      SUCCESS → at least one valid file
 *      FAILURE → no valid files
 */
int validate_and_store_files(Fnode **head, char *argv[], int argc)
{
    Fnode *tail = NULL;

    /* Start checking files from argv[1] onward */
    for (int i = 1; i < argc; ++i)
    {
        const char *candidate = argv[i];

        /* Check extension */
        if (!has_txt_ext(candidate))
        {
            printf("ERROR: Only .txt files allowed → %s\n", candidate);
            continue;
        }

        /* Check if file exists + non-empty */
        if (is_valid_file(candidate) == FAILURE)
        {
            printf("ERROR: File missing or empty → %s\n", candidate);
            continue;
        }

        /* Check for duplicates */
        int dup = 0;
        for (Fnode *t = *head; t; t = t->link)
        {
            if (strcmp(t->fname, candidate) == 0)
            {
                dup = 1;
                break;
            }
        }

        if (dup)
        {
            printf("ERROR: Duplicate file ignored → %s\n", candidate);
            continue;
        }

        /* Create new node for valid file */
        Fnode *n = malloc(sizeof(Fnode));
        if (!n)
        {
            printf("ERROR: Memory allocation failed.\n");
            return FAILURE;
        }

        strncpy(n->fname, candidate, MAXF - 1);
        n->fname[MAXF - 1] = '\0';
        n->link = NULL;

        /* Add to linked list */
        if (*head == NULL)
            *head = tail = n;
        else
        {
            tail->link = n;
            tail = n;
        }

        printf("INFO: File accepted → %s\n", candidate);
    }

    /* If no valid files, stop program */
    if (*head == NULL)
    {
        printf("ERROR: No valid input files.\n");
        return FAILURE;
    }

    printf("\nSUCCESS: File validation completed.\n");
    printf("File List: ");
    print_file_list(*head);

    return SUCCESS;
}

/*
 * FUNCTION: print_file_list
 * --------------------------
 * Purpose:
 *      Prints the list of all validated files like:
 *      file1.txt -> file2.txt -> NULL
 *
 * Why needed:
 *      Helps user confirm which files are being used.
 *
 * Returns:
 *      nothing
 */
void print_file_list(Fnode *head)
{
    while (head)
    {
        printf("%s", head->fname);
        if (head->link)
            printf(" -> ");
        else
            printf(" -> NULL");

        head = head->link;
    }
    printf("\n");
}
