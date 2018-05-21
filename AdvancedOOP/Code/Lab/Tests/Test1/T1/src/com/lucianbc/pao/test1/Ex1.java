package com.lucianbc.pao.test1;

import java.io.*;
import java.net.Socket;
import java.util.LinkedList;
import java.util.List;

@SuppressWarnings({"SameParameterValue", "UnusedReturnValue"})
public class Ex1 {

    public static void main(String[] args) throws IOException, ClassNotFoundException {
	    Ex1 e1 = new Ex1();

        List<Object> objects = new LinkedList<>();
	    objects.add(new C1(1, "tag1"));
        objects.add(new C1(2, "tag2"));
        objects.add(new C2("11", "12"));
        objects.add(new Terminator());

        e1.serialize(objects, "date.sser");
        e1.deserialize("date.sser");
    }

    private Socket socket;

    public int citesteByte() throws IOException {
        InputStream in = socket.getInputStream();
        return in.read();
    }

    private void serialize(List<Object> objects, String filename) throws IOException {
        File file = new File(filename);
        FileOutputStream fileOutputStream = new FileOutputStream(file);
        ObjectOutputStream oos = new ObjectOutputStream(fileOutputStream);

        for(Object o : objects) {
            oos.writeObject(o);
        }

        fileOutputStream.close();
    }

    private List<Object> deserialize(String filename) throws IOException, ClassNotFoundException {
        File file = new File(filename);
        List<Object> objects = new LinkedList<>();
        try (ObjectInputStream inputStream = new ObjectInputStream(new FileInputStream(file))) {
            while (true) {
                Object o = inputStream.readObject();
                if (o.getClass().equals(Terminator.class)) {
                    break;
                }
                objects.add(o);
            }
        }
        return objects;
    }
}

class C1 implements Serializable {
    int nr;
    String tag;

    public C1(int nr, String tag) {
        this.nr = nr;
        this.tag = tag;
    }
}

class C2 implements Serializable {
    String t1;
    String t2l;

    public C2(String t1, String t2l) {
        this.t1 = t1;
        this.t2l = t2l;
    }
}

class Terminator implements Serializable {
}