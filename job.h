#pragma once
#include <iostream>
#include <string>
using namespace std;
const int MAX_JOB_SKILLS = 10;
class Job {
public:
    int id = 0;
    string title;
    string requiredSkills[MAX_JOB_SKILLS];
    int requiredSkillCount = 0;
    int minYears = 0;
    int minEducation = 0;
};