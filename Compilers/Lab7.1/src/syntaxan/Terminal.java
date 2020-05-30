package syntaxan;

import token.Token;
import token.Utils ;

public class Terminal extends TreeNode {
    private token.Utils.TOKEN_TAG tokenTag;
    private String value;

    public Terminal(Token token) {
        this.type = syntaxan.Utils.TreeNodeType.TERMINAL;
        this.tokenTag = token.getTag();
        this.value = token.getAttribute();
    }

    public Terminal (token.Utils.TOKEN_TAG tag) {
        this.type = syntaxan.Utils.TreeNodeType.TERMINAL;
        this.tokenTag = tag;
    }

    public Terminal(String value, token.Utils.TOKEN_TAG tag) {
        this.type = syntaxan.Utils.TreeNodeType.TERMINAL;
        this.value = value;
        this.tokenTag = tag;
    }

    public Terminal(Token token, Neterminal parent) {
        this.type = syntaxan.Utils.TreeNodeType.TERMINAL;
        this.tokenTag = token.getTag();
        this.value = token.getAttribute();
        this.setParent(parent);
    }
    public Terminal (token.Utils.TOKEN_TAG tag, Neterminal parent) {
        this.type = syntaxan.Utils.TreeNodeType.TERMINAL;
        this.tokenTag = tag;
        this.setParent(parent);
    }


    public Terminal(String value, token.Utils.TOKEN_TAG tag, Neterminal parent) {
        this.type = syntaxan.Utils.TreeNodeType.TERMINAL;
        this.value = value;
        this.tokenTag = tag;
        this.setParent(parent);
    }

    public String getValue() {
        return this.value;
    }

    public Utils.TOKEN_TAG getTokenTag() {
        return tokenTag;
    }

    @Override
    public String toString() {
        return this.value;
    }

    public void printSelf() {
        System.out.print(this.toString());
    }
}
