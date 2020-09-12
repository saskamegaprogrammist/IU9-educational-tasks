import java.util.Scanner;

public class MaxNumber {

    public static int compare(int[] array, int i, int j){
        if (array[i] == 0 || array[j] == 0) System.out.println(array[i] + " " + array[j]);
        int one = array[i];
        int two = array[j];
        int k1=1;
        int k2=1;
        for (k1=1;one>0; k1++){
            one/=10;
        }
        for (k2=1;two>0; k2++){
            two/=10;
        }
        long comp1, comp2;
        comp1=(long)array[i]*(long)Math.pow(10, k2-1)+array[j];
        comp2=(long)array[j]*(long)Math.pow(10, k1-1)+array[i];
        System.out.println(comp1 + " " + comp2);
        if (array[i] == 0) return (int)-1;
        else if (array[j] == 0) return (int)1;
        else if  (comp1<comp2) return (int)-1;
        else return (int)1;

    }

    public static void swap(int[] array, int i, int j){
        int t=array[i];
        array[i]=array[j];
        array[j]=t;
    }

    public static void bubblesort(int[] array){
        int tek, tek1, bound1, bound, del;
        int sch, sch1;
        for (tek = array.length - 1, tek1 = 0, del = 0; tek - tek1 > 0; del++) {
            if ((del % 2) == 0) {
                for (bound = tek, tek = tek1, sch = tek1; sch < bound; sch++) {
                    if (compare(array, sch, sch + 1) > 0) {
                        swap(array, sch, sch + 1);
                        tek = sch;
                    }
                }
            } else {
                for (bound1 = tek1, tek1 = tek, sch1 = tek; sch1 > bound1; sch1--) {
                    if (compare(array,sch1 - 1, sch1) > 0) {
                        swap(array,sch1 - 1, sch1);
                        tek1 = sch1;
                    }
                }
            }
        }
    }

    public static String toString(int[] array){
        int i;
        String str="";

        for (i=array.length-1; i>=0;i--) {
            str+=array[i] + " ";
        }
        return str;
    }


    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int amount = in.nextInt();
        int [] array = new int[amount];

        for (int i=0; i<amount; i++){
            array[i]=in.nextInt();
        }

        bubblesort(array);

        System.out.println(toString(array));
    }
}
