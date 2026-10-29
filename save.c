#include "IS.h"

// Saves the inverted index database to a backup .txt file
int save_database(hash_t *arr, int size)
{
    char filename[30];
    printf("Enter the filename to save the database: ");
    scanf("%s", filename);

    char *ptr=strrchr(filename, '.');
    if(ptr != NULL && strcmp(ptr, ".txt") == 0)
    {
        FILE *fp = fopen(filename, "w");
        if (fp == NULL)
        {
            printf("Error opening file for writing.\n");
            return FAILURE;
        }

        for (int i = 0; i < size; i++)
        {
            m_node *temp_m = arr[i].m_link;
            while (temp_m != NULL)
            {
                fprintf(fp, "# Index: %d Word: %s; Filecount: %d; ", i,temp_m->word, temp_m->f_count);

                s_node *temp_s = temp_m->s_link;
                while (temp_s != NULL)
                {
                    fprintf(fp, "file: %s; Wordcount: %d ", temp_s->filename, temp_s->w_count);
                    temp_s = temp_s->s_link;
                }
                fprintf(fp, "#\n");
                temp_m = temp_m->m_link;
            }
        }
        fclose(fp);
        return SUCCESS;
    }
    else
    {
        printf("Invalid file extension. Please use .txt\n");
        return FAILURE;
    }
}