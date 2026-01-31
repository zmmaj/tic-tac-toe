/** @addtogroup tik-tak-toe
 * @{
 */
/**
 * @file
 */

 static volatile const char copyright[] =
 "\t\t@(#) Copyright (c) 2024\n"
 "\t\tZmaj from ZmajSoft.  Use this as you wish.\n";

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "main.h"  // Potez, POTEZ_RACUNARA, POTEZ_IGRACA, functions

char igrac = POTEZ_RACUNARA;    // AI
char covek = POTEZ_IGRACA;      // Human
#define FLUSH fflush(stdin)

bool imaPoteza(char tabla[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tabla[i][j] == ' ')
                return true;
    return false;
}

int vrednost(char t[3][3])
{
    // Redovi
    for (int i = 0; i < 3; i++) {
        if (t[i][0] == t[i][1] && t[i][1] == t[i][2]) {
            if (t[i][0] == igrac) return +10;
            if (t[i][0] == covek) return -10;
        }
    }
    // Kolone
    for (int j = 0; j < 3; j++) {
        if (t[0][j] == t[1][j] && t[1][j] == t[2][j]) {
            if (t[0][j] == igrac) return +10;
            if (t[0][j] == covek) return -10;
        }
    }
    // Dijagonale
    if (t[0][0] == t[1][1] && t[1][1] == t[2][2]) {
        if (t[0][0] == igrac) return +10;
        if (t[0][0] == covek) return -10;
    }
    if (t[0][2] == t[1][1] && t[1][1] == t[2][0]) {
        if (t[0][2] == igrac) return +10;
        if (t[0][2] == covek) return -10;
    }
    return 0;
}

int minimax(char t[3][3], int dubina, bool maks)
{
    int score = vrednost(t);
    if (score == 10 || score == -10) return score;
    if (!imaPoteza(t)) return 0;

    if (maks) {
        int najbolji = -1000;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (t[i][j] == ' ') {
                    t[i][j] = igrac;
                    int val = minimax(t, dubina + 1, false);
                    t[i][j] = ' ';
                    if (val > najbolji) najbolji = val;
                }
        return najbolji;
    } else {
        int najbolji = 1000;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (t[i][j] == ' ') {
                    t[i][j] = covek;
                    int val = minimax(t, dubina + 1, true);
                    t[i][j] = ' ';
                    if (val < najbolji) najbolji = val;
                }
        return najbolji;
    }
}

Potez najboljiPotez(char tabla[3][3])
{
    int najboljaVrednost = -1000;
    Potez najbolji = {-1, -1};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tabla[i][j] == ' ') {
                tabla[i][j] = igrac;
                int val = minimax(tabla, 0, false);
                tabla[i][j] = ' ';
                if (val > najboljaVrednost) {
                    najbolji.red = i;
                    najbolji.kolona = j;
                    najboljaVrednost = val;
                }
            }
    return najbolji;
}

void prikaziTablu(char t[SIZE][SIZE])
{
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("\t\t");  // centriranje tabele u terminalu
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", t[i][j]);
            if (j < SIZE - 1)
                printf("|");
        }
        printf("\n");

        if (i < SIZE - 1)
            printf("\t\t---+---+---\n");  // linija između redova
    }

    printf("\n");
}

void inicijalizuj(char t[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            t[i][j] = ' ';
}

bool krajIgre(char t[3][3])
{
    int score = vrednost(t);
    return score != 0 || !imaPoteza(t);
}

void objaviPobednika(char t[3][3])
{
    int score = vrednost(t);
    if (score == 10) printf("RAČUNAR pobeđuje!\n");
    else if (score == -10) printf("VI pobeđujete!\n");
    else printf("Nerešeno!\n");
}

void igraTicTacToe(int koIgra)
{
    char tabla[3][3];
    inicijalizuj(tabla);

    int x, y, potez;
    while (!krajIgre(tabla)) {
        if (koIgra == 2) { // IGRAČ
            while (true) {
                printf("Unesite potez (1-9): ");
                scanf("%d", &potez);
                if (getchar()) FLUSH;

                if (potez < 1 || potez > 9) {
                    printf("Nevažeći potez. Probajte 1-9.\n");
                    continue;
                }

                x = (potez - 1) / 3;
                y = (potez - 1) % 3;

                if (tabla[x][y] == ' ') {
                    tabla[x][y] = POTEZ_IGRACA;
                    break;
                } else {
                    printf("Polje %d zauzeto. Probajte ponovo.\n", potez);
                }
            }
            prikaziTablu(tabla);
            koIgra = 1;
        } else { // RAČUNAR
            Potez ai = najboljiPotez(tabla);
            tabla[ai.red][ai.kolona] = POTEZ_RACUNARA;
            printf("Računar igra %c na poziciji %d,%d\n", POTEZ_RACUNARA, ai.red + 1, ai.kolona + 1);
            prikaziTablu(tabla);
            koIgra = 2;
        }
    }

    objaviPobednika(tabla);

    char opcija[2];
    printf("Igrati ponovo? (Y/N): ");
    scanf("%c", &opcija[0]);
    if (getchar()) FLUSH;

    if (opcija[0] == 'Y' || opcija[0] == 'y')
        igraTicTacToe(1);
    else
        printf("Kraj igre.\n");
}

void prikaziUputstvo(void)
{
    printf("\n\n");
    printf("\t\t\tTik-Tak-Toe - Uputstvo\n\n");

    printf("\t\tTabla je 3x3 i polja su numerisana 1-9:\n\n");

    int broj = 1;
    for (int i = 0; i < 3; i++) {
        printf("\t\t"); // horizontalno pomeranje tabele
        for (int j = 0; j < 3; j++) {
            printf(" %d ", broj++);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) {
            printf("\t\t---+---+---\n");
        }
    }

    printf("\n\t\tIgrac pritiska broj polja i Enter da odigra potez.\n");
    printf("\t\tAko ste spremni, pritisnite Enter da počne igra...\n");

    getchar();  // Čeka Enter
}



int main(void)
{
    srand(time(NULL));
    printf("Tik-Tak-Toe\nVi = X, Računar = O\n");
    fprintf(stderr, "%s", copyright);
    prikaziUputstvo();
    igraTicTacToe(1); // RAČUNAR počinje
    return 0;
}
