package com.lucianbc.pao.studenti.dao;

import com.lucianbc.pao.studenti.data.Student;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class StudentiDao {
    private static StudentiDao instance;
    public static StudentiDao getInstance() {
        if (instance == null) instance = new StudentiDao();
        return instance;
    }

    private Map<Integer, Student> stds;

    private StudentiDao() {
        this.stds = new HashMap<>();
        stds.put(1, new Student(1, "ion", 2));
        stds.put(2, new Student(2, "cristi", 1));
    }

    public List<Student> getStudents() {
        return new ArrayList<>(stds.values());
    }

    public Student getStudent(Integer stdId) {
        return stds.get(stdId);
    }

    public void insertOrUpdateStudent(Student std) {
        stds.put(std.getId(), std);
    }
}
