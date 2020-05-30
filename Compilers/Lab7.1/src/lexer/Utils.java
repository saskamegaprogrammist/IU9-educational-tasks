package lexer;

import java.util.ArrayList;
import java.util.Arrays;

public class Utils {
    public static final ArrayList<Character> symbols= new ArrayList<>(
            Arrays.asList('!', '\"', '#', '$', '%', '&', '\'', '*', '+', ',', '-',
                    '/', ':', ';', '<', '>', '?', '@', '[', ']', '^',
                    '_', '`', '{', '}', '~'));
    public static final char openBracket = '(';
    public static final char closeBracket = ')';
    public static final char delimiter = '|';
    public static final char dot = '.';
    public static final char escape = '\\';
    public static final char equals = '=';

}
