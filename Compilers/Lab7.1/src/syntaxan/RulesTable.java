package syntaxan;

import java.util.HashMap;

public class RulesTable {
    private HashMap<Cell, Integer> rulesMap = null;

    public RulesTable() {
        this.rulesMap = new HashMap<>();
    }

    public void addRule(Cell cell, Integer ruleId) {
        this.rulesMap.put(cell, ruleId);
    }

    public Integer getRule(Cell cell) {
        return this.rulesMap.getOrDefault(cell, Utils.ERROR_ID);
    }

}
