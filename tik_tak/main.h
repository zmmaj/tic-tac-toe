/** @addtogroup tik-tak-toe
 * @{
 */
/** @file
 */


typedef struct {
    int red;
    int kolona;
} Potez;

#define POTEZ_RACUNARA 'O'
#define POTEZ_IGRACA   'X'
#define SIZE 3

/* Funkcije za Igru Tik-Tak-Toe */
Potez najboljiPotez(char tabla[3][3]);
bool imaPoteza(char tabla[3][3]);
int vrednost(char tabla[3][3]);
int minimax(char tabla[3][3], int dubina, bool maks);
void prikaziTablu(char tabla[3][3]);
void inicijalizuj(char tabla[3][3]);
bool krajIgre(char tabla[3][3]);
void objaviPobednika(char tabla[3][3]);
void igraTicTacToe(int koIgra);
void prikaziUputstvo(void);


/** @}
 */
