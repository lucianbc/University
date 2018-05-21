package com.lucianbc.pao.test1;

public class ThreadSafety {
    private int x = 0;

    public synchronized void inc(int times) {
        while (times > 0) {
            this.x = this.x + 1;
            times = times - 1;
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        ThreadSafety t = new ThreadSafety();
        Thread t1 = new Thread(() -> t.inc(23));
        Thread t2 = new Thread(() -> t.inc(23));
        t1.start();
        t2.start();
    }
}
