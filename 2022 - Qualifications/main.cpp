//
//  main.cpp
//  hashcode_2022
//
//  Created by Yu Cheuk Hei on 25/2/2022.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

struct Contributor
{
    string name;
    int num_skills;
    
    int available = 0;
    
    map<string, int> skills;
};

struct Project
{
    string name;
    int num_days;
    int score;
    int best_before;
    int num_roles;
    
    vector<string> roles_ordered;
    map<string, int> roles;
};

struct Solve
{
    string name;
    int num_roles;
    
    vector<string> people;
};

int numContributors;
int numProjects;
vector<Contributor> contributors;
vector<Project> projects;
vector<Solve> res;


void parseInputFile(int testCase = 0) {
    vector< vector<string> > fileNames{ {"a.txt", "output_a.txt"},
                                        {"b.txt", "output_b.txt"},
                                        {"c.txt", "output_c.txt"},
                                        {"d.txt", "output_d.txt"},
                                        {"e.txt", "output_e.txt"},
                                        {"f.txt", "output_f.txt"}
    };
    
    
    ifstream ifs(fileNames[testCase][0]);
    
    if (!ifs) return;
    
    ifs >> numContributors >> numProjects;
    
    for (int i = 0; i < numContributors; ++i) {
        Contributor c;
        
        string temp_num_skills;
        ifs >> c.name >> temp_num_skills;
        
        c.num_skills = stoi(temp_num_skills);
        
        string temp_skill_name;
        string temp_skill_lvl;
        for (int j = 0; j < c.num_skills; ++j) {
            ifs >> temp_skill_name >> temp_skill_lvl;
            c.skills[temp_skill_name] = stoi(temp_skill_lvl);
        }
        
        contributors.push_back(c);
    }
    
    
    for (int i = 0; i < numProjects; ++i) {
        Project p;

        string temp_name;
        string temp_num_days;
        string temp_score;
        string temp_best_before;
        string temp_num_roles;
        ifs >> temp_name >> temp_num_days >> temp_score >> temp_best_before >> temp_num_roles;
        
        p.name = temp_name;
        p.num_days = stoi(temp_num_days);
        p.score = stoi(temp_score);
        p.best_before = stoi(temp_best_before);
        p.num_roles = stoi(temp_num_roles);
        
        string temp_role_name;
        string temp_role_lvl;
        for (int j = 0; j < p.num_roles; ++j) {
            ifs >> temp_role_name >> temp_role_lvl;
            p.roles_ordered.push_back(temp_role_name);
            
            // There might be duplicate roles in the same project
            // e.g. DataNextv9 PublicSpeaking-NET 1 and 4
            // We store the maximum role between them
            if (p.roles[temp_role_name] != 0) {
                p.roles[temp_role_name] = p.roles[temp_role_name] > stoi(temp_role_lvl) ? p.roles[temp_role_name] : stoi(temp_role_lvl);
            } else {
                p.roles[temp_role_name] = stoi(temp_role_lvl);
            }
        }
        
        projects.push_back(p);
    }
    
}

void outputToFile(int testCase = 0) {
    vector< vector<string> > fileNames{ {"a.txt", "output_a.txt"},
                                        {"b.txt", "output_b.txt"},
                                        {"c.txt", "output_c.txt"},
                                        {"d.txt", "output_d.txt"},
                                        {"e.txt", "output_e.txt"},
                                        {"f.txt", "output_f.txt"}
    };
    
    ofstream outputFile;
    outputFile.open(fileNames[testCase][1]);
    
    outputFile << res.size() << '\n';
    
    for (int i = 0; i < res.size(); ++i) {
        outputFile << res[i].name << '\n';
        for (int j = 0; j < res[i].people.size(); ++j) {
            outputFile << res[i].people[j] << ' ';
        }
        outputFile << '\n';
    }
}

// TODO
int calScore(vector<Contributor> clients, vector<string> res) {
    return -1;
}

int mode;

// IMPORTANT: Greedy Constraints
bool project_sorter(Project const& lhs, Project const& rhs) {
    
    switch (mode) {
            
        // Add Projects by descending order of scores
        default:
        case 0:
            return lhs.score > rhs.score;
            
        // Add Projects by increasing order of "best before" for the project
        case 1:
            return lhs.best_before < rhs.best_before;
        
        // Add Projects by increasing order of number of roles required by the project
        case 2:
            return lhs.num_roles < rhs.num_roles;
        
        // Add Projects by the number of days it takes to complete the project
        case 3:
            return lhs.num_days < rhs.num_days;
        
        // Add Projects by its score to role ratio
        case 4:
            return 1.0 * lhs.score / lhs.num_roles > 1.0 * rhs.score / rhs.num_roles;
            
    }

}

