package Threads;
import Steck.Steck;

import java.io.FileWriter;
import java.io.IOException;


public class Thread1 extends Thread{
    private Steck cr1;
    private FileWriter output;
    private int work_count;

    public Thread1 (Steck cr1, FileWriter file) {
        super("Thread1");
        this.cr1 = cr1;
        this.output = file;
        this.work_count = 0;
        start();
    }

    @Override
    public void run() {
        while (true) {
            if (cr1.isFull()) {
                try {
                output.write(getName() + ": cannnot put new element (steck is full)\n");
                output.flush();
                // break;
                } catch (IOException e){
                    e.printStackTrace();
                    System.exit(1);
                }
            } else {
                // System.out.println(getName() + ": element " + cr1.put() + " was putted");
                try {
                    output.write(getName() + ": element " + cr1.put() + " was putted\n");
                    output.flush();
                } catch (IOException e) {
                    e.printStackTrace();
                    System.exit(1);
                }
            }

            if (work_count >= 500) {
                break;
            }
            work_count++;
        }
    }
}