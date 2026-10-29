#ifndef IS_H
#define IS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SUCCESS		1
#define FAILURE		0
#define DATA_NOT_FOUND -1

typedef struct node
{
    char file[30];
    struct node *link;
}Slist;

typedef struct main_node
{
    char word[30];
    int f_count;
    struct main_node *m_link;
    struct sub_node *s_link;
}m_node;

typedef struct sub_node
{
    char filename[30];
    int w_count;
    struct sub_node *s_link;
}s_node;

typedef struct hash
{
    int index;
    struct main_node *m_link;
}hash_t;

int validate(int argc,char *argv[], Slist **file);
int duplicate(char *filename, Slist *file);
int find_index(char *word);
void create_hash(hash_t *arr, int size);
int insert_at_first(Slist **head,char *filename);
void free_database(hash_t *arr, int size);
void free_file_list(Slist **head);
int creat_database(hash_t *arr,m_node *main,s_node *sub, Slist *file);
int display_database(hash_t *arr, int size);
int search_database(hash_t *arr,char *word);
int save_database(hash_t *arr, int size);
int update_database(hash_t *arr,Slist **filename);

#endif