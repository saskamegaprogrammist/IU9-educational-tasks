import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Lexer {
    private String lastTokenType = "separator";
    private Position position;
    private int state = States.NORMALSTATE;
    private ArrayList<Token> tokens = new ArrayList<>();
    public Lexer(String file) {
        this.position = new Position(file);
        this.iterateTokens();
    }

    private void iterateTokens() {
        Matcher spaces = Pattern.compile("^\\s+").matcher(position.getString());
        if (spaces.find()) {
            position.addIndex(spaces.end());
        }

        while (!position.getString().equals(Language.eof)) {
            Pattern p = Pattern.compile(Language.groups);
            Matcher m = p.matcher(position.getString());
            if (m.find()) {
                if (m.group("separator") != null) {
                    tokens.add(new Token("SEPARATOR", position.toString(), m.group("separator")));
                    position.addIndex( m.group("separator").length());
                    this.state = States.NORMALSTATE;
                    this.lastTokenType = "separator";
                } else {
                    if (!lastTokenType.equals("separator")) {
                        if (this.state == States.NORMALSTATE) {
                            this.state = States.ERRORSTATE;
                            tokens.add(new Token("Syntax Error", position.toString(), ""));
                        }
                        position.next();
                    } else {
                        if (m.group("intIdent") != null) {
                            tokens.add(new Token("INTIDENT", position.toString(), m.group("intIdent")));
                            position.addIndex(m.group("intIdent").length());
                        }
                        if (m.group("floatIdent") != null) {
                            tokens.add(new Token("FLOATIDENT", position.toString(), m.group("floatIdent")));
                            position.addIndex(m.group("floatIdent").length());
                        }
                        if (m.group("number") != null) {
                            tokens.add(new Token("NUMBER", position.toString(), m.group("number")));
                            position.addIndex(m.group("number").length());
                        }
                        this.state = States.NORMALSTATE;
                    }

                    this.lastTokenType = "ident";
                }


            } else {
                if (this.state == States.NORMALSTATE) {
                    this.state = States.ERRORSTATE;
                    tokens.add(new Token("Syntax Error", position.toString(), ""));
                }
                position.next();
            }
        }
    }

    public void printTokens() {
        tokens.forEach(System.out::println);
    }
}
