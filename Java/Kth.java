import java.util.Scanner;

public class Kth {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        long k = in.nextLong();
        long chislo=9;
        long chislo1=9;

        int i=2;
        for (i=2; i<=20; i++){
            if (k<chislo) break;
            else {
                chislo1=chislo;
                chislo+=9*(long)Math.pow(10, i-1)*i;
            }
        }
        if (k<9) System.out.println(k+1);
        else {
            k-=chislo1;
            long nomer= 0;
            nomer = k%(i-1);
            k=(long)k/(i-1);
            k+=Math.pow(10, i-2);

            long nomer1= i-1-nomer;



            long ost=1;


            System.out.println(k);
            System.out.println(nomer);
            System.out.println(nomer1);
            System.out.println(i);



            for (int j=1; j<=nomer1; j++){
                ost=k%10;
                k/=10;
            }
            System.out.println(ost);

        }

    }
}