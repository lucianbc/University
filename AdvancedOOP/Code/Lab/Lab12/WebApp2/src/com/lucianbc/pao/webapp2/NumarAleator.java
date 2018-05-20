package com.lucianbc.pao.webapp2;

import javax.annotation.Resource;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.sql.DataSource;
import java.io.IOException;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class NumarAleator extends HttpServlet {


    @Resource(name = "jdbc/myDb")
    private DataSource dbRes;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        double numar = Math.random();
        request.getSession().setAttribute("number", numar);

        try {
            Class.forName("com.mysql.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            System.out.println("Crapa db");
            e.printStackTrace();
        }

        getServletContext().getRequestDispatcher("/index.jsp").forward(request, response);


        try(Connection connection = dbRes.getConnection(); Statement statement = connection.createStatement()) {
            ResultSet rs = statement.executeQuery("select * from calls");
            System.out.println(rs);
        } catch (SQLException e) {
            e.printStackTrace();
        }

    }
}
