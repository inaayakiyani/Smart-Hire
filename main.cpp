#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "candidate.h"
#include "job.h"
#include "scoring.h"
#include "dynamicarray.h"
#include "hashtable.h"
#include "heap.h"
#include "avl.h"
#include "bst.h"

using namespace std;

const int MAX_JOBS = 50;

int splitLine(string line, char separator, string parts[], int maxParts)
{
    int count = 0;
    string current = "";
    int length = line.length();

    for (int i = 0; i < length; i++)
    {
        if (line[i] == separator)
        {
            if (count < maxParts)
            {
                parts[count] = current;
                count++;
            }

            current = "";
        }
        else
        {
            current = current + line[i];
        }
    }

    if (count < maxParts)
    {
        parts[count] = current;
        count++;
    }

    return count;
}

bool loadCandidates(string filename, DynamicArray& list)
{
    ifstream file(filename);

    if (!file.is_open())
        return false;

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        string parts[5];
        int partCount = splitLine(line, '|', parts, 5);

        if (partCount < 5)
            continue;

        Candidate c;
        c.id = stoi(parts[0]);
        c.name = parts[1];
        c.yearsExperience = stoi(parts[3]);
        c.education = stoi(parts[4]);

        string skillParts[MAX_CANDIDATE_SKILLS];
        int skillTotal = splitLine(parts[2], ',', skillParts, MAX_CANDIDATE_SKILLS);

        for (int i = 0; i < skillTotal; i++)
        {
            c.skills[i] = skillParts[i];
            c.skillCount++;
        }

        list.add(c);
    }

    return true;
}

int loadJobs(string filename, Job jobs[], int maxJobs)
{
    ifstream file(filename);

    if (!file.is_open())
        return -1;

    int jobTotal = 0;
    string line;

    while (getline(file, line))
    {
        if (jobTotal >= maxJobs)
            break;

        if (line.empty())
            continue;

        string parts[5];
        int partCount = splitLine(line, '|', parts, 5);

        if (partCount < 5)
            continue;

        Job j;
        j.id = stoi(parts[0]);
        j.title = parts[1];
        j.minYears = stoi(parts[3]);
        j.minEducation = stoi(parts[4]);

        string skillParts[MAX_JOB_SKILLS];
        int skillTotal = splitLine(parts[2], ',', skillParts, MAX_JOB_SKILLS);

        for (int i = 0; i < skillTotal; i++)
        {
            j.requiredSkills[i] = skillParts[i];
            j.requiredSkillCount++;
        }

        jobs[jobTotal] = j;
        jobTotal++;
    }

    return jobTotal;
}

int readInt()
{
    int value;
    cin >> value;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        return -1;
    }

    return value;
}

void printBanner()
{
    cout << "==========================================" << endl;
    cout << "    SMARTHIRE: Candidate Ranking System   " << endl;
    cout << "==========================================" << endl;
}

void printLine()
{
    cout << "+-------+------------------+-------+-----+----------------------------+" << endl;
}

void printTableHeader()
{
    printLine();
    cout << "| " << left << setw(5) << "ID"
         << " | " << setw(16) << "Name"
         << " | " << setw(5) << "Years"
         << " | " << setw(3) << "Edu"
         << " | " << setw(26) << "Skills" << " |" << endl;
    printLine();
}

void printCandidate(Candidate c)
{
    string skillText = "";

    for (int i = 0; i < c.skillCount; i++)
    {
        if (i > 0)
            skillText = skillText + ", ";

        skillText = skillText + c.skills[i];
    }

    cout << "| " << left << setw(5) << c.id
         << " | " << setw(16) << c.name
         << " | " << setw(5) << c.yearsExperience
         << " | " << setw(3) << c.education
         << " | " << setw(26) << skillText << " |" << endl;
}

void printJobs(Job jobs[], int jobCount)
{
    for (int i = 0; i < jobCount; i++)
    {
        cout << jobs[i].id << " | " << jobs[i].title << endl;
    }
}

