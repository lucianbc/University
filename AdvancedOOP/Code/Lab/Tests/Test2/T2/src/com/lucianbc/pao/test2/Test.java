package com.lucianbc.pao.test2;

public class Test {
    public void mmain(String[] args) {
        synchronized (Test.class) {
            for(int i = 0; i < 100; i++) {
                System.out.println(i);
            }
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        Test test = new Test();
        test.mmain(new String[0]);
    }
}
