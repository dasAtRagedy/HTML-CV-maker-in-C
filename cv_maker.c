#include <stdio.h>

void handleArgs(int argc, char *argv[])
{
    argc = argc;
    return;
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        handleArgs(argc, argv);
    }
    return 0;
}