#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// Criptarea fisierului ROT13
char rot13(char ch, char m)
{
    ch = ((ch - m) + 13) % 26 + m;
    return ch;
}

void rotateWord(char word[])
{
    int i;
    for(i = 0; i < strlen(word); i++)
    {
        //printf("%c\n", i);
        if('a' <= word[i] && word[i] <= 'z')
            word[i] = rot13(word[i], 'a');
        else if('A' <= word[i] && word[i] <= 'Z')
            word[i] = rot13(word[i], 'A');
    }
}

void rot13File(char fileName[])
{
    FILE* f = fopen(fileName, "r+");
    char buffer[100];
    while(fscanf(f, "%100s", buffer) == 1)
    {
        rotateWord(buffer);
        fseek(f, -strlen(buffer), SEEK_CUR);
        fwrite(buffer, sizeof(char), strlen(buffer), f);
    }
}
// Sfarsit criptare

// Criptare/Decriptare campuri din struct
typedef struct
{
    char Nume[40];
    int id;
    int salariu;
} Angajat;

void afisareAngajat(Angajat a)
{
    printf("%s %d %d\n", a.Nume, a.id, a.salariu);
}

void putDummy(char fileName[])
{
    Angajat angajati[] = {{"Mircea", 1, 50}, {"Costel", 2, 55}, {"Dorel", 3, 45}};
    int n = sizeof(angajati)/sizeof(angajati[0]);

    FILE* out = fopen(fileName, "wb");

    fwrite(angajati, sizeof(Angajat), n, out);

    fclose(out);
}

void afisare(char fileName[])
{
    Angajat* angajati = NULL;

    FILE* in = fopen(fileName, "rb");

    fseek(in, 0, SEEK_END);

    int n = ftell(in);

    fseek(in, 0, SEEK_SET);

    //printf("%d\n", n);

    angajati = malloc(n);

    n /= sizeof(Angajat);

    fread(angajati, sizeof(Angajat), n, in);

    for(int i = 0; i < n; i++)
        afisareAngajat(angajati[i]);

    fclose(in);
}

void cripteazaFisier(char fileName[], int value)
{
    FILE* in = fopen(fileName, "rb+");

    if(in == NULL) return;

    fseek(in, 0, SEEK_END);

    int n = ftell(in)/sizeof(Angajat);

    fseek(in, 0, SEEK_SET);

    for(int i = 0; i < n; i++)
    {
        int length = sizeof(((Angajat*)0)->Nume);
        char* word = malloc(length);
        fread(word, length, 1, in);
        fseek(in, -length, SEEK_CUR);

        for(int i = 0; i < sizeof(word)/sizeof(value); i++)
        {
            int* unit = word + i * sizeof(value);
            *unit = *unit ^ value;
        }

        fwrite(word, length, 1, in);
        int offset = sizeof(Angajat) - length;
        fseek(in, offset, SEEK_CUR);
    }

    fclose(in);
}

void criptareStructDrive(char fileName[], int value)
{
    //putDummy(fileName);
    //afisare(fileName);
    cripteazaFisier(fileName, value);
}
// Sfarsit criptare

// Romb
void scrieRombDrive(char fileName[])
{
    FILE* file = fopen(fileName, "r+");

    if(file == NULL) return;

    int n;
    fscanf(file, "%d", &n);

    fprintf(file, "\n");

    int i, j;
    for(i = 0; i < 2 * n + 1; i++)
    {
        for(int j = 0; j < 2 * n + 1; j++)
        {
            int val;
            if(i <= n && j <= n) val = i + j - n;
            else if(i <= n && j > n) val = i - (j - 1) % n - 1;
            else if(i > n && j <= n) val = j - (i - 1) % n - 1;
            else val = 3 * n - i - j;

            if(val >= 0)
                fprintf(file, "%d ", val);
            else fprintf(file, "  ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Inlocuire

typedef struct
{
    char src;
    char dest;
} Pair;

void replace(char fileName[], char src, char n)
{
    FILE* myFile;
    myFile = fopen(fileName, "r+");

    char buffer[100];

    while(fscanf(myFile, "%s", buffer) == 1)
    {
        char ok = 0;
        for(int i = 0; i < strlen(buffer); i++)
        {
            if(buffer[i] == src)
            {
                buffer[i] = n;
                ok = 1;
            }
        }

        if(ok == 1)
        {
            fseek(myFile, -strlen(buffer), SEEK_CUR);
            fwrite(buffer, sizeof(char), strlen(buffer), myFile);
        }
    }
    fclose(myFile);
}

void replaceMore(char fileName[], int n_args, ...)
{
    char v[255] = {0};

    va_list myL;
    va_start(myL, n_args);

    for(int i = 0; i < n_args; i++)
    {
        Pair crtPair = va_arg(myL, Pair);
        v[crtPair.src] = crtPair.dest;
    }

    va_end(myL);

    FILE* myFile;
    myFile = fopen(fileName, "r+");

    if(myFile == 0)
        return;


    char buffer[100];

    //printf("%p\n", myFile);

    //fscanf(myFile, "%s", buffer);
    //printf("%s\n", buffer);

    while(fscanf(myFile, "%s", buffer) == 1)
    {
        char ok = 0;
        for(int i = 0; i < strlen(buffer); i++)
        {
            if(v[buffer[i]] != 0)
            {
                buffer[i] = v[buffer[i]];
                ok = 1;
            }
        }

        if(ok == 1)
        {
            fseek(myFile, -strlen(buffer), SEEK_CUR);
            fwrite(buffer, sizeof(char), strlen(buffer), myFile);
        }
    }
    fclose(myFile);
}


// Sfarsit inlocuire

int main()
{
    //rot13File("file.in");

    //criptareStructDrive("Angajati.bin", 0xf99a52ac);

    //scrieRombDrive("romb.txt");

    Pair arg1 = {'a', 'z'};
    Pair arg2 = {'L', 'D'};

    replaceMore("replace.txt", 2, arg1, arg2);

    return 0;
}
