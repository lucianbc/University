package com.lucianbc.pao.test2;

import java.util.*;

public class Test6 {
    public void showByCondition(Iterable data, Comparator<Object> condition, Object test) {
        for (Object d : data) {
            int rez = condition.compare(d, test);
            if (rez < 0) System.out.println(d);
        }
    }

    public void functon(List myList1, List myList2) {
        for (Object o : myList1) {
            boolean is = false;
            for (Object o2 : myList2) {
                if (o.equals(o2)) {
                    is = true;
                    break;
                }
            }
            if (is) {
                System.out.println(o);
            }
        }
    }
}
