public class Language {
    private static String intIdent = "[\\p{Alpha}&&[^I-M]][\\t ]*(\\p{Alnum}[\\t ]*){0,5}";
    private static String floatIdent = "[I-M][\\t ]*(\\p{Alnum}[\\t ]*){0,5}";
    private static String number = "(\\p{Digit}[\\t ]*)+";
    private static String separator = "[\\+,][\\t ]*";
    public static String eof = "&";
    static String groups = "(?<intIdent>^"+intIdent+")|(?<number>^"+number+")|(?<floatIdent>^"+floatIdent+")|(?<separator>^"+separator+")";
}
