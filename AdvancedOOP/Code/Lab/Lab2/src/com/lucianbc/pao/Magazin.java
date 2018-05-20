package com.lucianbc.pao;

import java.util.Arrays;

public class Magazin {
    private static final int SIZE = 10;

    private int clientPoz = 0;
    private Client[] clienti;
    private ProdusCumparat[][] produse;

    public Magazin() {
        this.clienti = new Client[SIZE];
        this.produse = new ProdusCumparat[SIZE][SIZE];
    }

    public Client userNou(String nume) {
        Client client = new Client(nume);
        if (clientPoz >= clienti.length) {
            clienti = Arrays.copyOf(clienti, clienti.length + SIZE);
            produse = Arrays.copyOf(produse, produse.length + SIZE);
        }
        clienti[clientPoz] = client;
        clientPoz += 1;
        return client;
    }

    public int gasesteClient(String nume) {
        for (int i = 0; i < clienti.length; i++) {
            if (clienti[i] == null) continue;
            if (clienti[i].getNume().equals(nume)) {
                return i;
            }
        }
        return -1;
    }

    public void clientCumpara(String nume, String numeProdus, int cantitate) {
        int pozC = gasesteClient(nume);
        if (pozC == -1) {
            userNou(nume);
            pozC = gasesteClient(nume);
        }
        boolean added = false;
        for (int i = 0; i < produse[pozC].length; i++) {
            if (produse[pozC][i] == null) {
                produse[pozC][i] = new ProdusCumparat(numeProdus, cantitate);
                added = true;
                break;
            }
            if (produse[pozC][i].getNume().equals(numeProdus)) {
                produse[pozC][i].setCantitate(produse[pozC][i].getCantitate() + cantitate);
                added = true;
                break;
            }
        }
        if (!added) {
            produse[pozC] = Arrays.copyOf(produse[pozC], produse[pozC].length + SIZE);
            produse[pozC][produse[pozC].length - SIZE] = new ProdusCumparat(numeProdus, cantitate);
        }
    }
}
