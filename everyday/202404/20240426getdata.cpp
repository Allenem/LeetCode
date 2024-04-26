#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<vector<pair<string, vector<int>>>> readInputFromFile(const string& filename) {
    vector<vector<pair<string, vector<int>>>> testCases;


    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return testCases;
    }

    string line1, line2;
    while (getline(inputFile, line1) && getline(inputFile, line2)) {
        // exclude the [ and ]
        line1 = line1.substr(1, line1.size() - 2);
        line2 = line2.substr(1, line2.size() - 2);      
        // cout << "line1: " << line1 << endl;
        // cout << "line2: " << line2 << endl;

        vector<string> args1;
        vector<vector<int>> args2;

        // read line1 and split it by comma, then store it in args1
        stringstream ss(line1);
        string arg1;
        while (getline(ss, arg1, ',')) {
            args1.push_back(arg1.substr(1, arg1.size() - 2));
        }

        // read line2 and split it by comma, then store it in args2
        stringstream ss2(line2);
        char ch;
        int num;
        while (ss2 >> ch) {
            if (ch == '[') {
                vector<int> innerVec;
                while (ss2 >> ch && ch != ']') {
                    if (isdigit(ch)) {
                        ss2.putback(ch);
                        ss2 >> num;
                        innerVec.push_back(num);
                    }
                }
                args2.push_back(innerVec);
            }
        }

        vector<pair<string, vector<int>>> testCase;
        for (int i = 0; i < args1.size(); i++) {
            testCase.push_back({args1[i], args2[i]});
        }

        testCases.push_back(testCase);
            
    }

    inputFile.close();

    return testCases;
}

// int main() {
//     vector<vector<pair<string, vector<int>>>> testCases = readInputFromFile("20240426.txt");

//     // Printing the read data
//     for (int i = 0; i < testCases.size(); i++) {
//         cout << "Test case " << i + 1 << endl;
//         for (int j = 0; j < testCases[i].size(); j++) {
//             cout << testCases[i][j].first << " ";
//             for (int k = 0; k < testCases[i][j].second.size(); k++) {
//                 cout << testCases[i][j].second[k] << " ";
//             }
//             cout << endl;
//         }
//     }

//     return 0;
// }
