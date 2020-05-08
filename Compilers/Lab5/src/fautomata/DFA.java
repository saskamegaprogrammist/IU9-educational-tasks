package fautomata;

import java.util.*;

public class DFA {
    private HashMap<Integer,String> finals = new HashMap<>();
    private int statesSize;
    private ArrayList<ArrayList<Integer>> states;
    private int[][] transitions;
    private NFA nfa;
    private FactorizedAlphabet factorizedAlphabet;
    public final static int wrongState = -1;

    public DFA(NFA nfa) {
        this.nfa = nfa;
        this.initiliazeStates();
        this.determinate();
        this.factorize();
    }

    private void determinate() {
        ArrayList<ArrayList<Integer>> mStates = new ArrayList<>();
        ArrayList<Integer> newAL = new ArrayList<>();
        newAL.add(0);
        ArrayList<Integer> initialState = closure(newAL);
        statesSize++;
        states.add(initialState);
        mStates.add(initialState);
        while (!mStates.isEmpty()){
            ArrayList<Integer> tStates = mStates.remove(mStates.size()-1);
            int tStateNumber = findState(tStates, states);
            for (int i=0; i<Alphabet.getSize();i++) {
                ArrayList<Integer> lStates = new ArrayList<>();
                int letter = i;
                tStates.forEach(state -> {
                   ArrayList<Integer> states = nfa.getTransitionNumber(state, letter);
                    for (int s:states) {
                        if (!lStates.contains(s)) lStates.add(s);
                    }
                });
                if (lStates.size() == 0) continue;
                ArrayList<Integer>uStates = closure(lStates);
                int newStateNumber = findState(uStates, this.states);
                if (newStateNumber == wrongState) {
                    statesSize++;
                    states.add(uStates);
                    transitions[tStateNumber][i] = statesSize-1;
                    findUFinals(uStates, statesSize-1);
                    mStates.add(uStates);
                } else {
                    transitions[tStateNumber][i] = newStateNumber;
                }

            }
        }
    }

    private void findUFinals(ArrayList<Integer> uStates, int uNumber) {
        ArrayList<Integer> uFinals = new ArrayList<>();
        for (Integer state:uStates) {
            if (nfa.isFinal(state)) uFinals.add(state);
        }
        if (uFinals.size() != 0) {
            int min = uFinals.get(0);
            for (Integer state: uFinals) {
                if (state < min) min = state;
            }
            finals.put(uNumber, nfa.getFinal(min));
        }
    }

    private int findState(ArrayList<Integer> newStates, ArrayList<ArrayList<Integer>> allStates) {
        Collections.sort(newStates);
        int length = newStates.size();
        int counter = 0;
        for (ArrayList<Integer> state:allStates) {
            if (state.size() != newStates.size()) {
                counter++;
                continue;
            }
            int i;
            Collections.sort(state);
            for(i=0;i<length;i++) {
                if (!newStates.get(i).equals(state.get(i))) break;
            }
            if (i==length) return counter;
            else counter++;
        }
        return wrongState;
    }

    private void initiliazeStates() {
        int alpSize = Alphabet.getSize();
        int oldStatesSize = this.nfa.getStatesSize();
        transitions = new int[oldStatesSize][alpSize];
        for (int i=0; i<oldStatesSize; i++) {
            for (int j=0; j<alpSize; j++) {
                transitions[i][j]=wrongState;
            }
        }

        states = new ArrayList<>();
    }

    private ArrayList<Integer> closure(ArrayList<Integer> tStates){
        Stack<Integer> newStack = new Stack();
        tStates.forEach(newStack::push);
        ArrayList<Integer> result = new ArrayList<>(tStates);
        while (!newStack.empty()) {
            Integer currentState = newStack.pop();
            ArrayList<Integer> uStates = nfa.getEpsTransition(currentState);
            uStates.forEach(state -> {
                if (!result.contains(state)){
                    result.add(state);
                    newStack.push(state);
                }
            });

        }
        return result;
    }

    public int getFactorizedTransition(int state, char letter) {
//        System.out.println(letter + " " + state + " " + transitions[state][Alphabet.getNumber(letter)]);
        int newLetter = factorizedAlphabet.findLetter(Alphabet.getNumber(letter));
        return transitions[state][newLetter];
    }

    public boolean isFinal(int state) {
        return this.finals.containsKey(state);
    }

    public String getFinal(int state) {
        return this.finals.get(state);
    }

    private void factorize() {
        this.factorizedAlphabet = new FactorizedAlphabet(this);
        int alphSize = FactorizedAlphabet.getSize();
        int [][] newTransitions = new int[statesSize][alphSize];
        for (int i=0; i<statesSize; i++) {
            for (int j=0; j<alphSize; j++) {
                int oldLetter = factorizedAlphabet.getLetter(j).get(0);
                newTransitions[i][j]=transitions[i][oldLetter];
            }
        }
        transitions = newTransitions;
    }

    public boolean compareSymbols(int a, int b) {
        int i = 0;
        for (; i<statesSize; i++) {
            if (transitions[i][a] != transitions[i][b]) break;
        }
        if (i == statesSize) return true;
        else return false;
    }
}
