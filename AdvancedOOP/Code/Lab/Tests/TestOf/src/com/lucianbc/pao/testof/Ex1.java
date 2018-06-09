package com.lucianbc.pao.testof;


import javax.swing.*;
import java.io.Serializable;
import java.sql.Connection;
import java.util.List;

class Buck implements Serializable {
    String message;
}

class SpecialBulk extends Buck {
    public Buck subObject;
    public List<Object> children;

    private transient JFrame childFrame;

    public static Connection jdbcConnection;

    public String conc(List<String> l) {
        StringBuffer buffer = new StringBuffer();
        for (int i = 0; i < l.size() - 1; i++) {
            buffer.append(l.get(i));
            buffer.append(",");
        }

        buffer.append(l.get(l.size() - 1));

        return buffer.toString();
    }
}

class Sing {
    private static Sing s;
    private Sing() { }

    void metA() {}
    void metB() {}

    static Sing getInstance() {
        if (s == null) s = new Sing();
        return s;
    }

    public static void main(String[] args) {
        Sing s = Sing.getInstance();
        s.metA();
        s.metB();
    }
}
