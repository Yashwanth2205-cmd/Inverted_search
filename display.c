#include "IS.h"

// Displays the complete inverted index database with all words and their file counts
int display_database(hash_t *arr, int size)
{
    printf("-------------------------------------------------------------------\n");
    printf(" Index\tWord\t\tFilecount\tfilename\tWordcount\n");
    printf("-------------------------------------------------------------------\n");

    for(int i=0;i<size;i++)
    {
        if(arr[i].m_link == NULL)
            continue;
        
        printf(" %d", arr[i].index);
        m_node *temp=arr[i].m_link;
        while(temp != NULL)
        {
            printf("\t%s\t\t%d", temp->word, temp->f_count);
            s_node *sub_temp=temp->s_link;
            while(sub_temp != NULL)
            {
                printf("\t\t%s\t%d", sub_temp->filename, sub_temp->w_count);
                sub_temp=sub_temp->s_link;
            }
            printf("\n");
            temp=temp->m_link;
        }
    }
    printf("-------------------------------------------------------------------\n");
    return SUCCESS;
}