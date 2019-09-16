package Threads;
import Steck.Steck;
import CR2.CR2;

import java.io.FileWriter;
import java.io.IOException;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.locks.ReentrantLock;


public class Thread5 extends Thread{
    private Steck cr1;
    private CR2 cr2;
    private CyclicBarrier barrier;
    private ReentrantLock mutex;
    private int work_count;

    private FileWriter output;

    public Thread5 (Steck cr1, CR2 cr2, CyclicBarrier barrier, ReentrantLock mutex, FileWriter output) {
        super("Thread5");
        this.cr1 = cr1;
        this.cr2 = cr2;
        this.barrier = barrier;
        this.mutex = mutex;
        this.output = output;
        this.work_count = 0;
        start();
    }

    @Override
    public void run() {
        while (true) {
            try {
                if (cr1.isEmpty()) {
                    // System.out.println(getName() + ": cannnot get new element (steck is empty)");
                    output.write(getName() + ": cannnot get new element (steck is empty)\n");
                    // break;
                } else {
                    int current_element = cr1.get();
                    // System.out.println(getName() + ": element " + current_element + " was getted");
                    output.write(getName() + ": element " + current_element + " was getted\n");
                }

                try {
                    // System.out.println(getName() + ": waiting for barrier");
                    output.write(getName() + ": waiting for barrier\n");
                    barrier.await();
                    // System.out.println(getName() + ": break a barrier");
                    output.write(getName() + ": break a barrien\n");
                } catch (BrokenBarrierException e){
                    e.printStackTrace();
                    break;
                } catch (InterruptedException e) {
                    System.out.println("interrupted");
                    break;
                }
                
                mutex.lock();
                cr2.useValue();
                output.write(getName() + ": useValue()\n");
                mutex.unlock();
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