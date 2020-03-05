//
// Created by alexis on 16.09.19.
//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int perm [2][7];
    int checksum=0;
    int sum=0;
    for (int i=0; i<7;i++) sum+=(i+1);
    cout << "Enter permutation of order 7" << endl;
    for (int i=0; i<2; i++){
        for (int j=0; j<7; j++){
            cin >> perm[i][j];
            if (perm[i][j] > 7){
                cout << "ERROR" ;
                return -1;
            }
            checksum+=perm[i][j];
        }
        if (checksum!=sum){
            cout << "ERROR" ;
            return -1;
        }
        checksum=0;
    }
    int element;
    cout << "Enter element" << endl;
    cin >> element;
    vector<int> orbit;
    for (int i=0; i<7; i++) {
        if (perm[0][i] == element) {
            orbit.push_back(perm[1][i]);
        }
    }
    for (;;){
        int i=0;
        for (; i<7; i++) {
            if (perm[0][i]==orbit.at(orbit.size()-1)){
                break;
            }
        }
        if (perm[1][i]!=element) orbit.push_back(perm[1][i]);
        else {
            orbit.push_back(element);
            break;
        }
    }
    for (int i=0; i<orbit.size(); i++) {
        cout << orbit.at(i) << " ";
    }
    orbit.clear();
}