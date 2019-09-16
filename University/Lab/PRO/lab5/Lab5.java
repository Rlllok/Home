import Steck.Steck;
import Threads.Thread1;
import Threads.Thread2;
import Threads.Thread3;
import Threads.Thread4;
import Threads.Thread5;
import Threads.Thread5;
import Threads.Thread6;
import CR2.CR2;

import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.Semaphore;
import java.io.FileWriter;
import java.io.IOException;


public class Lab5 {
    public static void main(String args[]){
        Steck steck = new Steck(11);
        CR2 cr2 = new CR2();

        CyclicBarrier barrier = new CyclicBarrier(3);
        ReentrantLock mutex = new ReentrantLock();
        Semaphore sem1 = new Semaphore(0, true);
        Semaphore sem2 = new Semaphore(0, true);

        try {
            FileWriter outputFile = new FileWriter("log.txt");

            Thread1 thread1 = new Thread1(steck, outputFile);
            Thread2 thread2 = new Thread2(steck, cr2, barrier, mutex, outputFile);
            Thread3 thread3 = new Thread3(barrier, cr2, mutex, sem1, sem2, outputFile);
            Thread4 thread4 = new Thread4(steck, outputFile);
            Thread5 thread5 = new Thread5(steck, cr2, barrier, mutex, outputFile);
            Thread6 thread6 = new Thread6(cr2, mutex, sem1, sem2, outputFile);

            try {
                thread1.join();
                thread2.join();
                thread3.join();
                thread4.join();
                thread5.join();
                thread6.join();
            } catch (InterruptedException e) {
                System.out.println("interrupted");
            }

            outputFile.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }


    }
}

