package com.lucianbc.pao.test2;

import java.util.LinkedList;
import java.util.List;

public class Test3 {
    public List test = new LinkedList();

    public static void main(String[] args) {
        Test3 t3 = new Test3();
        synchronized (t3.test) {
            for (int i = 0; i < 100; i++) {
                System.out.println(i);
            }
            try {
                t3.test.wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
