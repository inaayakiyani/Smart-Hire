#pragma once

#include "candidate.h"
#include "job.h"

inline int calculateScore(Candidate& c, Job& j)
{
    int matched = 0;

    for (int i = 0; i < j.requiredSkillCount; i++)
    {
        for (int k = 0; k < c.skillCount; k++)
        {
            if (j.requiredSkills[i] == c.skills[k])
            {
                matched++;
                break;
            }
        }
    }

    int skillScore = 60;

    if (j.requiredSkillCount > 0)
        skillScore = 60 * matched / j.requiredSkillCount;

    int experienceScore = 25;

    if (j.minYears > 0)
    {
        if (c.yearsExperience < j.minYears)
            experienceScore = 25 * c.yearsExperience / j.minYears;
    }

    int educationScore = 0;

    if (c.education >= j.minEducation)
        educationScore = 15;

    return skillScore + experienceScore + educationScore;
}