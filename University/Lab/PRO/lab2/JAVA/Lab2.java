import Output.Output;
import Inp.Input;
import LastMax.LastMax;

public class Lab2 {
    public static void main(String[] args) {
        final int N = 10;
        final int M = 8;
        int column = 0;
        int position = -1;

        System.out.println("RandomMatrix: ");
        int matrix[][] = new int [N][M];
        Input.RandomMatrix(matrix, N, M);
        Output.MatrixOutput(matrix, N, M);
        position = LastMax.LastMaxInColumn(matrix, N, M, column);
        System.out.format("Last max in column %d: %d\n", column, matrix[position][column]);
        System.out.format("Last max in column %d position: %d\n", column, position);
        System.out.println("SortedMatrix: ");
        Input.SortedMatrix(matrix, N, M);
        Output.MatrixOutput(matrix, N, M);
        position = LastMax.LastMaxInColumn(matrix, N, M, column);
        System.out.format("Last max in column %d: %d\n", column, matrix[position][column]);
        System.out.format("Last max in column %d position: %d\n", column, position);
    }
}
