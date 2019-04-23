package Output;

public class Output {
    public static void MatrixOutput(int matrix[][], int N, int M) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++)
                System.out.format("%3d", matrix[i][j]);
            System.out.println();
        }
    }
}
