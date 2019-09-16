package Threads;
import Steck.Steck;
import CR2.CR2;

import java.io.FileWriter;
import java.io.IOException;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.locks.ReentrantLock;

import java.util.concurrent.Semaphore;


public class Thread3 extends Thread{
    private CR2 cr2;
    private CyclicBarrier barrier;
    private ReentrantLock mutex;
    private Semaphore sem1;
    private Semaphore sem2;
    private int work_count;

    private FileWriter output;

    public Thread3 (CyclicBarrier barrier, CR2 cr2, ReentrantLock mutex, Semaphore sem1, Semaphore sem2, FileWriter output) {
        super("Thread3");
        this.barrier = barrier;
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
                sem2.release();
                output.write(getName() + ": sem2 was released\n");
                try {
                    sem1.acquire();
                    output.write(getName() + ": sem1 was acquired\n");
                } catch (InterruptedException e) {
                    System.out.println("Interrupted");
                }

                mutex.lock();
                cr2.useValue();
                // System.out.println(getName() + ": useValue()");
                output.write(getName() + ": useValue()\n");
                
                mutex.unlock();

                try {
                    // System.out.println(getName() + ": waigetName() + ": waiting for barrier");
                    output.write(getName() + ": waiting for barrier\n");
                    barrier.await();
                    // System.out.println(getName() + ": break a barrier");
                    output.write(getName() + ": break a barrier");
                } catch (BrokenBarrierException e){
                    e.printStackTrace();
                    break;
                } catch (InterruptedException e) {
                    System.out.println("interrupted");
                    break;
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