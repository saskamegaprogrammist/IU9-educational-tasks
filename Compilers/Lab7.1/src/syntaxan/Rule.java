package syntaxan;

import java.util.ArrayList;
import java.util.Collections;

public class Rule {
    private ArrayList<TreeNode> rule = null;
    private String neterminalName = null;

    public Rule(ArrayList<TreeNode> rule, String neterminalName) {
        this.neterminalName = neterminalName;
        this.rule = rule;
    }

    public String getNeterminalName() {
        return neterminalName;
    }

    public int getLength() {
        if (rule == null) return 0;
        else return rule.size();
    }

    public ArrayList<TreeNode> getReversed() {
        ArrayList revRule = new ArrayList(rule);
        Collections.reverse(revRule);
        return revRule;
    }

    public TreeNode getNode(int index) {
        return this.rule.get(index);
    }
}
