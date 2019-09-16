package Steck;


public class Steck {
    private int[] buffer;
    private final int N;
    private final int MaxSize = 10;
    private final int MinSize = 0;
    private int index = 0;
    private boolean empty = true;
    private boolean full = false;

    public Steck() {
        this(0);
    }

    public Steck(int N) {
        this.N = N;
        buffer = new int[this.N];
    }

    synchronized public int get() {
        int current_value = 0;

        if (empty) {
            System.out.println("EMPTY");
        } else {
            current_value = buffer[index];
            buffer[index] = 0;
            index--;
            if (index == MinSize) {
                empty = true;
            }
            full = false;
        }

        notify();

        return current_value;
    }

    synchronized public int put() {
        if (full) {
            System.out.println("FULL");
        } else {
        buffer[index] = index;
        index++;
        if (index == MaxSize) {
            full = true;
        }
        empty = false;
        }

        notify();

        return index;
    }


    synchronized public boolean isFull() {
        notify();
        return full;
    }


    synchronized public boolean isEmpty() {
        notify();
        return empty;
    }


    synchronized public void print() {
        for (int i = 0; i < index; i++) {
            System.out.println(buffer[i] + " ");
        }

        notify();
    }

}