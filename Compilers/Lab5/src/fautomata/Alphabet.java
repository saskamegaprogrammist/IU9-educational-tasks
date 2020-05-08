package fautomata;

public class Alphabet {
    private static final int size = 99;

    public static int getNumber(char symbol) {
        if (symbol == 'ε') return 98;
        if (symbol == '\r') return 96;
        if (symbol == '\t') return 97;
        if (symbol == '\n') return 95;
        return symbol-32;
    }

    public static char getChar(int number) {
        if (number == 98) return 'ε';
        if (number == 96) return '\r';
        if (number == 97) return '\t';
        if (number == 95) return '\n';
        return (char) (number+32);
    }

    public static int getSize() {
        return size;
    }

}
