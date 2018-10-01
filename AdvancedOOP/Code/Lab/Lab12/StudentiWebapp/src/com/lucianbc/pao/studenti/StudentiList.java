package com.lucianbc.pao.studenti;

import com.lucianbc.pao.studenti.dao.StudentiDao;
import com.lucianbc.pao.studenti.data.Student;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Comparator;

public class StudentiList extends HttpServlet {
    private StudentiDao studentiDao;

    public StudentiList() {
        this.studentiDao = StudentiDao.getInstance();
        System.out.println("Constructor called");
    }

    @Override
    public void init() throws ServletException {
        System.out.println("Init called");
        super.init();
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setAttribute("studenti", studentiDao.getStudents());
        request.getRequestDispatcher("studenti.jsp").forward(request, response);
    }
}
