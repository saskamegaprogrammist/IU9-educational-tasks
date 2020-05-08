package fautomata;

import java.util.ArrayList;
import java.util.HashMap;

public class NFA {
    private HashMap<Integer,String> finals = new HashMap<>();
    private int statesSize;
    private ArrayList<Integer>[][] transitions;


    public NFA() {
    }

    public void setStatesSize(int states) {
        this.statesSize = states;
        this.initiliazeStates();
    }

    public void addFinal(int state, String kw) {
        this.finals.put(state, kw);
    }



    private void initiliazeStates() {
        int alpSize = Alphabet.getSize();
        transitions = new ArrayList[statesSize][alpSize];
        for (int i=0; i<statesSize; i++) {
            for (int j=0; j<alpSize; j++) {
                transitions[i][j] = new ArrayList<>();
            }
        }
    }

    public int getStatesSize() {
        return this.statesSize;
    }

    public boolean isFinal(int state) {
        return finals.containsKey(state);
    }
    public String getFinal(int state) {
        return this.finals.get(state);
    }

    public void addTransition(char symbol, int initialState, int finalState){
        transitions[initialState][Alphabet.getNumber(symbol)].add(finalState);
    }

    public ArrayList<Integer> getEpsTransition(int state) {
        return getTransition(state, 'ε');
    }

    public ArrayList<Integer> getTransition(int state, char letter) {
        return transitions[state][Alphabet.getNumber(letter)];
    }

    public ArrayList<Integer> getTransitionNumber(int state, int letter) {
        return transitions[state][letter];
    }

}
