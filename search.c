#include "IS.h"

// Searches for a word in the database and displays its file occurrences
int search_database(hash_t *arr, char *word)
{
    int i = find_index(word);
    if (i < 0 || i >= 28)
        return DATA_NOT_FOUND;

    if (arr[i].m_link == NULL)
        return DATA_NOT_FOUND;

    m_node *temp_m = arr[i].m_link;
    while (temp_m != NULL)
    {
        if (strcmp(temp_m->word, word) == 0)
        {
            printf("Word: %s, Filecount: %d\n", temp_m->word, temp_m->f_count);

            s_node *temp_s = temp_m->s_link;
            while (temp_s != NULL)
            {
                printf("file: %s, Wordcount: %d\n", temp_s->filename, temp_s->w_count);
                temp_s = temp_s->s_link;
            }
            printf("\n");
            return SUCCESS;
        }
        temp_m = temp_m->m_link;
    }
    return DATA_NOT_FOUND;
}
