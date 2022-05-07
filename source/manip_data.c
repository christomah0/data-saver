#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>

#include "../include/manip_data.h" // header contains the declaration of the functions useful for running the program

#define SIZE (127)

// data structure assembles the variable for manipulating data
typedef struct data {
    char fullname[SIZE];
    char date_of_birth[SIZE];
    char sex[11];
    int id;
} data;

data R, W;

FILE *fp = NULL;
char c;

void bf_color(char color[]); // prototype of function

// function which displays a loading graphical
void loading()
{
    system("cls");
    printf("\nLOADING ");

    for (int i = 0; i < 25; i++) {
        printf(" %c", 219);
        _sleep(1);
    }
}

// function which changes the color of the console with specific case
void bf_color(char color[])
{
    char buffer[9] = "COLOR ";
    strcat(buffer, color);
    system(buffer);
}

// just a component with the menu for displaying string on the screen
void _out_(char *buffer)
{
    system("cls");
    for (int i = 0; i < 50; i++) printf("*");
    printf("\n*\t%s\n", buffer);
    for (int i = 0; i < 50; i++) printf("*");
    printf("\n\n");
}

//function which terminates string with '\0'
void c_null(char *buffer)
{
    for (int i = 0; buffer[i] != '\0'; i++)
        if (buffer[i] == '\n')
            buffer[i] = '\0';
}

// display the menu necessary
char output_menu(int x)
{
    char _x;

    while (true) {
        if (x == 0) {
            bf_color("0A");
            _out_("WELCOME TO THE DATA SAVER");
            printf("[1] Save data\n[2] Search data\n[3] Reset data\n[4] Exit\n\n");
            printf("[?] Enter a choice : ");
            fflush(stdout);
            fflush(stdin);
            scanf("%c", &_x);

            if (_x == '1' || _x == '2' || _x == '3' || _x == '4') {
                return _x;
            }
            else {
                bf_color("04");
                fprintf(stderr, "\nError : Invalid value\n\n");
                system("pause");
                continue;
            }
        }
        else if (x == 1) {
            _out_("SAVE DATA");
            break;
        }
        else if (x == 2) {
            _out_("SEARCH DATA");
            break;
        }
        else if (x == 3) {
            _out_("RESET DATA");
            break;
        }
        else if (x == 4) {
            _out_("SEARCH DATA IN A LEVEL");
            break;
        }
        else if (x == 5) {
            _out_("LIST DATA IN A LEVEL");
            break;
        }
    }

    return 0;
}

// function saves the level in a file
int input_level(char buffer[], char *buffer_file, FILE *fp)
{
    fp = fopen(buffer_file, "a");

    if (fp == NULL) {
        bf_color("04");
        fprintf(stderr, "\nError : %s\n\n", strerror(errno));
        fclose(fp);
        system("pause");
        return EXIT_FAILURE;
    }

    fprintf(fp, buffer);
    fclose(fp);

    return 0;
}

// function output the level in a file
int output_level(char *buffer_file, FILE *fp)
{
    char c;
    fp = fopen(buffer_file, "r");

    if (fp == NULL) {
        bf_color("04");
        fprintf(stderr, "\nError : No data saved\n\n");
        fclose(fp);
        system("pause");
        return 1;
    }

    while ((c = fgetc(fp)) != EOF) { // 'fgetc' picks up one character in a file via the flux opened 
        if (feof(fp)) { // evaluation which breaks the process of the loop when the end of the file reached
            break;
        }

        fprintf(stdout, "%c", c); // output the character picked up by 'fgetc'
    }

    printf("\n\n");
    fclose(fp);

    return 0;
}

