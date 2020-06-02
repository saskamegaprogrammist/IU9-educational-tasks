package syntaxan;

import token.Token;
import token.Utils;

import java.util.ArrayList;
import java.util.Stack;

public class SyntaxAnalizator {

    private ArrayList<Message> messages;
    private ArrayList<Token> chain = null;
    private Stack<TreeNode> stack = null;
    private RulesTable rulesTable = null;
    private RulesList rulesList = null;
    private TreeNode treeNode = null;

    public SyntaxAnalizator() {
        this.initializeRules();
        this.messages = new ArrayList<>();
    }

    public void setChain(ArrayList<Token> chain) {
        this.chain = chain;
    }

    private void initializeRules() {
        this.rulesList = new RulesList();
        this.rulesTable = new RulesTable();

        ArrayList<TreeNode> ruleSeq = new ArrayList();
        ruleSeq.add(new Neterminal("S_START"));
        ruleSeq.add(new Neterminal("S_END"));
        int ruleId = rulesList.addRule(new Rule(ruleSeq, "S"));
        rulesTable.addRule(new Cell("S", Utils.TOKEN_TAG.NETERMINAL), ruleId);
        rulesTable.addRule(new Cell("S", Utils.TOKEN_TAG.AXIOM), ruleId);

        ruleSeq = new ArrayList();
        ruleSeq.add(new Neterminal("RULE"));
        ruleSeq.add(new Neterminal("S_START"));
        ruleId = rulesList.addRule(new Rule(ruleSeq, "S_START"));
        rulesTable.addRule(new Cell("S_START", Utils.TOKEN_TAG.NETERMINAL), ruleId);

        ruleSeq = new ArrayList();
        ruleSeq.add(new Neterminal("AXIOM"));
        ruleId = rulesList.addRule(new Rule(ruleSeq, "S_START"));
        rulesTable.addRule(new Cell("S_START", Utils.TOKEN_TAG.AXIOM), ruleId);

        ruleSeq = new ArrayList();
        ruleSeq.add(new Neterminal("RULE"));
        ruleSeq.add(new Neterminal("S_END"));
        ruleId = rulesList.addRule(new Rule(ruleSeq, "S_END"));
        rulesTable.addRule(new Cell("S_END", Utils.TOKEN_TAG.NETERMINAL), ruleId);

        ruleSeq = new ArrayList();
        ruleSeq.add(new Epsilon());
        ruleId = rulesList.addRule(new Rule(ruleSeq, "S_END"));
        rulesTable.addRule(new Cell("S_END", Utils.TOKEN_TAG.END), ruleId);

        ruleSeq = new ArrayList();
        ruleSeq.add(new Terminal(Utils.TOKEN_TAG.NETERMINAL));
        ruleSeq.add(new Terminal(Utils.TOKEN_TAG.EQ));
        ruleSeq.add(new Neterminal("RP_EXPR"));
        ruleId = rulesList.addRule(new Rule(ruleSeq, "RULE"));
        rulesTable.addRule(new Cell("RULE", Utils.TOKEN_TAG.NETERMINAL), ruleId);

        ruleSeq = new ArrayList();
        ruleSeq.add(new Terminal(Utils.TOKEN_TAG.AXIOM));
        ruleSeq.add(new Terminal(Utils.TOKEN_TAG.EQ));
        ruleSeq.add(new Neterminal("RP_EXPR"));
        ruleId = rulesList.addRule(new Rule(ruleSeq, "AXIOM"));
        rulesTable.addRule(new Cell("AXIOM", Utils.TOKEN_TAG.AXIOM), ruleId);

        ruleSeq = new ArrayList();
        ruleSeq.add(new Neterminal("RP"));
        ruleSeq.add(new Neterminal("RP_END"));
        ruleId = rulesList.addRule(new Rule(ruleSeq, "RP_EXPR"));
        rulesTable.addRule(new Cell("RP_EXPR", Utils.TOKEN_TAG.NETERMINAL), ruleId);
        rulesTable.addRule(new Cell("RP_EXPR", Utils.TOKEN_TAG.TERMINAL), ruleId);
        rulesTable.addRule(new Cell("RP_EXPR", Utils.TOKEN_TAG.DELIMITER), ruleId);
        rulesTable.addRule(new Cell("RP_EXPR", Utils.TOKEN_TAG.DOT), ruleId);
//        rulesTable.addRule(new Cell("RP_EXPR", Utils.TOKEN_TAG.END), ruleId);

        ruleSeq = new ArrayList();
        ruleSeq.add(new Terminal(Utils.TOKEN_TAG.DELIMITER));
        ruleSeq.add(new Neterminal("RP_EXPR"));
        ruleId = rulesList.addRule(new Rule(ruleSeq, "RP_END"));
        rulesTable.addRule(new Cell("RP_END", Utils.TOKEN_TAG.DELIMITER), ruleId);

        ruleSeq = new ArrayList();
        ruleSeq.add(new Terminal(Utils.TOKEN_TAG.DOT));
        ruleId = rulesList.addRule(new Rule(ruleSeq, "RP_END"));
        rulesTable.addRule(new Cell("RP_END", Utils.TOKEN_TAG.DOT), ruleId);

        ruleSeq = new ArrayList();
        ruleSeq.add(new Epsilon());
        ruleId = rulesList.addRule(new Rule(ruleSeq, "RP"));
        rulesTable.addRule(new Cell("RP", Utils.TOKEN_TAG.DELIMITER), ruleId);
        rulesTable.addRule(new Cell("RP", Utils.TOKEN_TAG.DOT), ruleId);

        ruleSeq = new ArrayList();
        ruleSeq.add(new Terminal(Utils.TOKEN_TAG.NETERMINAL));
        ruleSeq.add(new Neterminal("RP"));
        ruleId = rulesList.addRule(new Rule(ruleSeq, "RP"));
        rulesTable.addRule(new Cell("RP", Utils.TOKEN_TAG.NETERMINAL), ruleId);

        ruleSeq = new ArrayList();
        ruleSeq.add(new Terminal(Utils.TOKEN_TAG.TERMINAL));
        ruleSeq.add(new Neterminal("RP"));
        ruleId = rulesList.addRule(new Rule(ruleSeq, "RP"));
        rulesTable.addRule(new Cell("RP", Utils.TOKEN_TAG.TERMINAL), ruleId);
    }

