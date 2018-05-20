package com.lucianbc.pao.studenti.data;

public class Student {
    private int id;
    private String nume;
    private int absente;

    public Student(int id, String nume, int absente) {
        this.id = id;
        this.nume = nume;
        this.absente = absente;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public int getAbsente() {
        return absente;
    }

    public void setAbsente(int absente) {
        this.absente = absente;
    }
}
