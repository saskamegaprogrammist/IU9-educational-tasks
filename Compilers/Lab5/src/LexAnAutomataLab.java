import compiler.Compiler;
import fautomata.DFA;
import fautomata.NFA;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Paths;
import java.util.Scanner;

public class LexAnAutomataLab {

    public static void main (String[] args) throws IOException {
        String nfaFilename = "nfa.txt";
        FileParser fileParser = new FileParser(nfaFilename);
        fileParser.parse();
        NFA nfa = fileParser.getNFA();
        DFA dfa = new DFA(nfa);



        String fileName = args[0];
        Scanner scanner = new Scanner(Paths.get(fileName), StandardCharsets.UTF_8.name());
        String contents = scanner.useDelimiter("\\A").next(); // regex \A mean start of input so we get the whole file content
        scanner.close();
        Compiler compiler = new Compiler(dfa);
        compiler.runLexAn(contents);
        compiler.printTokens();
        compiler.printMessages();
    }
}
