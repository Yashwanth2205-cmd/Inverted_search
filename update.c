#include "IS.h"

// Restores the inverted index database from a backup .txt file
int update_database(hash_t *arr,Slist **filename)
{
    char file[30];
    printf("Enter the backup filename: ");
    scanf("%s", file);

    char *ptr=strrchr(file, '.');
    if(ptr != NULL && strcmp(ptr, ".txt") == 0)
    {
        FILE *fp = fopen(file, "r");
        if (fp == NULL)
        {
            printf("Error opening file for reading.\n");
            return FAILURE;
        }
        free_database(arr, 28);
        create_hash(arr, 28);
        char ch=fgetc(fp);
        rewind(fp);
        if(ch == '#')
        {
            int index,f_count,w_count;
            char word[30];
            while(fscanf(fp, " # Index: %d Word: %29[^;]; Filecount: %d; ", &index,word,&f_count) == 3)
            {
                if(index < 0 || index >= 28 || f_count < 0)
                {
                    fclose(fp);
                    return FAILURE;
                }
                m_node *new_m=(m_node*)malloc(sizeof(m_node));
                if(new_m == NULL)
                {
                    fclose(fp);
                    return FAILURE;
                }
                strcpy(new_m->word, word);
                new_m->f_count=f_count;
                new_m->m_link=arr[index].m_link;
                new_m->s_link=NULL;
                arr[index].m_link=new_m;
                for(int i=0;i<f_count;i++)
                {
                    if(fscanf(fp, "file: %29[^;]; Wordcount: %d ", file,&w_count) != 2 || w_count < 0)
                    {
                        fclose(fp);
                        return FAILURE;
                    }
                    s_node *new_s=(s_node*)malloc(sizeof(s_node));
                    if(new_s == NULL)
                    {
                        fclose(fp);
                        return FAILURE;
                    }
                    strcpy(new_s->filename, file);
                    new_s->w_count=w_count;
                    new_s->s_link=new_m->s_link;
                    new_m->s_link=new_s;

                    if(duplicate(file, *filename))
                    {
                        if(!insert_at_first(filename, file))
                            continue;                        
                    }
                }
                char marker;
                if(fscanf(fp, " %c", &marker) != 1 || marker != '#')
                {
                    fclose(fp);
                    printf("Invalid file format.\n");
                    return FAILURE;
                }
            }            
        }
        else
        {
            fclose(fp);
            printf("Invalid file format.\n");
            return FAILURE;
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