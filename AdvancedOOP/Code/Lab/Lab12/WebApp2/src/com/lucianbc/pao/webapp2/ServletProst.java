package com.lucianbc.pao.webapp2;

import javax.annotation.Resource;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.sql.DataSource;
import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

@WebServlet(name = "ServletProst")
public class ServletProst extends HttpServlet {
    @Resource(name = "jdbc/configureDb")
    private DataSource dbRes;


    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = (String)request.getSession().getAttribute("username");
        Integer id = searchUser(username);
        if (id == null) {
            response.getWriter().append("No user found!");
        } else {
            response.getWriter().append(id.toString());
        }
    }

    private Integer searchUser(String username) {
        try (Connection connection = dbRes.getConnection(); PreparedStatement st = connection.prepareStatement("SELECT * from users where username = ?")) {
            st.setString(1, username);
            ResultSet rs = st.executeQuery();
            if (rs.next()) {
                return rs.getInt("user_id");
            } else {
                return null;
            }
        } catch (Exception ex) {
            System.out.println("Crapa");
        }
        return null;
    }
}
