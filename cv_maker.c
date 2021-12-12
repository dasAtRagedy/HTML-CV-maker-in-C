#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    char name[50];
    char html_text[50][256];
    int html_text_count;
} Category;

typedef struct
{
    char name_surname[50];
    char birth_date[11]; //yyyy-mm-dd
    int age;
    char e_mail[100];
    char phone_number[13]; //12 numbers +\n if we use +370 format
    char linkedIn_link[100];
} Main_data;

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



void printMainOptions();

void manage_main_info(Main_data *user_data);
void create_section(Category **categories, int *section_count, int *capacity);

void print_all_sections(Category *categories, int section_count);
void view_sections(Category *categories, int section_count);

void switch_section(Category **categories, int section_count);
void swap_elements(Category **categories, int first, int second);

void delete_section(Category **categories, int *section_count);
void erase_element(Category **categories, int *section_count, int pos);

void save(Main_data * main_data, Category *categories, int section_count);

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
            view_sections(categories, section_count);
            break;
        case SWITCH_SECTION:
            if(section_count == 0)
                printf("Enter a field first!\n");
            else
                switch_section(&categories, section_count);
            break;
        case DELETE_SECTION:
            delete_section(&categories, &section_count);
            break;
        case SAVE:
            save(&user_data, categories, section_count);
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
    user_data->age=number;
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

void create_section(Category **categories, int *section_count, int *capacity)
{
    //DADEDAMA VIETOS I DINAMINI MASYVA
    printf("Input the name of your section (up to 50 symbols): ");
    if(*section_count == *capacity)
    {
        *capacity *= 2;
        *categories = realloc(*categories, *capacity * sizeof(Category));
    }
    //TODO: FIX SUS VALIDACIJA
    scanf("%50[^\n]", (*categories)[*section_count].name);
    scanf("%*[^\n]");
    getc(stdin);
    for (int i = 0; i < 49; ++i)
    {
        //TODO: FIX SUS VALIDACIJA
        printf("Input line %d of text (up to 256 symbols, 'N' to finish)\n: ", i + 1);
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

//UTILITY
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
    _getch();
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
        //TODO: FIX SUS VALIDACIJA
        printf("Input exactly 2 numbers seperated by a space - the id's of elements you wish to swap.\n");
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

//UTILITY
void swap_elements(Category **categories, int first, int second)
{
    Category temporary;
    temporary = (*categories)[first];
    (*categories)[first] = (*categories)[second];
    (*categories)[second] = temporary;
}

void delete_section(Category **categories, int *section_count)
{
    int mem_one;
    bool correct_input = true;
    do
    {
        //TODO: FIX SUS VALIDACIJA
        correct_input = true;
        print_all_sections(*categories, *section_count);
        printf("Input the id of section, that you wish to delete: ");
        scanf("%d", &mem_one);
        if (getchar() != '\n' || mem_one <= 0 || mem_one > section_count)
        {
            correct_input = false;
        }
        system("cls");
        if(!correct_input)
        {
            printf("Incorrect input! Try again.\n");
            fflush(stdin);
        }
    }
    while (correct_input == 0);
    erase_element(categories, section_count, mem_one - 1);
}

void erase_element(Category **categories, int *section_count, int pos)
{
    for (int i = pos; i < *section_count; ++i)
    {
        (*categories)[i] = (*categories)[i + 1];
    }
    (*section_count)--;
}

void save(Main_data * main_data, Category *categories, int section_count)
{
    char fileName[55];
    printf("What should be the fileName(up to 50 symbols): \n");
    scanf("%50[^\n]", fileName);
    fflush(stdin);

    if(strstr(fileName, ".htm") == NULL || (strstr(fileName, ".htm") - fileName != 4) && (strstr(fileName, ".html") - fileName != 5))
    {
        strcat(fileName, ".html");
    }
    FILE *writeFile = fopen(fileName, "w");
    if (writeFile == NULL)
    {
        printf("Error opening file: %s\n", fileName);
        return;
    }
    fprintf(writeFile, "<!DOCTYPE html>\n");
    fprintf(writeFile, "<head>\n");
    fprintf(writeFile, "<title>%s</title>\n", main_data->name_surname);
    fprintf(writeFile, "<style>\n");
    fprintf(writeFile, "@import url('https://fonts.googleapis.com/css2?family=Roboto&display=swap');\n");
    fprintf(writeFile, "body {\n");
    fprintf(writeFile, "   font-family: 'Roboto', sans-serif;\n");
    fprintf(writeFile, "}\n");
    fprintf(writeFile, "</style>\n");
    fprintf(writeFile, "</head>\n");
    fprintf(writeFile, "<body>\n");
    fprintf(writeFile, "<h1>%s</h1>\n", main_data->name_surname);
    fprintf(writeFile, "<h2>email: %s</h2>\n", main_data->e_mail);
    fprintf(writeFile, "<h2>age: %d</h2>\n", main_data->age);
    fprintf(writeFile, "<h2>number: %s</h2>\n", main_data->phone_number);
    fprintf(writeFile, "<h2>LinkedIn: %s</h2>\n", main_data->linkedIn_link);
    for(int i = 0; i < section_count; i++)
    {
        fprintf(writeFile, "<hr>\n");
        fprintf(writeFile, "<h1>%s</h1>\n", categories[i].name);
        fprintf(writeFile, "<p>");
        for(int j = 0; j < categories[i].html_text_count; j++)
        {
            fprintf(writeFile, "%s<br>\n", categories[i].html_text[j]);
        }
        fprintf(writeFile, "</p>\n");
    }
    fprintf(writeFile, "</body>\n");

    fclose(writeFile);
    printf("Saved, press any key to continue\n");
    _getch();
    system("cls");
    fflush(stdin);
}
