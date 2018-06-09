package com.lucianbc.pao.studenti;

import com.lucianbc.pao.studenti.dao.StudentiDao;
import com.lucianbc.pao.studenti.data.Student;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "StudentPage")
public class StudentPage extends HttpServlet {
    private StudentiDao studentiDao = StudentiDao.getInstance();

    public StudentPage() {
        System.out.println("Constructor for std page called");
    }

    @Override
    public void init() throws ServletException {
        System.out.println("Init for std page called");
        super.init();
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        int id = Integer.parseInt(request.getParameter("id"));
        int abs = Integer.parseInt(request.getParameter("absente"));
        String nume = request.getParameter("nume");
        Student student = new Student(id, nume, abs);
        studentiDao.insertOrUpdateStudent(student);
        request.getSession().setAttribute("user", new Student(1, "asd", 23));
        response.sendRedirect(request.getRequestURL() + "?" + request.getQueryString());
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        prepareStdPage(request, response);
    }

    private void prepareStdPage(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        int id = Integer.parseInt(request.getParameter("id"));
        Student std = studentiDao.getStudent(id);
        if (std == null) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
            return;
        }
        request.setAttribute("name", std.getNume());
        request.setAttribute("abs", std.getAbsente());
        request.getRequestDispatcher("student.jsp").forward(request, response);
    }
}
