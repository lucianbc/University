package com.lucianbc.pao.testof;

import javax.swing.*;
import java.sql.*;

class Bulk {
    public static void processLogic() {
        System.out.println("Processing");
    }
}

public class Threads {

    public static void main(String[] args) {
        for (int i = 0; i < 5; i++) {
            Thread t = new Thread(Bulk::processLogic);
            t.start();
        }
    }

    public void confBtn() {
        JButton buton = new JButton();
        buton.addActionListener(e -> System.out.println("Click!"));
    }


    public int count(Connection con, int nr) {
        try(Statement stm = con.createStatement()) {
            ResultSet rs = stm.executeQuery("select count(*) from student where prezente > 5");

            return rs.getInt(1);
        } catch (SQLException ex) {
            System.out.println("Eroare la citirea din baza de date");
        }

        return -1;
    }
}
