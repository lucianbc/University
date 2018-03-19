package com.lucianbc.uni.pao.lab4;

import com.lucianbc.uni.pao.lab4.date.Profesor;
import com.lucianbc.uni.pao.lab4.date.Student;
import com.neuralsoft.pao.ppldatabase.MainWindow;

public class Main {

    public static void main(String[] args) {
        MainWindow mainWindow = new MainWindow();
        mainWindow.addElementType(Student.class);
        mainWindow.addElementType(Profesor.class);
        mainWindow.show();
    }
}
