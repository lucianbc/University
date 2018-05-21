package com.lucianbc.pao.test1;

import java.io.*;
import java.util.Random;
import java.util.stream.IntStream;

public class RandomCountToFile {

    public static void main(String[] args) {
        RandomCountToFile f = new RandomCountToFile();
        f.writeRands("rands.txt", 5, 55);
    }

    private void writeRands(String filename, int max, int count) {
        File file = new File(filename);

        Random random = new Random();

        try (FileOutputStream fos = new FileOutputStream(file); PrintWriter writer = new PrintWriter(fos)) {
            IntStream.range(0, count - 1).forEach(e -> writer.print(String.format("%d, ", random.nextInt(max))));
            writer.print(String.format("%d", random.nextInt(max)));
        } catch (FileNotFoundException e) {
            System.out.println("Fisierul nu a fost gasit si nu aputut fi creat");
        } catch (IOException e) {
            System.out.println("Eroare la scrierea in fisier");
        }
    }
}
