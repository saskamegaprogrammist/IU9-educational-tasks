import fautomata.NFA;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Paths;
import java.util.Scanner;
import java.util.regex.Pattern;

public class FileParser {
    private static final String comma = ",";
    private static final String dash = " - ";
    private static final Pattern finalFullPattern = Pattern.compile("finit:\\s*\\[.*\\]");
    private static final Pattern finalPattern = Pattern.compile("finit:\\s*\\[");
    private NFA nfa;
    private String filename;
    FileParser(String filename) {
       this.filename = filename;
    }

    public void parse() {
        int states;
        this.nfa = new NFA();
        try {
            Scanner scanner = new Scanner(Paths.get(filename), StandardCharsets.UTF_8.name());
            if (scanner.hasNextInt()) {
                states = scanner.nextInt();
                this.nfa.setStatesSize(states);

            } else
                return;

            if (scanner.hasNextLine()) {
                scanner.nextLine();
                String line = scanner.findInLine(finalFullPattern);
                line = finalPattern.matcher(line).replaceAll("");
                line = line.substring(0, line.length()-1);
                String[] finals = line.split(comma);
                addFinals(finals);
            } else
                return;

            while (scanner.hasNextLine()) {
               String line = scanner.nextLine();
               if (line.length() == 0) continue;
               String[] path = line.split(dash);
               addTransitions(path);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public NFA getNFA() {
        return this.nfa;
    }
    
    private void addFinals(String[] finals) {
        for (String s:finals) {
            String[] finalState = s.split(dash);
            this.nfa.addFinal(getStateInt(finalState[0]), finalState[1]);
        }
    }

    private void addTransitions(String[] path) {
        switch (path[1]) {
            case "eps":
                this.nfa.addTransition('ε', getStateInt(path[0]), getStateInt(path[2]));
                break;
            case "digit":
                for (char i = '0'; i <= '9'; i++) {
                    this.nfa.addTransition(i, getStateInt(path[0]), getStateInt(path[2]));
                }
                break;
            case "letter":
                for (char i = 'a'; i <= 'z'; i++) {
                    this.nfa.addTransition(i, getStateInt(path[0]), getStateInt(path[2]));
                }
                for (char i = 'A'; i <= 'Z'; i++) {
                    this.nfa.addTransition(i, getStateInt(path[0]), getStateInt(path[2]));
                }
                break;
            case "all":
                for (char i = ' '; i <= '~'; i++) {
                    this.nfa.addTransition(i, getStateInt(path[0]), getStateInt(path[2]));
                }
            case "ws":
                this.nfa.addTransition('\n', getStateInt(path[0]), getStateInt(path[2]));
                this.nfa.addTransition('\r', getStateInt(path[0]), getStateInt(path[2]));
                this.nfa.addTransition('\t', getStateInt(path[0]), getStateInt(path[2]));
                this.nfa.addTransition(' ', getStateInt(path[0]), getStateInt(path[2]));
                break;
            default:
                this.nfa.addTransition(path[1].charAt(0), getStateInt(path[0]), getStateInt(path[2]));
        }
    }
    
    private int getStateInt(String s) {
        return Integer.parseInt(s) - 1;
    }


}