// function which saves the data about the level and individual
int input_data()
{
    char buffer[SIZE];
    int i = 0, j = 0, x_l = 0, x_i = 0;
    int counter_l = 0, counter_i = 0;

    while (true) {
        bf_color("0A");
        output_menu(1);
        printf("[tip] type '0' to exit\n\n");
        printf("[?] Enter number of level to save : ");
        scanf("%d", &x_l);

        if (x_l == 0) {
            return EXIT_SUCCESS;
        }
        
        for (i = 0; i < x_l; i++) {
            bf_color("0A");
            output_menu(1);
            printf("[*] %d level(s) has been saved!\n\n", counter_l);
            printf("[?] Enter level : ");
            fflush(stdout);
            fflush(stdin);
            fgets(buffer, SIZE, stdin);
            input_level(buffer, "level_list.txt", fp); // save the value entered in 'buffer' in 'level_list.txt'
            c_null(buffer);
            
            ++counter_l;
            counter_i = 0;

            strcat(buffer, ".bin");
            fp = fopen(buffer, "wb+");

            if (fp == NULL) {
                bf_color("04");
                fprintf(stderr, "\nError : %s\n\n", strerror(errno));
                fclose(fp);
                system("pause");
                return EXIT_FAILURE;
            }

            printf("[?] Enter individual's number to save : ");
            scanf("%d", &x_i);

            for (j = 1; j <= x_i; j++) { // loop ensure the process of saving of the data in data file
                bf_color("0A");
                output_menu(1);
                printf("[!] ID must be a number\n");
                printf("[*] %d individual(s) has been saved!\n\n", counter_i);
                printf("[?] Enter id : ");
                fflush(stdout);
                fflush(stdin);
                scanf("%d", &R.id);
                printf("[?] Enter fullname : ");
                fflush(stdout);
                fflush(stdin);
                fgets(R.fullname, SIZE, stdin);
                printf("[?] Enter birth's date : ");
                fflush(stdout);
                fflush(stdin);
                fgets(R.date_of_birth, SIZE, stdin);
                printf("[?] Enter sex : ");
                fflush(stdout);
                fflush(stdin);
                fgets(R.sex, 11, stdin);

                if (fwrite(&R, sizeof(R), j, fp) != j) { // function 'fwrite' allows the data entered of being saved in data file
                    bf_color("04");
                    fprintf(stderr, "\nError : %s\n\n", strerror(errno));
                    system("pause");
                    return EXIT_FAILURE;
                }
                else {
                    //bf_color("0F");
                    output_menu(1);
                    fprintf(stdout, "[+] Data has been saved\n\n");
                    system("pause");
                }

                ++counter_i;
            }

            fclose(fp);
        }

        while (true) { // loop used to ask the user if want to add more level apart from the previous
            bf_color("0A");
            output_menu(1);
            printf("[!] Add more level (Y/N): ");
            fflush(stdout);
            fflush(stdin);
            scanf("%c", &c);

            if (c == 'Y' || c == 'y' || c == 'N' || c == 'n') {
                fclose(fp);
                break;
            }
            else if (!isalpha(c)) {
                bf_color("04");
                fprintf(stderr, "\nError : Value must be a letter\n\n");
                system("pause");
                continue;
            }
            else {
                bf_color("04");
                fprintf(stderr, "\nError : Invalid value\n\n");
                system("pause");
                continue;
            }
        }
        if (c == 'N' || c == 'n') {
            fclose(fp);
            return EXIT_SUCCESS;
        }
    }
}

