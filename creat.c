#include "IS.h"

static int file_is_indexed(hash_t *arr, int size, char *filename)
{
    for(int i=0;i<size;i++)
    {
        m_node *main_temp=arr[i].m_link;
        while(main_temp != NULL)
        {
            s_node *sub_temp=main_temp->s_link;
            while(sub_temp != NULL)
            {
                if(strcmp(sub_temp->filename, filename)==0)
                    return SUCCESS;
                sub_temp=sub_temp->s_link;
            }
            main_temp=main_temp->m_link;
        }
    }
    return FAILURE;
}

// Creates an inverted index database by processing all input files and hashing words
int creat_database(hash_t *arr,m_node *main,s_node *sub, Slist *file)
{
    (void)main;
    (void)sub;
    Slist *temp=file;
    while(temp != NULL)
    {
        if(file_is_indexed(arr, 28, temp->file))
        {
            temp=temp->link;
            continue;
        }
        FILE *fp=fopen(temp->file,"r");
        if(fp == NULL)
            return FAILURE;
        char word[30];
        while(fscanf(fp,"%s",word) != EOF)
        {
            int index=find_index(word);
            m_node *m_temp=arr[index].m_link;
            while(m_temp != NULL)
            {
                if(strcmp(m_temp->word, word)==0)
                {
                    s_node *s_temp=m_temp->s_link;
                    while(s_temp != NULL)
                    {
                        if(strcmp(s_temp->filename, temp->file)==0)
                        {
                            s_temp->w_count++;
                            break;
                        }
                        s_temp=s_temp->s_link;
                    }
                    if(s_temp==NULL)
                    {
                        s_node *new_s=(s_node*)malloc(sizeof(s_node));
                        strcpy(new_s->filename, temp->file);
                        new_s->w_count=1;
                        new_s->s_link=m_temp->s_link;
                        m_temp->s_link=new_s;
                        m_temp->f_count++;
                    }
                    break;
                }
                m_temp=m_temp->m_link;
            }
            if(m_temp==NULL)
            {
                m_node *new_m=(m_node*)malloc(sizeof(m_node));
                strcpy(new_m->word, word);
                new_m->f_count=1;
                new_m->m_link=arr[index].m_link;
                arr[index].m_link=new_m;

                s_node *new_s=(s_node*)malloc(sizeof(s_node));
                strcpy(new_s->filename, temp->file);
                new_s->w_count=1;
                new_s->s_link=NULL;
                new_m->s_link=new_s;
            }
        }
        fclose(fp);
        temp=temp->link;
    }
    return SUCCESS;
}