    private void topDown() throws Exception {
        if (this.chain == null) {
            throw new Exception("no tokens to parse");
        }
        stack = new Stack<>();
        Neterminal startNeterminal =  new Neterminal("S'");
        stack.push(new Terminal(Utils.TOKEN_TAG.END, startNeterminal));
        stack.push(new Neterminal("S", startNeterminal));
        int i=0;
        for (;;) {
            TreeNode currentTN = stack.peek();
            if (currentTN.type == syntaxan.Utils.TreeNodeType.TERMINAL) {
                Terminal currentTNTerminal = (Terminal) currentTN;
                Token currentTerminal = chain.get(i);
                i++;
                if (currentTNTerminal.getTokenTag() == currentTerminal.getTag()) {
                    Neterminal parent = currentTN.getParent();
                    parent.addChild(new Terminal(currentTerminal));
                    currentTN.setParent(parent);
                    stack.pop();
                } else {
                    this.messages.add(new Message("should be terminal", currentTNTerminal, currentTerminal));
                    break;
                }
            } else {
                Neterminal currentTNNeterminal = (Neterminal) currentTN;
                Token currentNeterminal = chain.get(i);
                Integer ruleId = rulesTable.getRule(new Cell(currentTNNeterminal.getName(), currentNeterminal.getTag()));
                Neterminal newNet;
                if (ruleId == syntaxan.Utils.ERROR_ID) {
                    this.messages.add(new Message("no rule found", currentTNNeterminal, currentNeterminal));
                    break;
                } else {
                    Neterminal parent = currentTN.getParent();
                    newNet = new Neterminal(currentTNNeterminal.getName(), ruleId);
                    parent.addChild(newNet);
                    currentTN.setParent(parent);
                    stack.pop();
                }
                Rule r = rulesList.getRule(ruleId);
                ArrayList<TreeNode> newNodes = r.getReversed();
                for (TreeNode tN:newNodes) {
                    tN.setParent(newNet);
                    if (tN.getType() != syntaxan.Utils.TreeNodeType.EPSILON) stack.push(tN);
                }
            }
            if (currentTN.getType() == syntaxan.Utils.TreeNodeType.TERMINAL &&
                    ((Terminal) currentTN).getTokenTag() == Utils.TOKEN_TAG.END) break;
        }
        ArrayList<TreeNode> chNodes = startNeterminal.getChildNodes();
        if (chNodes.size()>0) {
            treeNode =  chNodes.get(0);
        }
    }

    public void printTree() {
        if (treeNode == null) {
            try {
                this.topDown();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        if (treeNode != null) {
            ((Neterminal) treeNode).printSelf(0);
        }
    }

    public ArrayList<Message> getMessages() {
        return this.messages;
    }

    public void printMessages() {
        messages.forEach(System.out::println);
    }
}
