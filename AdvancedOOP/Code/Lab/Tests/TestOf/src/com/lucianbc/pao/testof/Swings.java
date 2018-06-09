package com.lucianbc.pao.testof;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowEvent;

public class Swings {

    public static void main(String[] args) {
    }

    public void show() {
        JFrame jFrame = new JFrame();
        jFrame.setSize(200, 300);
        JPanel contentPane = new JPanel();
        contentPane.setLayout(new BorderLayout());
        JButton btn = new JButton();
        btn.addActionListener(e -> jFrame.dispatchEvent(new WindowEvent(jFrame, WindowEvent.WINDOW_CLOSING)));
        contentPane.add(btn, BorderLayout.CENTER);
        jFrame.setContentPane(contentPane);
        jFrame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        jFrame.setVisible(true);
    }

}
