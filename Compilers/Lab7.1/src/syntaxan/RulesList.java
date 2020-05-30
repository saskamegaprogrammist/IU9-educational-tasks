package syntaxan;

import java.util.ArrayList;

public class RulesList {
    private ArrayList<Rule> list = null;

    public RulesList() {
        list = new ArrayList<>();
    }

    public int addRule(Rule newRule) {
        list.add(newRule);
        return list.size()-1;
    }

    public Rule getRule(int i) {
        return list.get(i);
    }

    public int getLength() {
        if (list == null) return 0;
        else return list.size();
    }

}
