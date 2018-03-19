package com.lucianbc.uni.pao.lab4.date;

public class Profesor extends Persoana {

    private String disciplina;

    public String getDisciplina() {
        return disciplina;
    }

    public void setDisciplina(String disciplina) {
        this.disciplina = disciplina;
    }

    @Override
    public String toString() {
        return super.toString() + String.format("(%s)", disciplina);
    }

    @Override
    public String getElementType() {
        return "Profesor";
    }

    @Override
    public String[] getDataFieldNames() {
        return new String[] {"nume", "prenume", "disciplina"};
    }

    @Override
    public void setFieldAt(int position, String value) {

    }

    @Override
    public String getName() {
        return super.getPrenume();
    }

    @Override
    public String getType() {
        return "Profesor";
    }
}
