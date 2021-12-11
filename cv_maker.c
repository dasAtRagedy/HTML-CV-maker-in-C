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
    char birth_date[11]; //yyyy-mm-dd
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
void manage_main_info(Main_data *user_data);
void create_section(Category **categories, int *section_count, int *capacity);
void view_sections(Category *categores, int section_count);
void switch_section(Category *categories, int section_count);
void delete_section(Category **categories[], int *section_count);
void save(Category *categories, int section_count);
void exitProgram(Category **categories, int section_count);
int section_select(Category categories[], FILE *fin, int section_count);    //utility function to get the id of member
int num_validate();

int main()
{
    Category * categories = (Category *)malloc(sizeof(Category));
    Main_data user_data;
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
            manage_main_info(&user_data);
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
    }
    while (option != EXIT);

    return 0;
}

void manage_main_info(Main_data *user_data)
{
    char bufferis[257];
    printf("Please enter your name, surname and second name up to 50 symbols, if you have one\n");
    scanf("%256[^\n]", bufferis);
    char c;
    c = getchar();
    while (strlen(bufferis)>50){
        printf("sorry, I expected at most 50 symbols.\nPlease enter your name and surname again\n");
        scanf("%256[^\n]", bufferis);
        c = getchar();
    }
    strcpy(user_data->name_surname, bufferis);
    printf("Please enter your birth date in yyyy-mm-dd format\n");
    scanf("%256[^\n]", bufferis);
    c = getchar();
    int is_date_format_good=0;
    while (!is_date_format_good){
        if (strlen(bufferis)!=10){
            printf("sorry, I expected 10 numbers\nPlease enter birth date in yyyy-mm-dd format\n");
            scanf("%256[^\n]",bufferis);
            c = getchar();
        }
        else if (bufferis[4]!='-'||bufferis[7]!='-'||!isdigit(bufferis[0])||!isdigit(bufferis[1])||!isdigit(bufferis[2])||!isdigit(bufferis[3])||!isdigit(bufferis[5])||!isdigit(bufferis[6])||!isdigit(bufferis[8])||!isdigit(bufferis[9])){
            printf("sorry, that was not correct birth date format\nPlease enter birth date in yyyy-mm-dd format\n");
            scanf("%256[^\n]",bufferis);
            c = getchar();
        }
        else{
            is_date_format_good=1;
        }
    }
    strcpy(user_data->birth_date, bufferis);
    printf("Please enter, how old are you\n");
    int number=num_validate();
    user_data->how_old=number;
    printf("Please enter your email\n"); //there is no regex in c (I think), so there won't be any validation
    scanf("%256[^\n]", bufferis);
    c = getchar();
    strcpy(user_data->e_mail, bufferis);
    printf("Please enter your phone number in format +xxxxxxxxxxx\n");
    scanf("%256[^\n]", bufferis);
    c = getchar();
    int is_phone_number_good=0;
    while (bufferis[0]!='+'&&strlen(bufferis)!=12){
        printf("Sorry, that was not correct phone number format\nPlease enter your phone number in format +xxxxxxxxxxx\n");
        scanf("%256[^\n]", bufferis);
        c = getchar();
    }
    strcpy(user_data->phone_number, bufferis);
    //again, no regex, so there wont be any validation
    printf("Please enter your LinkedIn profile link\n");
    scanf("%256[^\n]", bufferis);
    c = getchar();
    strcpy(user_data->linkedIn_link, bufferis);
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

int num_validate() {
	int check1 = 0, check2 = 1, num;
	while (check1 < check2) {
		if ((scanf("%d", &num) == 1 && num > 0 && num <=100 && getchar() == '\n')) {
			check1++;
		}
		else {
			printf("I dont believe, that your age is %d, please enter you age again\n", num);
			while (getchar() != '\n') {
				;
			}
		}
	}
	return num;
}
