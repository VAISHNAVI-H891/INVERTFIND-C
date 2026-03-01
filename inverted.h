#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1
#define MAXW 100
#define MAXF 100
#define LINEBUF 512

/* file-list linked list */
typedef struct node
{
    char fname[MAXF];
    struct node *link;
} Fnode;

/* forward declarations */
typedef struct main_node main_node;
typedef struct sub_node sub_node;

/* 26-bucket hash table */
typedef struct hash_table
{
    int key;
    main_node *link;
} hash_table;

/* main node: one per unique WORD */
struct main_node
{
    char word_original[MAXW];     /* preserve original case and punctuation */
    char word_lower[MAXW];        /* lowercase for comparison/hash */
    int file_count;

    main_node *m_link;
    sub_node *s_link;
};

/* sub node: file entry for each word */
struct sub_node
{
    char file_name[MAXF];
    int word_count;
    sub_node *sub_link;
};

/*********** FUNCTION PROTOTYPES ******************/

/* validation & file-list */
int validate_and_store_files(Fnode **head, char *argv[], int argc);
void print_file_list(Fnode *head);

/* utils */
void normalize_keep_punct(char *dst, const char *src);
int get_hash_index(const char *word);
int is_valid_file(const char *fname);

/* create */
int create_database(hash_table htable[], Fnode *files);
void insert_word(hash_table htable[], const char *raw, const char *filename);

/* display and search */
int display_database(hash_table htable[]);
int search_database(hash_table htable[], char *word);

/* update/restore */
int restore_database_from_backup(hash_table htable[], const char *backup_fname);

/* parse saved DB (kept for compatibility if needed) */
int parse_saved_db_filenames(const char *savedfile, Fnode **out_list);

/* save */
int save_database(hash_table htable[], char *outfile);

#endif
