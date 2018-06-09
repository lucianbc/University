package com.lucianbc.pao.testof;

import java.io.*;
import java.util.LinkedList;
import java.util.List;

public class Ex2 {

    public static void main(String[] args) throws Exception {

        ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("fis.txt"));

        oos.writeObject(3);
//        oos.writeObject("unu");
//        oos.writeObject("doi");

        oos.close();

        Ex2 e = new Ex2();

        ObjectInputStream ois = new ObjectInputStream(new FileInputStream("fis.txt"));

        List<String> l = e.func(ois, 2);
        System.out.println(l);
    }

    public List<String> func(ObjectInputStream ois, int nr) {
        List<String> l = new LinkedList<>();

        try {
            Integer a = ois.readInt();

            System.out.println(a);
//
//            int min = a < nr ? a : nr;
//
//            while (min > 0) {
//                String s = ois.readUTF();
//                l.add(s);
//                min--;
//            }

            ois.close();
        } catch (IOException e) {
            System.out.println("Nu s-au putut citi informatii din fisier");
        }

        return l;
    }
}