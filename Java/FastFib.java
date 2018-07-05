import java.math.BigInteger;
import java.util.Scanner;

public class FastFib {
    public static void main(String[] args) {
        BigInteger [][] mas1 = new BigInteger[2][2];
        BigInteger [][] mas2 = new BigInteger[2][2];
        mas1[0][0]=mas2[0][0]=BigInteger.ONE;
        mas1[0][1]=BigInteger.ONE;
        mas2[0][1]=BigInteger.ZERO;
        mas1[1][0]=mas2[1][1]=BigInteger.ONE;
        mas1[1][1]=mas2[1][0]=BigInteger.ZERO;

        BigInteger help1=BigInteger.ZERO;
        BigInteger help2=BigInteger.ZERO;
        BigInteger help3=BigInteger.ZERO;
        BigInteger help4=BigInteger.ZERO;

        Scanner in = new Scanner(System.in);
        int n = in.nextInt();

        for (int i = n; i>0; ){
            if (i%2==1){
                help1=(mas2[0][0].multiply(mas1[0][0])).add(mas2[0][1].multiply(mas1[1][0]));
                help2=(mas2[0][0].multiply(mas1[0][1])).add(mas2[0][1].multiply(mas1[1][1]));
                help3=(mas2[1][0].multiply(mas1[0][0])).add(mas2[1][1].multiply(mas1[1][0]));
                help4=(mas2[1][0].multiply(mas1[0][1])).add(mas2[1][1].multiply(mas1[1][1]));
                mas2[0][1]=help2;
                mas2[0][0]=help1;

                mas2[1][1]=help4;
                mas2[1][0]=help3;
            }
            help1=(mas1[0][0].multiply(mas1[0][0])).add(mas1[0][1].multiply(mas1[1][0]));
            help2=(mas1[0][0].multiply(mas1[0][1])).add(mas1[0][1].multiply(mas1[1][1]));
            help3=(mas1[1][0].multiply(mas1[0][0])).add(mas1[1][1].multiply(mas1[1][0]));
            help4=(mas1[1][0].multiply(mas1[0][1])).add(mas1[1][1].multiply(mas1[1][1]));
            mas1[0][1]=help2;
            mas1[0][0]=help1;

            mas1[1][1]=help4;
            mas1[1][0]=help3;
            i/=2;


        }

        System.out.println(mas2[1][0]);

    }
}
