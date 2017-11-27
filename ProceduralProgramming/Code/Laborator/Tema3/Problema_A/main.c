#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getWord(char** buffer, FILE* input)
{
    int capacity = 15;
    int size = 0;
    (*buffer) = malloc(capacity*sizeof(char));
    char crt;
    crt = fgetc(input);
    while(crt != EOF && strchr(" .,?!\n\t", crt) == NULL)
    {
        if(size == capacity - 1)
        {
            capacity *= 2;
            char *tmp = realloc(*buffer, capacity);
            if(tmp != NULL)
                (*buffer) = tmp;
            else
                break;
        }
        (*buffer)[size++] = crt;
        crt = fgetc(input);
    }
    (*buffer)[size] = '\0';
    if(crt == EOF)
        return 0;
    else if(strlen(*buffer) == 0)
    {
        free(*buffer);
        return getWord(buffer, input);
    }
    else return 1;
}

void rezolvare(void (*rezolver)(char*, FILE*))
{
    FILE *fin, *fout;
    if((fin = fopen("date.in", "r")) == NULL)
    {
        printf("Eroare la deschiderea fisierului de citire!");
        return;
    }

    if((fout = fopen("date.out", "w")) == NULL)
    {
        printf("Eroare la deschiderea fisierului de scriere!");
        return;
    }

    char* myWord = NULL;

    while(getWord(&myWord, fin))
    {
        rezolver(myWord, fout);
    }

    fclose(fin);
    fclose(fout);
}

void rez_1(char* word, FILE* output)
{
    char* p;
    for(p = word; *p; p++) *p = tolower(*p);
    fprintf(output, "%s ", word);
    free(word);
}

void rez_2(char* word, FILE* output)
{
    int isOk = 1;
    char *p;
    for(p = word; *p; ++p) isOk = isOk && (strchr("aeiouAEIOU", *p) != NULL);
    if(isOk)
        fprintf(output, "%s ", word);
    free(word);
}

int main()
{
    printf("Probleme rezolvate:\n");
    printf("1. Scrierea din fisierul 'date.in' in fisierul 'date.out'\n");
    printf("   a tuturor cuvintelor, scrise cu litera mica, despartite\n");
    printf("   printr-un singur spatiu, fara alte semne de punctuatie.\n");
    printf("\n");
    printf("2. Scrierea din fisierul 'date.in' in fisierul 'date.out'\n");
    printf("   a tuturor cuvintelor ce contin numai vocale.\n");
    printf("\n");
    int opt = 0;
    do
    {
        printf("Introduceti optiunea: ");
        scanf("%d", &opt);
    }
    while(opt != 1 && opt != 2);

    if(opt == 1)
        rezolvare(rez_1);
    else rezolvare(rez_2);

    return 0;
}
