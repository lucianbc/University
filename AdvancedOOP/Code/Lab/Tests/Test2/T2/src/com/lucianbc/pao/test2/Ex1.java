package com.lucianbc.pao.test2;

import java.io.*;

class Ship {
    public String ionel;
}


class Item {
    public Ship parent;
}

class Gun extends Item {
    private int caliber;
}

class Magnum extends Gun implements Serializable {
    public String owner;
}

public class Ex1 {

    public static void main(String[] args) throws Exception {

        Magnum magnum = new Magnum();

        magnum.parent = new Ship();
        magnum.parent.ionel = "ionel";

        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("obiect.txt"))) {
            oos.writeObject(magnum);
        }

        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream("obiect.txt"))) {
            Object o = ois.readObject();
            System.out.println(o);
        }
    }
}