void solve(int threshold = 0, bool useMentor = false) {
    for (int i = 0; i < numProjects; ++i) {
        vector<int> occupied_t;
        
        bool skipProject = false;
        
        for (int j = 0; j < projects[i].num_roles; ++j) {
            string req_role = projects[i].roles_ordered[j];
            int req_lvl = projects[i].roles[req_role];
            
            bool found = false;
            int prev_k = -1;
            for (int k = 0; k < numContributors; ++k) {
                
                // If threshold = 0, ignores all projects that have passed the deadline
                // If 0 < threshold <= 1, allows projects to be at most projects[i].score * threshold dates late.
                if (contributors[k].available + projects[i].num_days > projects[i].best_before + projects[i].score * threshold) {
                    continue;
                }
                
                if (useMentor) {
                    // If found a contributor with req skill and skill lvl
                    // Possibly mentoring
                    if (contributors[k].skills.find(req_role) != contributors[k].skills.end()
                        && contributors[k].skills[req_role] >= (req_lvl - 1)
                        && find(occupied_t.begin(), occupied_t.end(), k) == occupied_t.end()) {

                        // Check if mentoring is available
                        // For simplicity, we only check if there are suitable mentors in the list of contributors that have been chosen earlier
                        // In other words, the first contributor must not be a mentor.
                        bool hasMentor = false;
                        for (int l = 0; l < (int)occupied_t.size() - 1; ++l) {
                            if (contributors[occupied_t[l]].skills.find(req_role) != contributors[occupied_t[l]].skills.end()
                                && contributors[occupied_t[l]].skills[req_role] >= req_lvl) {
                                
                                hasMentor = true;
                            }
                        }
                        
                        // Needs a mentor but there is no mentor, fail.
                        if (!hasMentor && contributors[k].skills[req_role] <= (req_lvl - 1)) {
                            continue;
                        }
                        
                        // No contributor for this role has been found before
                        if (prev_k == -1) {
                            found = true;
                            prev_k = k;
                            occupied_t.push_back(k);
                            
                        // A contributor for this role has already been found
                        // Check if we can replace the old contributor with the new one for improvement
                        } else if (contributors[k].available < contributors[prev_k].available) {
                            prev_k = k;
                            occupied_t.pop_back();
                            occupied_t.push_back(k);
                        }
                    }

                } else {
                    
                    //  If found a contributor with req skill and skill lvl
                    if (contributors[k].skills.find(req_role) != contributors[k].skills.end()
                        && contributors[k].skills[req_role] >= req_lvl
                        && find(occupied_t.begin(), occupied_t.end(), k) == occupied_t.end()) {
                        
                        found = true;
                        occupied_t.push_back(k);
                        break;
                    }
                }
            }
            
            // If there is one role in the project that we cannot find a suitable contributor, ignore this project
            if (!found) {
                skipProject = true;
                break;
            }
        }
        
        if (skipProject) {
            continue;
        }
        
        // Passed all checks, schedule this project
        // Add this to solution
        
        Solve s;
        s.name = projects[i].name;
        s.num_roles = projects[i].num_roles;
        
        int maxAvailable = 0;
        for (int j = 0; j < occupied_t.size(); ++j) {
            if (contributors[occupied_t[j]].available > maxAvailable) {
                maxAvailable = contributors[occupied_t[j]].available;
            }
        }
        
        for (int j = 0; j < occupied_t.size(); ++j) {
            s.people.push_back(contributors[occupied_t[j]].name);
            contributors[occupied_t[j]].available = maxAvailable + projects[i].num_days - 1;
        }
        
        res.push_back(s);
    }
}

int main()
{

    int testcase, threshold, useMentor;
    
    // IMPORTANT
    testcase = 2;
    mode = 0;
    threshold = 0;
    useMentor = false;
    
    parseInputFile(testcase);

    sort(projects.begin(), projects.end(), &project_sorter);
    
    solve(threshold, useMentor);
    
    outputToFile(testcase);
}

// A: 33, example
// B: 310676, mode = 2, threshold = 0, useMentor = true
// B: 310676, mode = 4, threshold = 0, useMentor = true
// C: 203315, mode = 0, threshold = 0, useMentor = false
// D: 50165, mode = 0, threshold = 0, useMentor = false
// E: 1637258, mode = 1, threshold = 0, useMentor = true
// F: 475082, mode = 1, threshold = 0 , useMentor = true
