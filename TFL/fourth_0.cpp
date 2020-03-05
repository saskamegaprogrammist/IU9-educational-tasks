//
// Created by alexis on 16.09.19.
//

#include <iostream>
#include <map>
#include <vector>

using namespace std;

static string table [6][6]={
        "", "e", "f", "g", "a", "y",
        "e", "e", "f", "g", "a", "e",
        "f", "f", "f", "g", "a", "f",
        "g", "g", "a", "e", "y", "f",
        "a", "a", "a", "e", "y", "f",
        "y", "e", "g", "g", "g", "y",
};

void permutRepRec(map<string, int> &mapTable, vector<int> &permuts, vector<int> &elements, int m){
    if (m==0){
        //cout << permuts.size() << endl;
        int el = mapTable.find(table[permuts.at(0)][permuts.at(1)])->second;
        bool flag = true;
        int size = elements.size();
        for (int i=0; i<size; i++) {
            if (elements.at(i)==el){
                flag = false;
                break;
            }
        }
        if (flag) elements.push_back(el);

    } else {
        int size = elements.size();
        for (int i=0; i<size; i++) {
            //cout <<" " << table[0][elements.at(i)] << endl;
            permuts.push_back(elements.at(i));
            permutRepRec(mapTable, permuts, elements, m-1);
            permuts.pop_back();
        }
    }
}

void permutRep(map<string, int> &mapTable, vector<int> &elements, int m){
    vector<int> permuts;
    permutRepRec(mapTable, permuts, elements, m);
}

void permutRepRecW(map<string, int> &mapTable, vector<int> &permuts, vector<int> &elements, int m){
    if (m==0){
        int size = permuts.size();
        vector<int> gener;
        for (int i=0; i<size; i++){
            gener.push_back(permuts.at(i));
        }
        //for (int i=0; i<gener.size(); i++) cout << table[0][gener.at(i)] << " " << endl;
        for (;;){
            permutRep(mapTable, gener, size+1);
            if (gener.size() == size) break;
            else size++;
        }
        if (gener.size()==5) {
            for (int i=0; i<permuts.size(); i++) cout << table[0][permuts.at(i)] << " generates this group" << endl;
        }
        cout << endl;
        gener.clear();
        return ;


    } else {
        int size = elements.size();
        vector<int> elemsNew;
        for (int j=0; j<size; j++){
            elemsNew.push_back(elements.at(j));
        }
        for (int i=0; i<size; i++) {
            if (elemsNew.size()<m) break;
            permuts.push_back(elements.at(i));
            vector<int> elemsNewOne;
            for (int j=0; j<elemsNew.size(); j++){
                if (elemsNew.at(j)!=elements.at(i)) elemsNewOne.push_back(elemsNew.at(j));
            }
            elemsNew.clear();
            for (int j=0; j<elemsNewOne.size(); j++){
                elemsNew.push_back(elemsNewOne.at(j));
            }
            permutRepRecW(mapTable, permuts, elemsNew, m-1);
            elemsNewOne.clear();
            permuts.pop_back();
        }
        elemsNew.clear();
    }
}

void permutRepW(map<string, int> &mapTable, vector<int> &elements, int m) {
    vector<int> permuts;
    permutRepRecW(mapTable, permuts, elements, m);

}

int main() {
    map<string, int> mapTable;
    for (int i = 1; i <= 5; i++) {
        mapTable.insert({table[0][i], i});
    }
    bool res = true;
    map<string, int>::iterator it1;
    map<string, int>::iterator it2;
    map<string, int>::iterator it3;
    for (it1 = mapTable.begin(); it1 != mapTable.end() && res; it1++) {
        for (it2 = mapTable.begin(); it2 != mapTable.end() && res; it2++) {
            for (it3 = mapTable.begin(); it3 != mapTable.end() && res; it3++) {
                string first = table[it1->second][0];
                string second = table[0][it2->second];
                string fS = table[it1->second][it2->second];
                string third = table[0][it3->second];
                string resultFirst = table[mapTable.find(fS)->second][it3->second];

                string sT = table[it2->second][it3->second];
                string resultSecond = table[it1->second][mapTable.find(sT)->second];
                cout << first << " " << second << " " << third << " " << resultFirst << " " << resultSecond << endl;
                if (resultFirst != resultSecond) {
                    res = false;
                    break;
                }
            }
        }
    }
    if (res) cout << "operation has associative property" << endl;
    else cout << "operation doesn't have associative property" << endl;
    int count = 0;
    for (int i = 1; i <= 5; i++) {
        count = 0;
        for (int j = 1; j <= 5; j++) {
            if (table[i][j] == table[0][j]) count++;
            else break;
        }
        if (count == 5) {
            cout << "left neutral element: " << table[i][0] << endl;
            break;
        }
    }
    if (count != 5) cout << "no left neutral element" << endl;
    for (int i = 1; i <= 5; i++) {
        count = 0;
        for (int j = 1; j <= 5; j++) {
            if (table[j][i] == table[j][0]) count++;
            else break;
        }
        if (count == 5) {
            cout << "right neutral element: " << table[0][i] << endl;
            break;
        }
    }
    if (count != 5) cout << "no right neutral element" << endl;
    vector<int> elements;

    for (it1 = mapTable.begin(); it1 != mapTable.end(); it1++) {

        elements.push_back(it1->second);

        //for (int i =0; i< elements.size(); i++) cout << table[0][elements.at(i)] << endl;
        //cout << endl;
    }

    for (int i=1; i<=4; i++) permutRepW(mapTable, elements, i);
}