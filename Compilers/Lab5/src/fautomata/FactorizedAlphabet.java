package fautomata;

import java.util.ArrayList;

public class FactorizedAlphabet {
    private static int size = 0;
    ArrayList<ArrayList<Integer>> alphabet;

    public FactorizedAlphabet(DFA dfa) {
        this.factorize(dfa);
    }

    private void factorize(DFA dfa) {
        alphabet = new ArrayList<>();

        int oldSize = Alphabet.getSize();
        int[] checked = new int[oldSize];
        checked[0] = 1;
        for (int startIndex=0; ; ) {
            ArrayList<Integer> newLetter = new ArrayList<>();
            newLetter.add(startIndex);
            for (int i = startIndex+1; i < oldSize; i++) {
                if (checked[i] == 0) {
                    boolean equal = dfa.compareSymbols(startIndex, i);
                    if (equal) {
                        newLetter.add(i);
                        checked[i] = 1;
                    }
                }
            }
            alphabet.add(newLetter);
            size++;
            int j=startIndex+1;
            for (; j<oldSize; j++) {
                if (checked[j] == 0) {
                    startIndex = j;
                    break;
                }
            }
            if (j==oldSize-1) break;
        }

    }

    public ArrayList<Integer> getLetter(int index) {
        return alphabet.get(index);
    }

    public int findLetter(int oldState) {
        int counter = 0;
        for (ArrayList newLetter: alphabet) {
            if (newLetter.contains(oldState)) return counter;
            else counter++;
        }
        return counter;
    }

    public static int getSize() {
        return size;
    }

}
