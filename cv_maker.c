#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    char name[50];
    char html_text[50][256];
} Category;

typedef struct
{
    char name_surname[50];
    char birth_data[11]; //yyyy-mm-dd
    int how_old;
    char e_mail[100];
    char phone_number[13]; //12 numbers +\n if we use +370 format
    char linkedIn_link[100];
} Main_data;

void manage_main_info();

enum options
{
    MAIN_INFO,
    CREATE_SECTION,
    VIEW_SECTIONS,
    SWITCH_SECTION,
    DELETE_SECTION,
    SAVE,
    EXIT
};

void printMainOptions()
{
    printf("%d) %s\n", MAIN_INFO, "Fill out your main information");
    printf("%d) %s\n", CREATE_SECTION, "Create a new section");
    printf("%d) %s\n", VIEW_SECTIONS, "View all sections");
    printf("%d) %s\n", SWITCH_SECTION, "Switch two sections");
    printf("%d) %s\n", DELETE_SECTION, "Delete a section");
    printf("%d) %s\n", SAVE, "Save your CV");
    printf("%d) %s\n", EXIT, "Exit");
    printf("%s", "Your choice: ");
}

void initialize_html();
void main_section(Category *categories, int *section_count);
void create_section(Category **categories, int *section_count, int *capacity);

void print_all_sections(Category *categories, int section_count);
void view_sections(Category *categories, int section_count);

void switch_section(Category **categories, int section_count);
void swap_elements(Category **categories, int first, int second);

void delete_section(Category **categories[], int *section_count);

void save(Category *categories, int section_count);
void exitProgram(Category **categories, int section_count);

int main()
{
    //komwnrEa
    Category * categories = (Category *)malloc(sizeof(Category));
    int section_count = 0;
    int capacity = 1;
    printf("Simple CV maker by: Denisas Savickis, Rytis Sapka, Simonas Jarukaitis, Deividas Baltuska\n");
    int option = 0;
    do
    {
        printf("Please select option number\n");
        printMainOptions();
        scanf("%d", &option);
        if(getchar() != '\n')
        {
            option = -1;
        }
        system("cls");
        switch (option)
        {
        case MAIN_INFO:
           // manage_main_info();
            break;
        case CREATE_SECTION:
            create_section(&categories, &section_count, &capacity);
            break;
        case VIEW_SECTIONS:
            view_sections(categories, section_count);
            break;
        case SWITCH_SECTION:
            if(section_count == 0)
                printf("Enter a field first!\n");
            else
                switch_section(&categories, section_count);
            break;
        case DELETE_SECTION:
            break;
        case SAVE:
            break;
        case EXIT:
            break;
        default:
            printf("Bad input provided. Try again.\n");
            fflush(stdin);
        }
    } while (option != EXIT);

    return 0;
}

void create_section(Category **categories, int *section_count, int *capacity)
{
    printf("Input the name of your section (up to 50 symbols): ");
    if(*section_count == *capacity)
    {
        *capacity *= 2;
        *categories = realloc(*categories, *capacity * sizeof(Category));
    }
    scanf("%50[^\n]", (*categories)[*section_count].name);
    /* clear remaining symbols in line */
    scanf("%*[^\n]");
    getc(stdin);
    for (int i = 0; i < 49; ++i)
    {
        printf("Input line %d of text (up to 256 symbols, 'N' to finish)\n: ", i + 1);
        /* clear remaining symbols in line */
        scanf("%256[^\n]", (*categories)[*section_count].html_text[i]);
        scanf("%*[^\n]");
        getc(stdin);
        if (strcmp((*categories)[*section_count].html_text[i], "N") == 0)
            break;
        if (i == 48)
            strcpy( (*categories)[*section_count].html_text[i + 1], "N");
    }
    (*section_count)++;
    system("cls");
}

void print_all_sections(Category *categories, int section_count)
{
    for (int i = 0; i < section_count; ++i)
    {
        printf("Section %d: %s\n", i + 1, categories[i].name);
    }
}

void view_sections(Category *categories, int section_count)
{
    print_all_sections(categories, section_count);
    printf("Input anything to return: ");
    scanf("%*d");
    system("cls");
    fflush(stdin);
}

void switch_section(Category **categories, int section_count)
{
    int mem_one, mem_two;
    bool correct_input = true;
    do
    {
        correct_input = true;
        print_all_sections(*categories, section_count);
        printf("Input exactly 2 numbers seperated by a space - the id's of elements you wish to swap.\n");
        int first, second;
        printf("Input the id of the first element you wish to swap: ");
        scanf("%d", &mem_one);
        if (getchar() != '\n' || mem_one <= 0 || mem_one > section_count)
        {
            correct_input = false;
        }
        if (correct_input)
        {
            printf("Input the id of the second element you wish to swap: ");
            scanf("%d", &mem_two);
            if (getchar() != '\n' || mem_two <= 0 || mem_two > section_count)
            {
                correct_input = false;
            }
        }
        system("cls");
        if(!correct_input)
        {
            printf("Incorrect input! Try again.\n");
            fflush(stdin);
        }
    }
    while (correct_input == 0);
    swap_elements(categories, mem_one - 1, mem_two - 1);
}

void swap_elements(Category **categories, int first, int second)
{
    Category temporary;
    temporary = (*categories)[first];
    (*categories)[first] = (*categories)[second];
    (*categories)[second] = temporary;
}
