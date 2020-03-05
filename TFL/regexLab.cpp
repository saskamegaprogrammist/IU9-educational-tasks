//
// Created by alexis on 22.12.19.
//

#include <regex>
#include <fstream>
#include <iostream>

using namespace std;
using char_type=char;
using str_type = basic_string<char_type>;

#define FILE_NAME_IN "../files/first.txt"
#define FILE_NAME_OUT "../files/second.xml"


int main() {

    setlocale(LC_ALL, "ru");
    basic_regex<char_type> sentence_reg("[^.]*((блин[А-я]*)|(редиск[А-я]*))+[^.]*\\.", regex::optimize);
    basic_regex<char_type> word_reg("(блин[А-я]*)|(редиск[А-я]*)", regex::optimize);
    ifstream fin(FILE_NAME_IN);
    ofstream fout(FILE_NAME_OUT);

    basic_string<char_type> s((istreambuf_iterator<char_type>(fin)), istreambuf_iterator<char_type>());
    cout << s;

    auto words_begin = sregex_iterator (s.begin(), s.end(), sentence_reg);
    auto words_end = sregex_iterator();
    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        string result_first;
        string result_second;
        smatch match = *i;
        string match_str = match.str();
        regex_replace(back_inserter(result_first), match_str.begin(), match_str.end(), sentence_reg, "<t>$&</t>\n");
        regex_replace(back_inserter(result_second), result_first.begin(), result_first.end(), word_reg, "***");
        cout << result_second<< '\n';
        fout << result_second ;
    }
    fout.close();
    getchar();
    return 0;
}