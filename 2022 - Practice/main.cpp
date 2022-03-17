//
//  main.cpp
//  hashcode_2022
//
//  Created by Yu Cheuk Hei on 15/2/2022.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

map<string, int> weight;
vector<string> all;

struct Client
{
    int numLike;
    int numDislike;
    
    vector<string> like;
    vector<string> dislike;
};

vector<Client> parseInputFile(int testCase = 0) {
    vector< vector<string> > fileNames{ {"a.txt", "output_a.txt"},
                                        {"b.txt", "output_b.txt"},
                                        {"c.txt", "output_c.txt"},
                                        {"d.txt", "output_d.txt"},
                                        {"e.txt", "output_e.txt"}};
    
    vector<Client> clients;
    ifstream ifs(fileNames[testCase][0]);
    
    // rmb to check if file exists
    
    int numClients;
    ifs >> numClients;
    
    string str;
    for (int i = 0; i < numClients; ++i) {
        Client c;
        
        ifs >> str;
        c.numLike = stoi(str);
        
        for (int j = 0; j < c.numLike; ++j) {
            ifs >> str;
            c.like.push_back(str);
            
            // Update weight
            if (weight.find(str) == weight.end()) {
                weight[str] = 0;
            }
            weight[str] += 1;
        }
        
        ifs >> str;
        c.numDislike = stoi(str);
        
        for (int j = 0; j < c.numDislike; ++j) {
            ifs >> str;
            c.dislike.push_back(str);
            
            // Update weight
            if (weight.find(str) == weight.end()) {
                weight[str] = 0;
            }
            weight[str] -= 1;
        }
        
        clients.push_back(c);
    }
    
    return clients;
}

void outputToFile(vector<string> res, int testCase = 0) {
    vector< vector<string> > fileNames{ {"a.txt", "output_a.txt"},
                                        {"b.txt", "output_b.txt"},
                                        {"c.txt", "output_c.txt"},
                                        {"d.txt", "output_d.txt"},
                                        {"e.txt", "output_e.txt"}};
    
    ofstream outputFile;
    outputFile.open(fileNames[testCase][1]);
    
    outputFile << res.size() << ' ';
    
    for (int i = 0; i < res.size(); ++i) {
        outputFile << res[i] << ' ';
    }
}

int calScore(vector<Client> clients, vector<string> res) {
    int score = 0;
    for (int i = 0; i < clients.size(); ++i) {
        bool like = true;
        for (int j = 0; j < clients[i].numLike && like; ++j) {
            // Like Ingredient not found
            if (find(res.begin(), res.end(), clients[i].like[j]) == res.end()) {
                like = false;
            }
        }
        
        for (int j = 0; j < clients[i].numDislike && like; ++j) {
            // Dislike Ingredients found
            if (find(res.begin(), res.end(), clients[i].dislike[j]) != res.end()) {
                like = false;
            }
        }
        
        if (like) {
            ++score;
        }
    }
    
    return score;
}

vector<string> solve(int threshold) {
    vector<string> res;
    for ( const auto &pair : weight ) {
        // std::cout << pair.first << " " << pair.second << "\n";
        if (pair.second >= threshold) {
            res.push_back(pair.first);
        }
    }
    
    return res;
}

vector<string> randomRes() {
    vector<string> res;
    for (int i = 0; i < all.size(); ++i) {
        if (rand() % 2 == 1) {
            res.push_back(all[i]);
        }
    }
    
    return res;
}

vector<string> randomRes2(vector<string> res, int add = 5, int rmv = 5) {
    for (int i = 0; i < rmv; ++i) {
        int min = 0;
        int max = res.size();
        int index = min + (rand() % static_cast<int>(max - min));
        
        res.erase(res.begin() + index);
    }
    
    for (int i = 0; i < add; ++i) {
        bool added = false;
        while (!added) {
            int min = 0;
            int max = all.size();
            int index = min + (rand() % static_cast<int>(max - min + 1));
            
            

            if (find(res.begin(), res.end(), all[index]) == res.end()) {
                res.push_back(all[index]);
                added = true;
            }
        }
    }
    
    return res;
}

int main()
{
    int testCase = 4;
    vector<Client> clients = parseInputFile(testCase);
    
    for ( const auto &pair : weight ) {
        // std::cout << pair.first << " " << pair.second << "\n";
        all.push_back(pair.first);
    }
    
/*
    int maxScore = 0;
    int maxThreshold;
    
    vector<string> res;
    for (int i = -5; i <= 5; ++i) {
        res = solve(i);
        int currScore = calScore(clients, res);
        
        if (maxScore < currScore) {
            maxScore = currScore;
            maxThreshold = i;
        }
        
        cout << "Threshold " << i << ": " << currScore << endl;
        res.clear();
    }
    
    res = solve(maxThreshold);
    outputToFile(res, testCase);
    // cout << calScore(clients, res) << endl;
*/

/*
    int maxScore = 0;
    int maxElim;
    
    vector<string> res = solve(0);
    int size = res.size();
    for (int i = 0; i < size; ++i) {
        string temp = res[0];
        res.erase(res.begin() + 0);
        
        int currScore = calScore(clients, res);
        
        if (maxScore < currScore) {
            maxScore = currScore;
            maxElim = i;
        }
        
        cout << "Elim " << i << ", " << temp << ": " << currScore << endl;
        res.push_back(temp);
    }
    
    cout << "To be removed: " << res[maxElim] << endl;
    res.erase(res.begin() + maxElim);
    outputToFile(res, testCase);
*/

/*
    int maxScore = 0;
    string maxIngredient;
    
    vector<string> res = solve(0);
    for ( const auto &pair : weight ) {
        // std::cout << pair.first << " " << pair.second << "\n";
        if (pair.second < 0) {
            res.push_back(pair.first);
            
            int currScore = calScore(clients, res);
            
            if (maxScore < currScore) {
                maxScore = currScore;
                maxIngredient = pair.first;
            }
            
            cout << "Insert " << maxIngredient << ": " << currScore << endl;
            res.pop_back();
        }
    }
    
    res.push_back(maxIngredient);
    cout << calScore(clients, res) << endl;
    outputToFile(res, testCase);
*/

    int maxScore = 0;
    vector<string> maxRes;
    
    for (int i = 0; i < 1000; ++i) {
        vector<string> res = randomRes();
        int currScore = calScore(clients, res);
        
        if (maxScore < currScore) {
            maxScore = currScore;
            maxRes = res;
        }
        
        cout << "Score: " << currScore << endl;
        res.clear();
    }
    
    cout << calScore(clients, maxRes) << endl;
    outputToFile(maxRes, testCase);

/*
    int maxScore = 0;
    vector<string> maxRes;
    
    for (int i = 0; i < 10; ++i) {
        vector<string> res = solve(0);
        vector<string> res_t = randomRes2(res, 4, 4);
        int currScore = calScore(clients, res_t);
        
        if (maxScore < currScore) {
            maxScore = currScore;
            maxRes = res_t;
        }
        
        cout << "Score: " << currScore << endl;
        res_t.clear();
    }
    
    cout << calScore(clients, maxRes) << endl;
    outputToFile(maxRes, testCase);
 
*/
}




