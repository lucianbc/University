#include <stdio.h>
#include <stdlib.h>

#define MAX_DIRECTIONS 8
#define procentaj(alive, size) (float)(alive * 100)/(size);

// Variabile globale

/* Pointer int*: board
 *  retine adresa primului element din tabloul
 *  utilizat pentru memorarea tablei pe care se
 *  desfasoara jocul. Acesta este alocat dinamic,
 *  iar pointerul este actualizat la fiecare iteratie.
 */
int* board;

/* int: M, N
 *  dimensiunile tablei de joc:
 *  -N: numarul de linii
 *  -M: numarul de coloane
*/
int N, M;

/* int: maxAlive
 *  variabila ce memoreaza numarul maxim de celule vii
 *  ce a fost inregistrat de-a lungul iteratiilor.
*/
int maxAlive;

/* Pointer spre functie de tip char, cu parametrii (int, int)
 *  acest pointer este fixat la citirea datelor si se refera
 *  la functia utilizata pentru determinarea vecinilor dupa
 *  modelul planar sau toroidal.
*/
char (*disp)(int, int);
// Sfarsit variabile globale

// Declarare functii

/* Functie: fileReadBoard
 *  citeste datele de intrare din fisierul "input.txt", formatate astfel:
 *   -char, modul de determinare al vecinilor: toroid sau plan
 *   -int, numarul de coloane
 *   -int, numarul de linii
 *   -int, numarul de iteratii
 *   -int[][], configuratia initiala a tablei de joc
 *  Returneaza numarul de iteratii
*/
int fileReadBoard(void);

/* Functie: consoleReadBoard
 *  citeste datele de intrare din consola, formatate astfel:
 *   -char, modul de determinare al vecinilor: toroid sau plan
 *   -int, numarul de coloane
 *   -int, numarul de linii
 *   -int, numarul de iteratii
 *   -int[][], configuratia initiala a tablei de joc
 *  Returneaza numarul de iteratii
*/
int consoleReadBoard(void);

/* Functie: showBoard
 *  afiseaza configuratia curenta a tablei de joc
*/
void showBoard(void);

/* Functie: processIteration
 *  proceseaza o noua iteratie din joc
*/
void processIteration(void);

// Sfarsit declarare functii

int main()
{
    int k;
    k = fileReadBoard();

    while(k)
    {
        processIteration();
        k--;
    }

    showBoard();

    float alivePercent = procentaj(maxAlive, M*N);
    printf("%.3f%%\n", alivePercent);

    return 0;
}

// Declarare functii inaccesibile din main

/* Functie: countNeighbours
 *  numara vecinii unei celule
 *  Parametrii:
 *   -x: int: coordonata x a celulei
 *   -y: int: coordonata y a celulei
 *   -transformer: char(*)(int, int): pointer
 *       spre o functie ce reprezinta modul de
 *       determinare al vecinilor dupa modelul
 *       planar sau toroidal
 *  Returneaza numarul de vecini vii ai unei celule
*/
int countNeighbours(int, int, char(*)(int, int));

/* Functie: torusCoord
 *  determina starea unei celule dupa modelul toroidal
 *  Parametrii:
 *   -x: int: coordonata x calculata matematic a celulei
 *   -y: int: coordonata y calculata matematic a celulei
 *  Returneaza starea celulei: 0 -> nepopulata
 *                             1 -> populata
*/
char torusCoord(int, int);

/* Functie: planeCoord
 *  determina starea unei celule dupa modelul planar
 *  Parametrii:
 *   -x: int: coordonata x calculata matematic a celulei
 *   -y: int: coordonata y calculata matematic a celulei
 *  Returneaza starea celulei: 0 -> nepopulata
 *                             1 -> populata
*/
char planeCoord(int, int);


// Sfarsit declarare functii

// Definitii functii
int consoleReadBoard(void)
{
    //citeste coloane, linii
    char p;
    int k;
    scanf("%c%d%d%d", &p, &M, &N, &k);

    if(p == 'P')
        disp = planeCoord;
    else if(p == 'T')
        disp = torusCoord;
    else
    {
        printf("MAPPING METHOD IS NOt RECOGNIZED!\n");
        exit(1);
    }

    board = (int*) malloc(N*M*sizeof(int));

    int nrAlive;
    int i, j;
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < M; j++)
        {
            scanf("%d", board + i * M + j);
            if(*(board + i * M + j))
                nrAlive++;
        }
    }

    if(nrAlive > maxAlive) maxAlive = nrAlive;

    return k;
}

int fileReadBoard(void)
{
    // citire coloane, linii
    char p;
    int k;
    FILE *inputFile;
    if((inputFile = fopen("input.txt", "r")) == NULL)
    {
        printf("ERROR OPENING THE FILE!\n");
        exit(1);
    }

    fscanf(inputFile, "%c%d%d%d", &p, &M, &N, &k);

    printf("M coloane: %d N linii: %d\n", M, N);

    if(p == 'P')
        disp = planeCoord;
    else if(p == 'T')
        disp = torusCoord;
    else
    {
        printf("MAPPING METHOD IS NOt RECOGNIZED!\n");
        exit(1);
    }

    board = (int*) malloc(N*M*sizeof(int));

    int nrAlive;
    int i, j;
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < M; j++)
        {
            fscanf(inputFile, "%d", board + i * M + j);
            if(*(board + i * M + j))
                nrAlive++;
        }
    }

    if(nrAlive > maxAlive) maxAlive = nrAlive;

    fclose(inputFile);

    return k;
}

void showBoard(void)
{
    printf("\n");
    int i, j;
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < M; j++)
            printf("%d ", *(board + i * M + j));
        printf("\n");
    }
}

char torusCoord(int x, int y)
{
    int cx = x < 0 ? M + x : x % M;
    int cy = y < 0 ? N + y : y % N;

    return *(board + cy * M + cx);
}

char planeCoord(int x, int y)
{
    if(x < 0 || y < 0 || x >= M ||y >= N) return 0;
    return *(board + y * M + x);
}

int countNeighbours(int x, int y, char(*transformer)(int, int))
{
    int mx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int my[] = {0, -1, -1, -1, 0, 1, 1, 1};

    int i;

    int brs = 0;

    for(i = 0; i < MAX_DIRECTIONS; i++)
    {
        brs += transformer(x + mx[i], y + my[i]);
    }
    return brs;
}

void processIteration(void)
{
    int nrAlive = 0;
    int i, j;
    int* newBoard = malloc(N*M*sizeof(int));
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < M; j++)
        {
            int nr = countNeighbours(j, i, disp);

            if(nr < 2)
                *(newBoard + i * M + j) = 0;
            else if(nr > 3)
                *(newBoard + i * M + j) = 0;
            else if(*(board + i * M + j) == 1 && (nr == 2 || nr == 3))
            { *(newBoard + i * M + j) = 1; nrAlive++; }
            else if(*(board + i * M + j) == 0 && nr == 3)
            { *(newBoard + i * M + j) = 1; nrAlive++; }
            else
                *(newBoard + i * M + j) = 0;
        }
    }

    if(nrAlive > maxAlive) maxAlive = nrAlive;

    free(board);
    board = newBoard;
    newBoard = NULL;
}
// Sfarsit definitii functii
