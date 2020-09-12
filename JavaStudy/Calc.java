import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;

public class Calc {


    public static boolean isNumber(char c) {
        return  (c>=48 && c<=57);
    }
    public static boolean isWSpace(char c) {
        return (c == ' ' || c == '\n' || c == '\t' || c == '\r');
    }
    public static boolean isMathOp(char c) {
        return  (c==42 || c==43 || c==45 || c==47);
    }
    public static boolean isSymbol(char c) {
        return  (c!='&'&&!isNumber(c) && !isMathOp(c) && !isWSpace(c) && c!='(' && c!=')');
    }


    public static ArrayList lexAn(String s, ArrayList vars){
        ArrayList<Object> tokens = new ArrayList();
        ArrayList<Object> error = new ArrayList();
        error.add(-2);

        char [] str = s.toCharArray();
        int par=0;
        Object lastS;
        int i=0;
        while (isWSpace(str[i])) {
            i++;
        }
        if (str[i]=='+' || str[i]=='*' || str[i] == '/') return error;

        lastS="&";

        for (; i<str.length; i++){
            if (isWSpace(str[i])) continue;
            if (str[i] == 40) {
                if (lastS.getClass() ==Integer.class||(lastS.getClass() ==String.class && !lastS.equals("&"))) return error;
                tokens.add("(");
                par++;
                lastS="(";
            }
            if (isMathOp(str[i])) {
                if (lastS.equals("+")|| lastS.equals("-") || lastS.equals("/") || lastS.equals("*")) return error;
                tokens.add(str[i]);
                lastS=str[i];
            }
            if (str[i] ==  41) {
                if (lastS.equals("+")|| lastS.equals("-") || lastS.equals("/") || lastS.equals("*")) return error;
                tokens.add(")");
                par--;
                lastS=")";
            }
            if (isNumber(str[i])){
                if (lastS.getClass() ==Integer.class||(lastS.getClass() ==String.class && !lastS.equals("&"))) return error;
                StringBuilder num = new StringBuilder();

                num.append(str[i]);
                i++;
                for (; i<str.length && isNumber(str[i]); i++){
                    num.append(str[i]);
                }
                i--;
                tokens.add(Integer.parseInt(num.toString()));
                lastS=Integer.parseInt(num.toString());
            }
            if (isSymbol(str[i])){
                if (lastS.getClass() ==Integer.class||(lastS.getClass() ==String.class && !lastS.equals("&"))) return error;
                StringBuilder word = new StringBuilder();
                lastS=str[i];
                word.append(str[i]);
                i++;
                for (; i<str.length && (isSymbol(str[i]) || isNumber(str[i])); i++){
                    word.append(str[i]);
                }
                i--;
                vars.add(word.toString());
                tokens.add(word.toString());
                lastS=word.toString();
            }

        }
        if (lastS.equals("+")|| lastS.equals("-") || lastS.equals("/") || lastS.equals("*")) return error;
        tokens.add('&');
        if (par == 0) return tokens;
        else return error;

    }
    public static int parseF(HashMap vars, ArrayList tokens, int i){
        int Fval=0;
        Object r = getToken(tokens);
        if (r.getClass() ==Integer.class) {
            Fval = (int)r;
            getRidOfToken(tokens);
        }
        if (r.getClass() == String.class && !r.equals("-") && !r.equals("(") && !r.equals(")")) {
            Fval = (int)vars.get(r);
            getRidOfToken(tokens);
        }
        if (r.equals("-")) Fval=0-parseF(vars, tokens, i+1);
        if (r.equals("(")) {
            //System.out.println("yes");
            getRidOfToken(tokens);
            Fval=parseE(vars, tokens, i+1);
            r=getToken(tokens);
            if (!r.equals(")")) System.out.println("NOT R PARENTHESIS");
            getRidOfToken(tokens);
        }

        return Fval;
    }
    public static int parseT_1(HashMap vars, ArrayList tokens, int i, int a){
        Object r = getToken(tokens);
        if (r.equals('*')) {
            getRidOfToken(tokens);
            int b=parseF(vars, tokens, i+1);
            b*=a;
            return parseT_1(vars, tokens, i+2, b);
        }
        if (r.equals('/')) {
            getRidOfToken(tokens);
            int b=parseF(vars, tokens, i+1);
            b=a/b;
            return parseT_1(vars, tokens, i+2, b);
        }
        return a;
    }
    public static int parseT(HashMap vars, ArrayList tokens, int i){
        int a=parseF(vars, tokens, i);
        a=parseT_1(vars, tokens, i+1, a);
        return a;
    }

    public static int parseE_1(HashMap vars, ArrayList tokens, int i, int a){
        Object r = getToken(tokens);
        if (r.equals('+')) {
            getRidOfToken(tokens);
            int b= parseT(vars, tokens, i+1);
            b+=a;
            return parseE_1(vars, tokens, i+2, b);
        }
        if (r.equals('-')) {
            getRidOfToken(tokens);
            int b=parseT(vars, tokens, i+1);
            b=a-b;
            return parseE_1(vars, tokens, i+2, b);
        }
        return a;
    }


    public static int parseE(HashMap vars, ArrayList tokens, int i){
        int a=0;
        a=parseT(vars, tokens, i);
        a=parseE_1(vars, tokens,i+1, a);
        return a;
    }

    public static Object getToken(ArrayList tokens){
        //System.out.println(tokens.get(0));
        return tokens.get(0);
    }

    public static void getRidOfToken(ArrayList tokens){
        tokens.remove(0);
    }

    /*public static int syntAn(HashMap vars, ArrayList<Object> tokens){
        int answer;
        tokens.add('&');
        int pos=0;
        while (!tokens.get(pos).equals('&')){
            parse()
        }
    }*/

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String expr = in.nextLine();
        HashMap vars = new HashMap();
        ArrayList v = new ArrayList();
        ArrayList tokens = new ArrayList();

        tokens = lexAn(expr,v);
        if (tokens.get(0).equals(-2)) System.out.println("error");
        else{
            //System.out.println("GREAT");
            if (v.size()!=0){
                for (int i=0; i<v.size(); i++){
                    if (!vars.containsKey(v.get(i))) vars.put(v.get(i), in.nextInt());
                }
            }

            System.out.println(parseE(vars, tokens,0));


        }


    }
}
