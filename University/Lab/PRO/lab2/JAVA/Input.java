package Inp;
import static java.lang.Math.*;

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
}
