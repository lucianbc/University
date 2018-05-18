package com.lucianbc.pao;

public class Main {

    public static void main(String[] args) {
        Validator validator = new Validator();
        eval("<asd>catelus cu parul cret <p> fura rata din cotet </p></asd>", validator);
        eval("<marcaj1>\n" +
                "<marcaj2>\n" +
                "</marcaj2>\n" +
                "</marcaj1>", validator);
        eval("<marcaj1>\n" +
                "<marcaj2>\n" +
                "</marcaj1>", validator);
        eval("<marcaj1>\n" +
                "pre text\n" +
                "<marcaj2>\n" +
                "Text\n" +
                "</marcaj2>\n" +
                "<marcaj3>\n" +
                "Text2\n" +
                "</marcaj3>\n" +
                "text\n" +
                "</marcaj1>", validator);
    }

    private static void eval(String text, Validator validator) {
        System.out.println(text);
        boolean b = validator.validate(text);
        System.out.println(b);
        System.out.println("---------");
    }
}
