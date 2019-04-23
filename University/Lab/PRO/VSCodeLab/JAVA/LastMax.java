package LastMax;

public class LastMax {
    public static int LastMaxInColumn(int matrix[][], int N, int M, int column) {
        int max = matrix[0][column];
        int position = -1;

        for (int i = 0; i < N; i++){
            if (max <= matrix[i][column]) {
                max = matrix[i][column];
                position = i;
            }
        }
        return position;
    }
}
