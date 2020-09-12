import java.util.Scanner;

public class Gauss {
        public static int determinant(int[][] matrix) {
            if
        }


        public static void main(String[] args) {
            Scanner in = new Scanner(System.in);
            int N = in.nextInt();
            fraction[][] matrix = new fraction[N][N + 1];
            fraction[][] det = new fraction[N][N];
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N + 1; j++) {
                    fraction fr=new fraction(1);
                    matrix[i][j] = new fraction(1);
                    if (j != N) det[i][j] = matrix[i][j];
                }
            }
            for (int i = 1; i < N; i++) {
                for (int ind = 0; ind < i; ind++) {
                    float koeff=matrix[ind][]
                    for (int j = 0; j < N + 1; j++) {

                    }
                }
            }


        }

}
