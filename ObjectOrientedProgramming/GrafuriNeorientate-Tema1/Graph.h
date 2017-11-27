/**
 * Implementarea unei structuri de date de tip graf
 * ce pune la dispozitie citirea unui graf dintr-un
 * stream de intrare, reprezentat prin lista muchiilor,
 * afisarea acestuia prin aceeasi reprezentare, traversarea
 * grafului in latime si in adancime, verificarea conexitatii
 * grafului si determinarea componentelor conexe prin
 * listele nodurilor din fiecare componenta conexa si
 * determinarea unui graf ce reprezinta reuniunea
 * multimii muchiilor a doua grafuri cu aceeasi lista
 * a nodurilor.
 *
 *
 * 18-Mar-2017
 * Boaca Lucian
 * Universitatea din Bucuresti,
 * Facultatea de Matematica si Informatica
 *
 */

#ifndef GRAFURINEORIENTATE_TEMA1_GRAPH_H
#define GRAFURINEORIENTATE_TEMA1_GRAPH_H


#include <functional>
#include "LinkedList.h"


class Graph {
private:
    int num_edges, num_vertices;

    LinkedList<int> *vertex_adj_lists;

    /**
     * @param num_vertex indexul nodului din reprezentarea interna a grafului
     * @return reprezentarea nodului in formatul primit la intrare
     */
    int translateVertex(int num_vertex);


    /**
     * @brief Traverseaza o componenta conexa a grafului in adancime / latime, in functie de
     *          parametrul "push_end"
     * @param push_endpoint pointer la o functie de introducere a datelor intr-o lista simplu
     *                      inlantuita (la inceputul / finalul listei)
     * @param checked tabloul de adevar ce reprezinta statutul nodurilor la un moment dat (vizitat / nevizitat)
     * @param seed indexul nodului din care se incepe traversarea
     * @return lista nodurilor din componenta conexa traversata, ordonata dupa aparitia acestora in traversarea grafului
     *
     * Traverseaza iterativ o componenta conexa a grafului plecand din nodul "seed" si folosind o lista simplu
     * inlantuita pentru a stoca vecinii unui nod care se viziteaza la un moment dat. Functia de inserare in lista
     * este primita prin parametrul "push_endpoint" si, in functie de aceasta, lista se comporta ca o coada (citire
     * de la inceput, inserare de la final) sau ca o stiva (citire si inserare de la inceput). Astfel, pentru coada,
     * graful este parcurs in latime, iar pentru stiva, in adancime;
     */
    LinkedList<int> * TraverseComponent(void (LinkedList<int>::*push_endpoint)(int val), bool* checked, int seed);

    /**
     * @brief Traverseaza intregul graf reunind traversarile pe fiecare componenta conexa
     * @param push_endpoint ca la functie "TraverseComponent"
     * @return lista nodurilor din intregul graf, ordonata dupa aparitia acestora in traversarea grafului
     */
    LinkedList<int> * Traverse(void (LinkedList<int>::*push_endpoint)(int val));

public:

    Graph();

    /**
     * Constructoru de copiere
     * @param other graful care se copiaza in graful curent
     */
    Graph(const Graph& other);

    /**
     * Operatorul de atribuire
     * @param other graful care se atribuie grafului curent
     * @return referinta catre graful curent
     */
    Graph&operator=(const Graph& other);

    virtual ~Graph();

    /**
     * Supraincarcarea operatorului de citire
     * @param fluxul de intrare din care se citeste graful
     * @param graph graful care se citeste
     * @return referinta catre fluxul de intrare
     */
    friend istream&operator>>(istream& in, Graph &graph);

    /**
     * Supraincarcarea operatorului de scriere
     * @param out fluxul de iesire catre care este directionata afisarea grafului
     * @param graph graful care se afiseaza
     * @return referinta catre fluxul de intrare
     */
    friend ostream&operator<<(ostream& out, Graph &graph);

    /**
     * Traversarea grafului in adancime
     * @return pointer catre lista nodurilor grafului, in ordinea aparitiei lor in traversare
     */
    LinkedList<int> * BreadthFirstTraversal();

    /**
     * Traversarea grafului in latime
     * @return pointer catre lista nodurilor grafului, in ordinea aparitiei lor in traversare
     */
    LinkedList<int> * DepthFirstTraversal();

    /**
     * Determina lista componentelor conexe, reprezentate ca liste de noduri
     * @return pointeri catre listele de noduri ale componentelor conexe
     */
    LinkedList<LinkedList<int> *> * GetConnectedComponents();

    /**
     * Determina daca graful este conex sau nu
     * @return true daca graful este conex, false altfel
     */
    bool isConnected();

    /**
     * Intoarce numarul de noduri ale grafului
     * @return num_vertices
     */
    friend int getVerticesNumber(Graph& g);

    /**
     * Intoarce numarul de muchii ale grafului
     * @return num_edges
     */
    int getEdgesNumber();

    /**
     * Determina lista drumurilor in graf
     * @return pointeri catre listele de noduri accesibile din fiecare nod
     */
    LinkedList<LinkedList<int> *> * GedPathsList();

    /**
     * Determina reuniunea a doua grafuri cu acelasi numar de noduri
     * @param other graful cu care este reunit graful curent
     * @return graful reprezentant reuniunea celor doua grafuri
     */
    Graph operator+(Graph& other);

    void operator--() { cout<<"Dcrementare\n"; }
    void operator--(int) { cout<<"Decrementare postfixata\n"; }
};


#endif //GRAFURINEORIENTATE_TEMA1_GRAPH_H
