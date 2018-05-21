package com.lucianbc.pao.test2;

import javax.swing.*;
import java.awt.*;

public class Test7 {
    public JFrame createFrame(String title) {
        JFrame frame = new JFrame();
        frame.setTitle(title);
        JPanel content = new JPanel();
        frame.setContentPane(content);
        content.setLayout(new BorderLayout());
        JTextArea textField = new JTextArea();
        textField.setEditable(false);
        content.add(textField, BorderLayout.CENTER);
        JButton button = new JButton("Click!");
        button.addActionListener(e -> {
            textField.setText("Click!");
        });
        content.add(button, BorderLayout.SOUTH);
        return frame;
    }

    public static void main(String[] args) {
        Test7 t7 = new Test7();
        JFrame frame = t7.createFrame("title");
        frame.setSize(400, 300);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}
