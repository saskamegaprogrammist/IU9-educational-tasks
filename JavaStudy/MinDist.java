import java.util.Scanner;

public class MinDist {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String s = in.nextLine();
        char x = in.next().charAt(0), y = in.next().charAt(0);

        int min=s.length();

        for (int i=0; i<s.length(); i++){
            if (s.charAt(i) == x) {
                for (int j=i-1, sch=0; j>=0; j--, sch++){
                    if (s.charAt(j) == y) {
                        if (sch<min) min=sch;
                        break;
                    }
                }
                for (int j=i+1, sch=0; j<s.length(); j++, sch++){
                    if (s.charAt(j) == y) {
                        if (sch<min) min=sch;
                        break;
                    }
                }
            }
        }
        System.out.println(min);

    }
}