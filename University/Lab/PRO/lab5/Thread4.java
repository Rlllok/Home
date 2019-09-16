package Threads;
import Steck.Steck;

import java.io.FileWriter;
import java.io.IOException;


public class Thread4 extends Thread{
    private Steck cr1;
    private int work_count;
    
    private FileWriter output;

    public Thread4 (Steck cr1, FileWriter output) {
        super("Thread4");
        this.cr1 = cr1;
        this.output = output;
        this.work_count = 0;
        start();
    }

    @Override
    public void run() {
        while (true) {
            try {
                if (cr1.isFull()) {
                    // System.out.println(getName() + ": cannnot put new element (steck is full)");
                    output.write(getName() + ": cannnot put new element (steck is full)\n");
                    // break;
                } else {
                    // System.out.println(getName() + ": element " + cr1.put() + " was putted");
                    output.write(getName() + ": element " + cr1.put() + " was putted\n");
                }
            } catch (IOException e) {
                e.printStackTrace();
                System.exit(1);
            }
            
                    if (work_count >= 500) {
                        break;
                    }
                    work_count++;
        }
    }
}