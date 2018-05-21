package com.lucianbc.pao.test1;

import java.util.List;

public class TestSync {
    private List<Object> lista;

    public synchronized Object getElement(int poz) {
        return lista.get(poz);
    }

    public synchronized void addElement(Object o) {
        lista.add(o);
    }

    private List<Object> getLista() {
        return lista;
    }
}
