import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Paths;
import java.util.Scanner;

public class LexerRegexpLab {

    public static void main (String[] args) throws IOException {

            String fileName = "programm.txt";
            Scanner scanner = new Scanner(Paths.get(fileName), StandardCharsets.UTF_8.name());
            String contents = scanner.useDelimiter("\\A").next();
            scanner.close();
            contents = contents.concat(Language.eof);
            System.out.println(contents);
            Lexer lexer = new Lexer(contents);
            lexer.printTokens();
    }
}
