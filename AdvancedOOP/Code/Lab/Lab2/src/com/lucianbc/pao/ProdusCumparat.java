package com.lucianbc.pao;

public class ProdusCumparat {
    private String nume;
    private int cantitate;

    public ProdusCumparat(String nume, int cantitate) {
        this.nume = nume;
        this.cantitate = cantitate;
    }

    public int getCantitate() {
        return cantitate;
    }

    public void setCantitate(int cantitate) {
        this.cantitate = cantitate;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }
}
