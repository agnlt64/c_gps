#include "repl.h"

void repl_help()
{
    printf("Commandes : \n");
    printf("a - Ajoute une ville\n");
    printf("s - Supprime une ville\n");
    printf("m - Modifie les données d'une ville\n");
    printf("l - Liste les villes\n");
    printf("h - Affiche l'aide\n");
    printf("q - Quitte le programme\n");
}

void repl(GPS_Data data[])
{
    repl_help();

    char command;

    do {
        printf("> ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'h':
            repl_help();
            break;
        case 'l':
            print_gps_arr(data);
            break;
        case 'q':
            return;
        default:
            break;
        }
    } while (command != 'q');
}