package com.lucianbc.pao.test1;

public class Suma {

    public Integer SUMA(Integer rezultat, int a, int b) {
        rezultat = a + b;
        return 0;
    }

    public static void main(String[] args) {
        Suma suma = new Suma();
        Integer integer = new Integer(0);
        suma.SUMA(integer, 3, 4);
        System.out.println(integer);
    }
}
