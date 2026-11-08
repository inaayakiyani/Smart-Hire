#pragma once
#include<iostream>
#include <string>
using namespace std;
const int MAX_CANDIDATE_SKILLS = 10;
class Candidate {
public:
    int id = 0;
    std::string name;
    std::string skills[MAX_CANDIDATE_SKILLS];
    int skillCount = 0;
    int yearsExperience = 0;
    int education = 0;
};