package Inp;
import static java.lang.Math.*;
import java.util.Scanner;

public class Input {
    public static void RandomMatrix(int matrix[][], int N, int M) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                matrix[i][j] = (int)(Math.random() * 11);
            }
        }
    }

    public static void SortedMatrix(int matrix[][], int N, int M) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                matrix[i][j] = i + j;
            }
        }
    }

    public static void inputMatrix(int matrix[][], int N, int M) {
        Scanner scan = new Scanner(System.in);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                matrix[i][j] = scan.nextInt();
            }
        }
    }
}
