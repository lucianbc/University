package com.lucianbc.pao.test1;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class Filtrare {
    public static List<String> filtru(List<String> lista, Predicate<String> tester) {
        return lista.stream().filter(tester).collect(Collectors.toList());
    }

    public static void main(String[] args) {
        ArrayList<String> list = new ArrayList<>();
        list.add("aaaasdf");
        list.add("aaaadf");
        list.add("aaaasf");
        list.add("aaaasd");
        list.add("aaasdf");
        list.add("aaaaf");

        ArrayList<String> myList = new ArrayList<>(filtru(list, s -> s.length() > 6));
        System.out.println(myList);
    }

}
