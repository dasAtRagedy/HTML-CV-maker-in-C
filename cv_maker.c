#include <stdio.h>

void handleArgs(int argc, char *argv[])
{
    argc = argc;
    return;
}

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

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        handleArgs(argc, argv);
    }

    printf("Simple CV maker by: Denisas Savickis, Rytis Sapka, Simas Jarukaitis, Deividas Bartuska\n");
    int option = 0;
    do
    {
        printMainOptions();
        scanf("%d", &option);
        system("cls");
        switch (option)
        {
        case EXIT:
            break;

        default:
            break;
        }
    } while (option != EXIT);

    return 0;
}