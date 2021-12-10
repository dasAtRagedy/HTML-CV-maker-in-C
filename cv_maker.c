#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void view_sections(Category *categores, int section_count);
void switch_section(Category *categories, int section_count);
void delete_section(Category **categories[], int *section_count);
void save(Category *categories, int section_count);
void exitProgram(Category **categories, int section_count);
int section_select(Category categories[], FILE *fin, int section_count);    //utility function to get the id of member

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
            break;
        case SWITCH_SECTION:
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

void create_section(Category ** categories, int *section_count, int *capacity)
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
    for (int i = 0; i < 14; ++i)
    {
        printf("Input line %d of text (up to 256 symbols, 'N' to finish)\n: ", i + 1);
        /* clear remaining symbols in line */
        scanf("%256[^\n]", (*categories)[*section_count].html_text[i]);
        scanf("%*[^\n]");
        getc(stdin);
        if (strcmp((*categories)[*section_count].html_text[i], "N") == 0)
            break;
        if (i == 13)
            strcpy( (*categories)[*section_count].html_text[i + 1], "N");
    }
    (*section_count)++;
    system("cls");
}
