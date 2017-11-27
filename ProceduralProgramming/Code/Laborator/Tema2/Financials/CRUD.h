#ifndef CRUD_H_INCLUDED
#define CRUD_H_INCLUDED

typedef struct {
    int size;
    int capacity;
    void* location;
} Table;

void citesteSalariiPermanenti(void);
void citesteSalariiFreelance(void);
Table citesteAngajati(void);
Table citesteCheltuieli(void);
Table citesteVenituri(void);

void scrieSalariiPermanente(void);
void scrieSalariiFreelance(void);
void scrieAngajati(void);
void scrieCheltuieli(void);
void scrieVenituri(void);

#endif // CRUD_H_INCLUDED
