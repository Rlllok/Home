package Threads;
import Steck.Steck;
import CR2.CR2;

import java.io.FileWriter;
import java.io.IOException;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.Semaphore;


public class Thread6 extends Thread{
    private CR2 cr2;
    private ReentrantLock mutex;
    private Semaphore sem1;
    private Semaphore sem2;
    private int work_count;

    private FileWriter output;

    public Thread6 (CR2 cr2, ReentrantLock mutex, Semaphore sem1, Semaphore sem2, FileWriter output) {
        super("Thread6");
        this.mutex = mutex;
        this.cr2 = cr2;
        this.sem1 = sem1;
        this.sem2 = sem2;
        this.output = output;
        this.work_count = 0;
        start();
    }

    @Override
    public void run() {
        while (true) {
            try {
                mutex.lock();
                cr2.modValue();
                // System.out.println(getName() + ": modValue()");
                output.write(getName() + ": modValue()\n");
                mutex.unlock();

                sem1.release();
                output.write(getName() + ": sem1 was released\n");
                try {
                    sem2.acquire();
                    output.write(getName() + ": sem2 was acquired\n");
                } catch (InterruptedException e) {
                    System.out.println("Interrupted");
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