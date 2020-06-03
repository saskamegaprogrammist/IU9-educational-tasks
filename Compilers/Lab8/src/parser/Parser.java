package parser;

import token.Token;
import token.Utils;

import java.util.ArrayList;
import java.util.HashMap;

public class Parser {
    private ArrayList<Token> chain = null;
    private ArrayList<Rule> rules = null;
    private ArrayList<Neterminal> neterminals = null;
    private HashMap<Neterminal, Integer> rulesMap = null;

    public Parser() {
        this.rules = new ArrayList<>();
    }

    public void setChain(ArrayList<Token> chain) {
        this.chain = chain;
    }

    private int parseTIMES(parser.Utils.PARSE_MODE mode, int index, Rule rule) {
        if (this.chain.get(index).getTag() == Utils.TOKEN_TAG.PLUS) {
            index++;
        }
        if (this.chain.get(index).getTag() == Utils.TOKEN_TAG.QUESTION || this.chain.get(index).getTag() == Utils.TOKEN_TAG.STAR) {
            if (mode == parser.Utils.PARSE_MODE.CALCULATE) {
                rule.addToFirst(new Epsilon());
            }
            index++;
        }
        return index;
    }

    private int parseGP(parser.Utils.PARSE_MODE mode, int index, Rule rule) throws Exception {
        index = this.parseRP(mode, index, rule);
        if (this.chain.get(index).getTag() != Utils.TOKEN_TAG.BR_CLOSE) {
            throw new Exception(String.format("expected \\] token at position:%s", this.chain.get(index).toString()));
        }
        index++;
        return index;
    }

    private int parseRP_E(parser.Utils.PARSE_MODE mode, int index, Rule rule) throws Exception {
        parser.Utils.PARSE_MODE modeTimes = mode;
        parser.Utils.PARSE_MODE modeSelf = mode;
        if (this.chain.get(index).getTag() == Utils.TOKEN_TAG.NETERMINAL) {
            if (mode == parser.Utils.PARSE_MODE.INITIAL) {
                Neterminal newN = new Neterminal(this.chain.get(index).getAttribute());
                this.addNeterminal(newN);
            }
            if (mode == parser.Utils.PARSE_MODE.CALCULATE) {
                Neterminal newN = new Neterminal(this.chain.get(index).getAttribute());
                Rule add = this.rules.get(this.rulesMap.get(newN));
                if (add.hasEps()) {
                    rule.addToFirst(add.getFIRSTwoEps());
                    modeSelf = parser.Utils.PARSE_MODE.CALCULATE;
                } else {
                    rule.addToFirst(add.getFIRST());
                    modeSelf = parser.Utils.PARSE_MODE.SKIP;
                }
            }
            index++;
            index = this.parseTIMES(modeTimes, index, rule);
            if (mode == parser.Utils.PARSE_MODE.CALCULATE) {
                if (rule.hasEps()) {
                    rule.removeEps();
                    modeSelf = parser.Utils.PARSE_MODE.CALCULATE;
                }
            }
            index = this.parseRP_E(modeSelf, index, rule);
            return index;
        } else if (this.chain.get(index).getTag() == Utils.TOKEN_TAG.TERMINAL) {
            if (mode == parser.Utils.PARSE_MODE.CALCULATE) {
                rule.addToFirst(new Terminal(this.chain.get(index).getAttribute()));
                modeTimes = parser.Utils.PARSE_MODE.CALCULATE;
            }
            index++;
            index = this.parseTIMES(modeTimes, index, rule);
            if (mode == parser.Utils.PARSE_MODE.CALCULATE) {
                if (rule.hasEps()) {
                    rule.removeEps();
                    modeSelf = parser.Utils.PARSE_MODE.CALCULATE;

                } else {
                    modeSelf = parser.Utils.PARSE_MODE.SKIP;
                }
            }
            index = this.parseRP_E(modeSelf, index, rule);
            return index;
        } else if (this.chain.get(index).getTag() == Utils.TOKEN_TAG.BR_OPEN) {
            index++;
            index = this.parseGP(mode, index, rule);
            index = this.parseTIMES(mode, index, rule);
            if (mode == parser.Utils.PARSE_MODE.CALCULATE) {
                if (rule.hasEps()) {
                    rule.removeEps();
                    modeSelf = parser.Utils.PARSE_MODE.CALCULATE;

                } else {
                    modeSelf = parser.Utils.PARSE_MODE.SKIP;
                }
            }
            index = this.parseRP_E(modeSelf, index, rule);
            return index;
        } else {
            if (mode == parser.Utils.PARSE_MODE.CALCULATE) {
                rule.addToFirst(new Epsilon());
            }
            return index;
        }
    }


