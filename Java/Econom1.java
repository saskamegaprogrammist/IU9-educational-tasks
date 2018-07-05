import java.util.ArrayList;
import java.util.Scanner;

public class Econom1 {

    public static String parse(char[] mass, int ind, ArrayList<String> array){
        String s = "";
        s+="(" + mass[ind];
        ind++;
        if (mass[ind] == '(') {
            String s1=parse(mass, ind+1, array);
            s+=s1;
            ind+=s1.length();
        }
        else {
            s += mass[ind];
            ind++;
        }
        //while (mass[ind] == ')') ind++;
        if (mass[ind] == '(') {
            String s2=parse(mass, ind+1,  array);
            s+=s2;
            ind+=s2.length();
        }
        else  s+=mass[ind];
        s+=")";
        ind+=2;
        int count=0;
        for (int i=0; i<array.size(); i++){
            if (array.get(i).compareTo(s)==0) count++;
        }
        if (count==0) {
            array.add(s);
        }
        return s;

    }


    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String s = in.nextLine();
        char [] mass = s.toCharArray();
        int ind=0;
        ArrayList<String> rezult= new ArrayList<String>();

        String [] array= new String[s.length()];
        for (int i=0; i<s.length(); i++) array[i]="";
        if (mass[ind] != '(') {
            System.out.println(0);
        }
        else {
            String st = parse(mass, 1, rezult);
            int length=0;
            //for (int i=0; i<rezult.size(); i++){
              //  System.out.println(rezult.get(i));
            //}
            System.out.println(rezult.size());
        }
    }
}
