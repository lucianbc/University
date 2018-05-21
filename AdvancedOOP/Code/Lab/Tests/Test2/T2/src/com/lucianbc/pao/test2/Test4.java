package com.lucianbc.pao.test2;

import java.io.*;
import java.util.LinkedList;
import java.util.List;
import java.util.function.Predicate;

public class Test4 {
    public boolean method(List<Serializable> l, Predicate<Serializable> p, String filename) {
        File file = new File(filename);
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(file))) {
            for (Serializable s : l) {
                if (p.test(s)) {
                    oos.writeObject(s);
                }
            }
        } catch (IOException e) {
            return false;
        }
        return true;
    }

    public List filt(Iterable it, String s) {
        List l = new LinkedList();
        it.forEach(o -> {
            if (o.toString().length() < s.length()) {
                l.add(o);
            }
        });
        return l;
    }

    public static void main(String[] args) throws Exception {
        List<Serializable> l = new LinkedList<>();
        l.add("o1777");
        l.add("o2");
        l.add(33);
        Test4 t = new Test4();
//        t.method(l, x -> true, "lista.txt");

        List ll = t.filt(l, "asd");

        ll.forEach(System.out::println);
    }
}