    private int parseRP_END(parser.Utils.PARSE_MODE mode, int index, Rule rule) throws Exception {
        if (this.chain.get(index).getTag() == Utils.TOKEN_TAG.DELIMITER) {
            index++;
            return this.parseRP(mode, index, rule);
        }
        return index;
    }


    private int parseRP(parser.Utils.PARSE_MODE mode, int index, Rule rule) throws Exception {
        index = this.parseRP_E(mode, index, rule);
        return this.parseRP_END(mode, index, rule);
    }

    private int parseRULE(parser.Utils.PARSE_MODE mode, int index) throws Exception {
        if (this.chain.get(index).getTag() != Utils.TOKEN_TAG.NETERMINAL) {
            throw new Exception(String.format("expected neterminal token at position:%s", this.chain.get(index).toString()));
        }
        Rule rule = null;
        if (mode == parser.Utils.PARSE_MODE.INITIAL) {
            Neterminal newRuleN = new Neterminal(this.chain.get(index).getAttribute());
            this.addRule(newRuleN);
        }
        if (mode == parser.Utils.PARSE_MODE.CALCULATE) {
            Neterminal newRuleN = new Neterminal(this.chain.get(index).getAttribute());
            rule = rules.get(rulesMap.get(newRuleN));
        }
        index++;
        if (this.chain.get(index).getTag() != Utils.TOKEN_TAG.EQ) {
            throw new Exception(String.format("expected = token at position:%s", this.chain.get(index).toString()));
        }
        index++;
        index = this.parseRP(mode, index, rule);
        if (this.chain.get(index).getTag() != Utils.TOKEN_TAG.DOT) {
            throw new Exception(String.format("expected . token at position:%s", this.chain.get(index).toString()));
        }
        index++;
        return index;
    }


    private int parseRULE1(parser.Utils.PARSE_MODE mode, int index) throws Exception {
        if (this.chain.get(index).getTag() == Utils.TOKEN_TAG.END) {
            return index;
        }
        index = parseRULE(mode, index);
        index = parseRULE1(mode, index);
        return index;
    }

    private void parseS(parser.Utils.PARSE_MODE mode) throws Exception {
        int index = this.parseRULE(mode, 0);
        this.parseRULE1(mode, index);
    }

    private void parse(parser.Utils.PARSE_MODE mode) throws Exception {
        if (chain == null) {
            throw new Exception("no tokens");
        }
        try {
            this.parseS(mode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private boolean validateRules() {
        for (Neterminal n:neterminals) {
            if(rulesMap.getOrDefault(n, parser.Utils.FAIL) == parser.Utils.FAIL) {
                return false;
            }
        }
        return true;
    }

    private boolean checkFirstChanged() {
        boolean changed = false;
        for (Rule r: rules) {
            changed = changed || r.isChangedFirst();
        }
        return changed;
    }

    private void printFirsts() {
        for (Rule rule:rules) {
            rule.printFirst();
        }
    }

    private void addRule(Neterminal neterminal) {
        int result = rulesMap.getOrDefault(neterminal, parser.Utils.FAIL);
        if (result == parser.Utils.FAIL) {
            this.rules.add(new Rule(neterminal));
            rulesMap.put(neterminal, rulesMap.size());
        }
    }

    private void addNeterminal(Neterminal neterminal) {
        for (Neterminal n: neterminals) {
            if (neterminal == n) return;
        }
        this.neterminals.add(neterminal);
    }


    public void calculateFIRSTs() {
        try {
            rules = new ArrayList<>();
            rulesMap = new HashMap<>();
            neterminals = new ArrayList<>();
            this.parse(parser.Utils.PARSE_MODE.INITIAL);
            if (validateRules()) {
                for (;;) {
                    this.parse(parser.Utils.PARSE_MODE.CALCULATE);
                    if (!checkFirstChanged()) break;
                }
                this.printFirsts();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
