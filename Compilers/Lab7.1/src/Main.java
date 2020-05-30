import lexer.Lexer;
import syntaxan.SyntaxAnalizator;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Paths;
import java.util.Scanner;

public class Main {
    public static void main (String[] args) throws IOException {
        if (args.length == 0) {
            System.out.println("not enough args");
            return;
        }
        String fileName = args[0];
        Scanner scanner = new Scanner(Paths.get(fileName), StandardCharsets.UTF_8.name());
        String contents = scanner.useDelimiter("\\A").next(); // regex \A mean start of input so we get the whole file content
        scanner.close();
        Lexer lexer = new Lexer();
        lexer.analyzeProgramm(contents);
        lexer.printTokens();
        lexer.printMessages();

        SyntaxAnalizator syntaxAnalizator = new SyntaxAnalizator();
        syntaxAnalizator.setChain(lexer.getTokens());
        syntaxAnalizator.topDown();
        syntaxAnalizator.printTree();
        syntaxAnalizator.printMessages();
    }
}
