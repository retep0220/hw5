//
//  main.cpp
//  HW5
//
//  Created by 王吉朗 on 2023/5/14.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "istream"
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class Sentence {
public:
    unordered_map<string, int> srored;
};

vector<string> tokenizer (string str) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

bool isCapital (char ch) {
    if(ch >= 'A' && ch <= 'Z') {
        return true;
    }
    else return false;
}

struct IsNotAlpha {
    bool operator()(char c) {
        return !std::isalpha(static_cast<unsigned char>(c));
    }
};

int main (int argv, char* args[]) {
    ifstream corpusFile(args[1]);
    
    string line;
    vector<Sentence> AllSentence;
    while (getline(corpusFile,line)) {
        
        vector<string> tempstr;
        tempstr = tokenizer(line);
        for (string &str : tempstr) {
            str.erase(remove_if(str.begin(), str.end(), IsNotAlpha()),str.end()); //delete all nonalphabet
            for (char &ch : str) {
                if (isCapital(ch)) {
                    ch = tolower(ch);
                }
            }
            //upper to lower
        }
        Sentence tempsen;
        static int sentnum = 1;
        for (string &str : tempstr) {
            tempsen.srored[str] = sentnum;
        }
        AllSentence.push_back(tempsen);
        sentnum++;
    }
    
    /*for (Sentence &tempsen : AllSentence) {
        for (auto it = tempsen.srored.begin(); it != tempsen.srored.end(); it++) {
            cout << it->first << endl;
        }
    }*/
    
    vector<string> keywords;
    ifstream queryFile(args[2]);
    
    string query;
    while (getline(queryFile,query)) {
        keywords = tokenizer(query);
        for (auto &str : keywords) {
            for (char &ch : str) {
                if (isCapital(ch)) {
                    ch = tolower(ch);
                }
            }
        }
        //upper to lower
        set<int> ids;
        for (auto &sent : AllSentence) {
            bool isMatch = true;
            for (string &key : keywords) {
                if (sent.srored.find(key) == sent.srored.end()) {
                    isMatch = false;
                    break;
                }
            }
            if (isMatch) {
                ids.insert(sent.srored[keywords[0]]);
            }
        }
        
        if (ids.empty()) {
            cout << -1 << endl;
        }
        else{
            for (auto &id : ids) {
                cout << id << " ";
            }
            cout << endl;
        }
        ids.clear();
    }
    
    
}
