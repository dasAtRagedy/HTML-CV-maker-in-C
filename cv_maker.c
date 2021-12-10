#include <stdio.h>

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

void initialize_html(Category categories[], FILE *fin, int section_count);
void main_section(Category categories[], FILE *fin, int section_count);
void create_section(Category categories[], FILE *fin, int section_count);
void view_sections(Category categories[], FILE *fin, int section_count);
void switch_section(Category categories[], FILE *fin, int section_count);
void delete_section(Category categories[], FILE *fin, int section_count);
void save(Category categories[], FILE *fin, int section_count);
void exit(Category categories[], FILE *fin, int section_count);
int section_select(Category categories[], FILE *fin, int section_count);    //utility function to get the id of member

int main()
{
    Category categories[15];
    printf("Simple CV maker by: Denisas Savickis, Rytis Sapka, Simonas Jarukaitis, Deividas Baltuska\n");
    int option = 0;
    do
    {
        printf("Please select option number\n");
        printMainOptions();
        scanf("%d", &option);
        system("cls");
        switch (option)
        {
        case MAIN_INFO:
           // manage_main_info();
            break;
        case CREATE_SECTION:
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
