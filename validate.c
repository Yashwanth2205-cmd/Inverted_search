#include "IS.h"

// Validates input files and builds a linked list of valid .txt files
int validate(int argc,char *argv[], Slist **file)
{
    int valid_file_count=0;

    if(argc <= 1)
    {
        printf("Invalid number of arguments\n");
        printf("Usage: ./a.out <file1.txt> <file2.txt> ... <fileN.txt>\n");
        return FAILURE;
    }

    for(int i=1; i<argc; i++)
    {
        char *ptr=strrchr(argv[i], '.');
        if(ptr != NULL && strcmp(ptr, ".txt") == 0)
        {
            if(!duplicate(argv[i], *file))
            {
                printf("%s File already exist, Ignoring the file\n", argv[i]);
                continue;
            }
            
            FILE *fp=fopen(argv[i], "r");
            if(fp == NULL)
            {
                printf("%s file doesn't exist ,unable to open file\n", argv[i]);
                continue;
            }

            int ch=fgetc(fp);
            fclose(fp);
            if(ch == EOF)
            {
                printf("%s File is empty, Ignoring the file\n",argv[i]);
                continue;
            }

            if(!insert_at_first(file, argv[i]))
                continue;

            valid_file_count++;
        }
    }

    return valid_file_count > 0 ? SUCCESS : FAILURE;
}