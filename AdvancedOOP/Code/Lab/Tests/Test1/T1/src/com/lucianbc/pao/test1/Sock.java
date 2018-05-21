package com.lucianbc.pao.test1;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class Sock {

    private InputStream inputStream;
    private OutputStream outputStream;

    private void openSocket(String host, int port) {
        Socket socket = null;
        try {
            socket = new Socket(host, port);
            this.inputStream = socket.getInputStream();
            this.outputStream = socket.getOutputStream();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // IOException aruncata de instantierea Socketului
    // UnknownHostException aruncata de instantierea Socketului - subclasa a IOException
    // IOException aruncate de getInputStream si getOutputStream daca socket-ul e inchis, deconectat sau canalul de comunicare e inchis
}
