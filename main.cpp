#include <iostream>
#include "candidate.h"
#include "job.h"

using namespace std;

int main()
{
    Candidate c;

    c.id = 1;
    c.name = "Inaya";
    c.yearsExperience = 2;
    c.education = 2;

    c.skills[0] = "cpp";
    c.skills[1] = "python";
    c.skills[2] = "git";
    c.skillCount = 3;

    Job j;

    j.id = 2001;
    j.title = "AI Developer";
    j.minYears = 1;
    j.minEducation = 2;

    j.requiredSkills[0] = "python";
    j.requiredSkills[1] = "ml";
    j.requiredSkillCount = 2;

    cout << "Candidate Name: " << c.name << endl;
    cout << "Skills:" << endl;

    for (int i = 0; i < c.skillCount; i++)
    {
        cout << c.skills[i] << endl;
    }

    cout << "Job Title: " << j.title << endl;
    cout << "Required Skills:" << endl;

    for (int i = 0; i < j.requiredSkillCount; i++)
    {
        cout << j.requiredSkills[i] << endl;
    }

    return 0;
}