#include "IS.h"

// Checks if a filename already exists in the file list to prevent duplicates
int duplicate(char *filename, Slist *file)
{
    while(file != NULL)
    {
        if(strcmp(file->file, filename)==0)
            return FAILURE;

        file=file->link;
    }
    return SUCCESS;
}

// Calculates hash index for a word based on its first character (A-Z, a-z, 0-9, or special)
int find_index(char *word)
{
    int index=0;
    if(isupper(word[0]))
        index=word[0]-'A';
    else if(islower(word[0]))
        index=word[0]-'a';
    else if(isdigit(word[0]))
        index=26;
    else
        index=27;

    return index;
}

// Initializes the hash table array with empty buckets
void create_hash(hash_t *arr, int size)
{
    for(int i=0;i<size;i++)
    {
        arr[i].index=i;
        arr[i].m_link=NULL;
    }
    printf("Hash table created successfully\n");
}

// Inserts a new filename at the beginning of the file linked list
int insert_at_first(Slist **head,char *filename)
{
    Slist *new = (Slist*)malloc(sizeof(Slist));
    
    if(new==NULL)
        return FAILURE;
    
    strcpy(new->file, filename);
    new->link=NULL;
    
    if(*head==NULL)
    {
        *head=new;
        return SUCCESS;
    }
    
    new->link=*head;
    *head=new;
    return SUCCESS;
}

void free_database(hash_t *arr, int size)
{
    for(int i=0;i<size;i++)
    {
        m_node *main_temp=arr[i].m_link;
        while(main_temp != NULL)
        {
            m_node *next_main=main_temp->m_link;
            s_node *sub_temp=main_temp->s_link;
            while(sub_temp != NULL)
            {
                s_node *next_sub=sub_temp->s_link;
                free(sub_temp);
                sub_temp=next_sub;
            }
            free(main_temp);
            main_temp=next_main;
        }
        arr[i].m_link=NULL;
    }
}

void free_file_list(Slist **head)
{
    Slist *temp=*head;
    while(temp != NULL)
    {
        Slist *next=temp->link;
        free(temp);
        temp=next;
    }
    *head=NULL;
}