// function which output the data saved in a data container
int output_data()
{
    int x = 0, i = 0, id = 0;
    int counter_i = 0;
    char buffer[SIZE];

    while (true) {
        bf_color("0A");
        output_menu(2);
        printf("[tip] type '0' to exit\n\n");
        printf("[1] Search data in a level\n[2] List data in a level\n\n");
        printf("[?] Enter a choice : ");
        scanf("%d", &x);

        if (x == 0)
            return EXIT_SUCCESS;
        else if (x == 1) { // the first part
            while (true) {
                bf_color("0A");
                output_menu(4);
                printf("[tip] type 'exit' to exit\n\n");
                printf("$LIST OF THE LEVEL : \n");
                printf("--------------------\n");
                if (output_level("level_list.txt", fp) == 1) { // list the level if no error met
                    return EXIT_FAILURE;
                }
                printf("[?] Enter a level : ");
                fflush(stdout);
                fflush(stdin);
                fgets(buffer, SIZE, stdin);
                c_null(buffer);

                if (strcmp(buffer, "exit") == 0) {
                    fclose(fp);
                    break;
                }

                strcat(buffer, ".bin"); // concatenation between level's name and extension '.bin' for having the right data file

                while (true) {
                    bf_color("0A");
                    output_menu(4);
                    fp = fopen(buffer, "rb+");

                    if (fp == NULL) { // evaluation of existence of data file
                        bf_color("04");
                        fprintf(stderr, "\nError : Data not found\n\n");
                        fclose(fp);
                        system("pause");
                        break;
                    }

                    printf("[!] ID must be a number\n[tip] type '0' to exit\n\n");
                    printf("[?] Enter an id : ");
                    scanf("%d", &id);

                    if (id == 0) {
                        fclose(fp);
                        break;
                    }

                    for (i = 1; i != 0; ++i) {
                        if (feof(fp)) { // if end of the file reached, then the data is not found in the data file
                            bf_color("04");
                            fprintf(stderr, "\nError : Data not found\n\n");
                            fclose(fp);
                            system("pause");
                            break;
                        }

                        fread(&W, sizeof(W), i, fp);

                        if (W.id == id) { // condition which checks existence of data
                            bf_color("0A");
                            output_menu(4);
                            printf("\n$DATA FOUND :");
                            printf("\n-------------\n\n");
                            printf("%c ID           : %d\n", 219, W.id);
                            printf("%c FULLNAME     : %s", 219, W.fullname);
                            printf("%c BIRTH'S DATE : %s", 219, W.date_of_birth);
                            printf("%c SEX          : %s\n", 219, W.sex);
                            fclose(fp);
                            system("pause");
                            break;
                        }
                    }
                }
            }
        }
        else if (x == 2) { // the second part
            while (true) {
                bf_color("0A");
                output_menu(5);
                printf("[tip] type 'exit' to exit\n\n");
                printf("$LIST OF THE LEVEL : \n");
                printf("--------------------\n");

                if (output_level("level_list.txt", fp) == 1)
                    return EXIT_FAILURE;

                printf("[?] Enter a level : ");
                fflush(stdout); // free up the flux output for the function concerned which use it 
                fflush(stdin); // free up the flux input for the function concerned which use it
                fgets(buffer, SIZE, stdin);
                c_null(buffer); // get rid of the new line which placed in the end of the string

                if (strcmp(buffer, "exit") == 0) // compare if value of 'buffer' and 'exit' are same
                    break;

                strcat(buffer, ".bin");
                fp = fopen(buffer, "rb+");

                if (fp == NULL) {
                    bf_color("04");
                    fprintf(stderr, "\nError : Data not found\n\n");
                    fclose(fp);
                    system("pause");
                    continue;
                }

                bf_color("0A");
                output_menu(5);
                printf("\n$LIST OF DATA SAVED :");
                printf("\n---------------------\n\n");
                for (i = 1; i != 0; ++i) {
                    if (fread(&W, sizeof(W), i, fp) != i) { // function 'fread' is used to retrieve data in the data file
                        fclose(fp);
                        break;
                    }

                    printf("%c ID           : %d\n", 219, W.id);
                    printf("%c FULLNAME     : %s", 219, W.fullname);
                    printf("%c BIRTH'S DATE : %s", 219, W.date_of_birth);
                    printf("%c SEX          : %s\n", 219, W.sex);
                    ++counter_i; // count the number of the individual saved
                }

                printf("\n[*] %d individual(s) in the level\n\n", counter_i);
                counter_i = 0;
                fclose(fp);
                system("pause");
            }
        }
        else {
            bf_color("04");
            fprintf(stderr, "\nError : Invalid value\n\n");
            system("pause");
            continue;
        }
    }

    return 0;
}

// function which resets the saved data
int reset_data()
{
    fp = fopen("level_list.txt", "r");

    while (true) {
        bf_color("0A");
        output_menu(3);
        if (fp == NULL) { // condition evaluate the existence of the data saved via 'level_list.txt'
            bf_color("04");
            fprintf(stderr, "Error : No data saved\n\n");
            fclose(fp);
            system("pause");
            return EXIT_FAILURE;
        }

        printf("[!] Reset data saved (Y/N): ");
        fflush(stdout);
        fflush(stdin);
        scanf("%c", &c);
        
        if (!isalpha(c)) { // evaluation of the value entered if it is in alphabet
            bf_color("04");
            fprintf(stderr, "\nError : Value must be a letter\n\n");
            system("pause");
            continue;
        }

        if (c == 'Y' || c == 'y') { // if true, the existed data file will be deleted
            //bf_color("0F");
            fclose(fp);
            remove("level_list.txt");
            system("rm *.bin");
            fprintf(stdout, "\n[+] Data reseted\n\n");
            system("pause");
            return EXIT_SUCCESS;
        }
        else if (c == 'N' || c == 'n') { // in other hand, just letting down the deletion
            fclose(fp);
            return EXIT_SUCCESS;
        }
        else {
            bf_color("04");
            fprintf(stderr, "\nError : Invalid value\n\n");
            system("pause");
            continue;
        }
    }

    return 0;
}
