package com.lucianbc.pao.test1;

import java.io.Serializable;

public class ClasaA {
}

class ClasaB extends ClasaA implements Serializable {
    public String nr;
}

class ClasaC extends ClasaB {
    public Date date;
}

class Date {

}