void rankForJob(DynamicArray& candidates, HashTable& skillIndex, Job& job, int topK)
{
    int n = candidates.getSize();
    bool* shortlisted = new bool[n];
    int* found = new int[n];

    for (int i = 0; i < n; i++)
    {
        shortlisted[i] = false;
    }

    for (int i = 0; i < job.requiredSkillCount; i++)
    {
        int count = skillIndex.search(job.requiredSkills[i], found);

        for (int k = 0; k < count; k++)
        {
            shortlisted[found[k]] = true;
        }
    }

    MaxHeap heap;

    for (int i = 0; i < n; i++)
    {
        if (shortlisted[i])
        {
            Candidate c = candidates.get(i);
            int score = calculateScore(c, job);
            heap.insert(c, score);
        }
    }

    cout << "Shortlisted: " << heap.getSize() << " candidates" << endl;

    int rank = 1;
    RankedCandidate top;

    printTableHeader();

    while (rank <= topK)
    {
        if (!heap.extractMax(top))
            break;

        cout << "Rank " << rank << " | Score " << top.score << endl;
        printCandidate(top.candidate);
        printLine();
        rank++;
    }

    delete[] shortlisted;
    delete[] found;
}

void compareHeights()
{
    BST bst;
    AVL avl;

    for (int i = 1; i <= 20; i++)
    {
        Candidate c;
        c.id = i;
        c.yearsExperience = i;
        bst.insert(c);
        avl.insert(c);
    }

    cout << "Inserted experience 1 to 20 in ascending order" << endl;
    cout << "BST height: " << bst.height() << endl;
    cout << "AVL height: " << avl.height() << endl;
}

int main()
{
    DynamicArray candidates;
    Job jobs[MAX_JOBS];
    HashTable skillIndex;
    AVL avl;

    if (!loadCandidates("data.txt", candidates))
    {
        cout << "Could not open data.txt" << endl;
        return 1;
    }

    int jobCount = loadJobs("jobs.txt", jobs, MAX_JOBS);

    if (jobCount < 0)
    {
        cout << "Could not open jobs.txt" << endl;
        return 1;
    }

    for (int i = 0; i < candidates.getSize(); i++)
    {
        Candidate c = candidates.get(i);
        avl.insert(c);

        for (int k = 0; k < c.skillCount; k++)
        {
            skillIndex.insert(c.skills[k], i);
        }
    }

    int choice = -1;

    while (choice != 0)
    {
        cout << endl;
        printBanner();
        cout << "  1. List all candidates" << endl;
        cout << "  2. Rank candidates for a job" << endl;
        cout << "  3. Search candidates by skill" << endl;
        cout << "  4. Candidates in an experience range" << endl;
        cout << "  5. BST vs AVL height" << endl;
        cout << "  0. Exit" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Choice: ";

        choice = readInt();

        if (choice == 1)
        {
            printTableHeader();

            for (int i = 0; i < candidates.getSize(); i++)
            {
                printCandidate(candidates.get(i));
            }

            printLine();
        }
        else if (choice == 2)
        {
            printJobs(jobs, jobCount);
            cout << "Job id: ";
            int jobId = readInt();

            int jobIndex = -1;

            for (int i = 0; i < jobCount; i++)
            {
                if (jobs[i].id == jobId)
                    jobIndex = i;
            }

            if (jobIndex == -1)
            {
                cout << "Job not found" << endl;
            }
            else
            {
                cout << "How many top candidates: ";
                int topK = readInt();

                if (topK < 1)
                    topK = 1;

                rankForJob(candidates, skillIndex, jobs[jobIndex], topK);
            }
        }
        else if (choice == 3)
        {
            cout << "Skill: ";
            string skill;
            cin >> skill;

            int* found = new int[candidates.getSize()];
            int count = skillIndex.search(skill, found);

            if (count == 0)
            {
                cout << "No candidates have this skill" << endl;
            }
            else
            {
                printTableHeader();

                for (int i = 0; i < count; i++)
                {
                    printCandidate(candidates.get(found[i]));
                }

                printLine();
            }

            delete[] found;
        }
        else if (choice == 4)
        {
            cout << "Min years: ";
            int minYears = readInt();
            cout << "Max years: ";
            int maxYears = readInt();

            if (minYears > maxYears)
                cout << "Min cannot be bigger than max" << endl;
            else
                avl.range(minYears, maxYears);
        }
        else if (choice == 5)
        {
            compareHeights();
        }
    }

    return 0;
}