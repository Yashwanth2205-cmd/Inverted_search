/*
Name: Yashwanth G

Date: 09/09/2026

Project Name: Inverted Search in C

Description:

This project is a command-line Inverted Search application developed in
the C programming language. It creates an inverted index of words found in
multiple text files by storing each word in a hash table with file references.

The application supports the following functionalities:
- Validation of input files
- Creation of inverted index database using hash table with linked lists
- Searching for words and displaying their file occurrences
- Displaying the complete inverted index database
- Saving the database to a backup file
- Updating the database from a backup file
- Handling of duplicate files and words
- Counting word frequencies across files

Usage:
./a.out <file1.txt> <file2.txt> ... <fileN.txt>
*/

#include "IS.h"

// Main menu-driven program for managing inverted search database operations
int main(int argc, char *argv[])
{
    Slist *file=NULL;
    m_node *main=NULL;
    s_node *sub=NULL;
    hash_t arr[28];
    create_hash(arr, 28);

    if(validate(argc, argv, &file))
    {
        printf("Validation successful\n");

        int op;
        while(1)
        {
            printf("\n              DATABASE MENU\n1.Creat\n2.Search\n3.Display\n4.Save\n5.Update \n6.Exit\n");
            printf("Enter your choice: ");
            scanf("%d",&op);
            switch(op)
            {
                case 1:
                {
                    if(creat_database(arr,main,sub,file))
                        printf("\nDatabase created successfully\n\n");
                    else
                        printf("Database creation failed\n");
                    break;
                }

                case 2:
                {
                    char word[30];
                    printf("Enter the word: ");
                    scanf("%s",word);
                    if(search_database(arr, word) == DATA_NOT_FOUND)
                        printf("\"%s\" WORD NOT FOUND",word);
                    
                    break;
                }

                case 3:
                {
                    if(display_database(arr, 28))
                        printf("Database displayed successfully\n");
                    else
                        printf("Database display failed\n");
                    break;
                }

                case 4:
                {
                    if(save_database(arr, 28))
                        printf("Database saved successfully\n");
                    else
                        printf("Database saving failed\n");
                    break;
                }

                case 5:
                {
                    
                    if(update_database(arr,&file))
                        printf("\nDatabase updated successfully\n\n");
                    else
                        printf("Database update failed\n");
                    break;
                }

                case 6:
                    printf("Exited......!\n");
                    free_database(arr, 28);
                    free_file_list(&file);
                    return FAILURE;

                default:
                    printf("Invalid Input, Re-enter a valid input");
            }
        }
    }
    else
    {
        printf("Validation failed\n");
        free_database(arr, 28);
        free_file_list(&file);
        return FAILURE;
    }
}