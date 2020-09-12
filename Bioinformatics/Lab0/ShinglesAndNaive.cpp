#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <cmath>
using namespace std;

bool compareStrings(const string & first, const string & second) {
    int hashFirst = hash<string>()(first);
    int hashSecond = hash<string>()(second);
    return (hashFirst == hashSecond);
}

void createShingles(string * proteins, int sizeProteins, int shingleSize, string** shingledProteins) {
    for (int i=0; i<sizeProteins; i++) {
        int sizeString = proteins[i].length();
        shingledProteins[i] = new string[sizeString-shingleSize];
        for (int j=0; j<sizeString-shingleSize; j++) {
            shingledProteins[i][j] = proteins[i].substr(j, shingleSize);
        }
    }
}

void createShingleHashes(string * proteins, int sizeProteins, int shingleSize, string** shingledProteins, int ** similarityMatrix) {
    for (int i=0; i<sizeProteins; i++) {
        similarityMatrix[i][i] = 1;
        for (int j=i+1; j<sizeProteins; j++) {
            float shSizeFirst = proteins[i].length() - shingleSize;
            float shSizeSecond = proteins[j].length() - shingleSize;
            int trueHashes = 0;
            for (int k = 0; k < shSizeFirst; k++) {
                for (int l = 0; l < shSizeSecond; l++) {
                    if (compareStrings(shingledProteins[i][k], shingledProteins[j][l])) {
                        trueHashes++;
                        break;
                    }
                }
            }
            float maxSize = 0;
            if (shSizeFirst > shSizeSecond) {
                maxSize = shSizeFirst;
            } else {
                maxSize = shSizeSecond;
            }

            similarityMatrix[i][j] = ceil(trueHashes / maxSize * 100);
        }
    }
}

void printTable(int sizeProteins, int ** similarityMatrix) {
    cout << "        " ;
    for (int i=0; i<sizeProteins; i++) {
        cout << i ;
        if (i>=100) {
            cout <<  " " ;
        } else if (i >=10) {
            cout <<  "  " ;
        } else {
            cout << "   " ;
        }
    }
    cout << endl;

    for (int i=0; i<sizeProteins; i++) {
        cout << "№" << i << "   " ;
        if (i>=100) {
            cout <<  " " ;
        } else if (i >=10) {
            cout <<  "  " ;
        } else {
            cout << "   " ;
        }
        for (int j=0; j<sizeProteins; j++) {
            cout << similarityMatrix[i][j] ;
            if (similarityMatrix[i][j] >=10) {
                cout <<  "  " ;
            } else {
                cout << "   " ;
            }
        }
        cout << endl;
    }
}


void shinglesAlgorithm(string * proteins, int sizeProteins) {
    int shingleSize = 30;
    string ** shingledProteins;
    shingledProteins = new string*[sizeProteins];

    createShingles(proteins, sizeProteins, shingleSize, shingledProteins);


    int ** similarityMatrix;
    similarityMatrix = new int*[sizeProteins];

    for (int i = 0; i < sizeProteins; i++) {
        similarityMatrix[i] = new int[sizeProteins];
    }

    for (int i = 0; i < sizeProteins; i++) {
        for (int j = 0; j < sizeProteins; j++) {
            similarityMatrix[i][j] = 0;
        }
    }

    createShingleHashes(proteins, sizeProteins, shingleSize, shingledProteins, similarityMatrix);

    printTable(sizeProteins, similarityMatrix);
    for (int i = 0; i < sizeProteins; i++) {
        delete [] similarityMatrix[i];
    }

    delete [] similarityMatrix;

    for (int i = 0; i < sizeProteins; i++) {
        delete [] shingledProteins[i];
    }

    delete [] shingledProteins;
}

int compareProteins(const string & firstProtein, const string & secondProtein) {
    int ** comparisonTable;
    comparisonTable = new int*[firstProtein.length()];
    for (int i=0; i<firstProtein.length(); i++) {
        comparisonTable[i] = new int[secondProtein.length()];
    }
    for (int i=0; i<firstProtein.length(); i++) {
        for (int j=0; j<secondProtein.length(); j++) {
            comparisonTable[i][j] = 0;
        }
    }

    for (int i=0; i<firstProtein.length(); i++) {
        int similar = 0;
        for (int j=0; j<secondProtein.length(); j++) {
            if (similar == 0 && firstProtein.at(i) == secondProtein.at(j)) {
                similar = 1;
            }
            if (i>0) {
                comparisonTable[i][j] = similar + comparisonTable[i - 1][j];
            } else {
                comparisonTable[i][j] = similar;
            }
        }
    }
    int answer = comparisonTable[firstProtein.length()-1][secondProtein.length()-1];
    for (int i=0; i<firstProtein.length(); i++) {
        delete [] comparisonTable[i];
    }
    delete [] comparisonTable;
    return answer;
}


void tableComparison(string * proteins, int proteinsSize) {
    int ** similarityMatrix;
    similarityMatrix = new int*[proteinsSize];

    for (int i = 0; i < proteinsSize; i++) {
        similarityMatrix[i] = new int[proteinsSize];
    }

    for (int i = 0; i < proteinsSize; i++) {
        for (int j = 0; j < proteinsSize; j++) {
            similarityMatrix[i][j] = 0;
        }
    }


    for (int i=0; i<proteinsSize; i++) {
        similarityMatrix[i][i]=1;
        for (int j=i+1; j<proteinsSize; j++) {
            int similarity = compareProteins(proteins[i], proteins[j]);
            float maxSize = 0;
            if (proteins[i].length() > proteins[j].length()) {
                maxSize = proteins[i].length();
            } else {
                maxSize = proteins[j].length();
            }
            similarityMatrix[i][j] = ceil(similarity / maxSize * 100);
        }
    }

    printTable(proteinsSize, similarityMatrix);
    for (int i = 0; i < proteinsSize; i++) {
        delete [] similarityMatrix[i];
    }

    delete [] similarityMatrix;
}


int main(int argc, char **argv) {

    string * protein;
    int n = 1000;

    protein = new string[n];

    if (argc < 2) {
        std::cerr << " Wrong format: " << argv[0] << " [infile] " << std::endl;
        return -1;
    }

    std::ifstream input(argv[1]);
    if (!input.good()) {
        std::cerr << "Error opening: " << argv[1] << " . You have failed." << std::endl;
        return -1;
    }
    std::string line, id, DNA_sequence;

    int stringSize = 0;

    while (std::getline(input, line)) {
        if (line.empty())
            continue;

        if (line[0] == '>') {
            if (DNA_sequence.size() != 0) {
                if (stringSize == 1000) {
                    cout << "Max proteins size is 1000" << endl;
                    break;
                }
                protein[stringSize] = DNA_sequence;
                stringSize++;
            }
            DNA_sequence.clear();
        } else {
            DNA_sequence += line;
        }
    }
    if (stringSize != 1000) {
        if (DNA_sequence.size() != 0) {
            protein[stringSize] = DNA_sequence;
            stringSize++;
        }
    }

    shinglesAlgorithm(protein, stringSize);
    tableComparison(protein, stringSize);
    delete [] protein;
}
