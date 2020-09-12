
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

public class Sync_1 {


    public static void copyDir(String codeWord, ArrayList<String> answer, File Dir, String start){
        File [] Dirfiles = Dir.listFiles();
        for (File s:Dirfiles ) {
            if (s.isFile()) answer.add(codeWord + start + Dir.getName() + "/" + s.getName());
            if (s.isDirectory()) copyDir(codeWord, answer, s,Dir.getName() + "/");
        }
    }


    public static void makeSync(ArrayList<String> answerCopy, ArrayList<String> answerDelete, File [] S, File [] D, String dir){

        int i=0;
        int j=0;
        IOException a = new IOException();

        for (; i < S.length; i++){
             for (j=0; j<D.length; j++){

                 //System.out.println(S[i].getName());
                 //if (D[j] != null) System.out.println(D[j].getName());


                 if (D[j] != null && S[i]!=null && S[i].getName().compareTo(D[j].getName())==0){
                     if (S[i].isDirectory()) {
                         File [] Snew = S[i].listFiles();
                         File [] Dnew = D[j].listFiles();
                         makeSync(answerCopy, answerDelete, Snew, Dnew, dir + S[i].getName()+"/");
                     }
                     if (S[i].isFile() ){
                         try {
                         if (!Arrays.equals(Files.readAllBytes(S[i].toPath()), Files.readAllBytes(D[j].toPath()))){
                             answerDelete.add("DELETE "+dir +D[j].getName());
                             answerCopy.add("COPY "+dir+D[j].getName());
                         }
                     }
                     catch (IOException e){

                     }
                         //System.out.println(S[i].lastModified());
                         //System.out.println(D[j].lastModified());

                     }
                     D[j]=null;
                     S[i]=null;
                     j=D.length+1;
                 }
             }
            /*if (j==D.length-1){
                if (S[i].isFile()) answerCopy.add("COPY "+dir+ S[i].getName());
                if (S[i].isDirectory()) copyDir("COPY ", answerCopy, S[i], "");
            }*/

        }
        for (File f:D) {
            if (f!=null) {
                if (f.isFile()) answerDelete.add("DELETE "+dir+f.getName());
                if (f.isDirectory()) copyDir("DELETE ", answerDelete, f, "");
            }
        }
        for (File f:S) {
            if (f!=null) {
                if (f.isFile()) answerCopy.add("COPY "+dir+f.getName());
                if (f.isDirectory()) copyDir("COPY ", answerCopy, f, "");
            }
        }
    }
    public static void main(String[] args) {
        ArrayList<String> answerCopy= new ArrayList<>();
        ArrayList<String> answerDelete= new ArrayList<>();
        File S = new File(args[0]);

        File D = new File(args[1]);

        File[] Sfiles = S.listFiles();
        File[] Dfiles = D.listFiles();
        /*for (File s:Sfiles ) System.out.println(s.getName());
        for (File s:Dfiles ) System.out.println(s.getName());*/
        makeSync(answerCopy, answerDelete, Sfiles, Dfiles, "");

        if (answerCopy.size() == 0 && answerDelete.size()== 0) System.out.println("IDENTICAL");
        else {

            answerDelete.sort(new Comparator<String>() {
                @Override
                public int compare(String o1, String o2) {
                    return o1.compareTo(o2);
                }
            });
            //System.out.println(answer.size());
            for (String s : answerDelete) System.out.println(s);
            answerCopy.sort(new Comparator<String>() {
                @Override
                public int compare(String o1, String o2) {
                    return o1.compareTo(o2);
                }
            });
            //System.out.println(answer.size());
            for (String s : answerCopy) System.out.println(s);
        }

    }
}
