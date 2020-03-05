
import java.util.regex.Matcher ;
import java.util.regex.Pattern ;


 public class IdentVsNumber {
     public static void main(String[] args) {
         test_match("a");
         test_match("aaaaaa123");
     }

     private static void test_match(String text) {

         String ident = "[a-zA-Z&&[^I-M]][\\t\\s]*([a-zA-Z0-9][\\t\\s]*){0,5}";
         String number = "\\+";
         String pattern = "(?<ident>^"+ident+")|(?<number>^"+number+")";

         Pattern p = Pattern.compile(pattern);
         Matcher m = p.matcher(text);
         //System.out.println(m.find());
         if (m.find()) {
             if (m.group("ident") != null) {
                 System.out.println(" Идентификатор " + m.group("ident"));
             } else {
                 System.out.println("Число" + m.group("number"));
             }
         } else {
             System.out.println(" Ошибка ");
         }
     }
 }