package com.lucianbc.uni.pao.lab4.date;

public class Student extends Persoana {
    private int an;

    public int getAn() {
        return an;
    }

    public void setAn(int an) {
        this.an = an;
    }

    @Override
    public String toString() {
        return super.toString() +
                " " + an;
    }

    @Override
    public String getElementType() {
        return "Student";
    }

    @Override
    public String[] getDataFieldNames() {
        return new String[] {"nume", "prenume", "an"};
    }

    @Override
    public void setFieldAt(int position, String value) {
        switch (position) {
            case 0:
                this.setNume(value);
                break;
            case 1:
                this.setPrenume(value);
                break;
            case 2:
                this.setAn(Integer.parseInt(value));
                break;
        }
    }

    @Override
    public String getName() {
        return super.getNume();
    }

    @Override
    public String getType() {
        return "Student";
    }
}
