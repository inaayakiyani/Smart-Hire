#include <iostream>
#include "candidate.h"
#include "job.h"
#include "scoring.h"

using namespace std;

int main()
{
    Job j;
    j.id = 2004;
    j.title = "Backend Developer";
    j.requiredSkills[0] = "java";
    j.requiredSkills[1] = "sql";
    j.requiredSkills[2] = "git";
    j.requiredSkillCount = 3;
    j.minYears = 3;
    j.minEducation = 2;

    Candidate hira;
    hira.skills[0] = "java";
    hira.skills[1] = "python";
    hira.skills[2] = "sql";
    hira.skills[3] = "git";
    hira.skillCount = 4;
    hira.yearsExperience = 6;
    hira.education = 3;

    Candidate fatima;
    fatima.skills[0] = "cpp";
    fatima.skills[1] = "java";
    fatima.skills[2] = "git";
    fatima.skillCount = 3;
    fatima.yearsExperience = 0;
    fatima.education = 2;

    Candidate usman;
    usman.skills[0] = "html";
    usman.skills[1] = "css";
    usman.skills[2] = "javascript";
    usman.skills[3] = "react";
    usman.skillCount = 4;
    usman.yearsExperience = 1;
    usman.education = 2;

    Job open;

    cout << calculateScore(hira, j) << endl;
    cout << calculateScore(fatima, j) << endl;
    cout << calculateScore(usman, j) << endl;
    cout << calculateScore(usman, open) << endl;

    g.remove(1, 2);
    g.inOrder();
    cout << g.height() << endl;
    return 0;
}