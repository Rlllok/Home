package CR2;


public class CR2 {
    public CR2() {}
    
    public static int int_value = 0;
    public static short short_value = 0;
    public static double double_value = 0;
    public static boolean boolean_value = false;

    synchronized public void useValue() {
        System.out.println("int_value + short_value: " + (int_value + short_value));
        System.out.println("short_value - int_value: " + (short_value - int_value));
        System.out.println("double_value + int_value: " + (double_value + int_value));
        System.out.println("!boolean_value: " + !boolean_value);

        notify();
    }

    synchronized public void modValue() {
        int_value++;
        short_value++;
        double_value++;
        boolean_value = !boolean_value;

        notify();
    }
}