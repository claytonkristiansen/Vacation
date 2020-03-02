#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "functions.h"

using std::ifstream;
using std::string;
using std::getline;
using std::cout;
using std::endl;
using std::runtime_error;

//Declared extern in functions.h


//Skips the specified number of entries. Entries are determined by the const DELIMITERS array set in funcitons.h
void StreamEntrySkip(std::ifstream& stream, int numEntries)
{
    if(stream.eof())
    {
        return;
    }
    const char DELIMITERS[] = "\n ,";
    stream >> std::noskipws;
    stream.clear();
    for(int i = 0; i < numEntries; ++i)
    {
        char extracted = 1;
        bool wordFlag = false;
        while(!wordFlag)
        {
            stream.get(extracted);
            if(extracted == EOF)
            {
                return;
            }
            for(int k = 0; k < 3; ++k)
            {
                if(extracted == DELIMITERS[k])
                {
                    wordFlag = true;
                    break;
                }
            }
        }
        
    }
    stream >> std::skipws;
}

int findBestVacation(int duration, int prefs[], int plan[])
{
    int mostFun = 0;
    int startDate = 0;
    if(duration > 365 || duration < 1)
    {
        throw(std::invalid_argument(""));
    }
    for(int i = 1; i <= 365 - duration + 1; ++i)
    {
        int val = computeFunLevel(i, duration, prefs, plan);
        if(val > mostFun)
        {
            mostFun = val;  
            startDate = i;
        }
    }
    return startDate;
}

int computeFunLevel(int start, int duration, int prefs[], int plan[])
{
    int end = start + duration - 1;
    // try
    // {
        if(end > 365)
        {
            throw(std::invalid_argument(""));
        }
    // }
    // catch(const std::invalid_argument& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
    int sum = 0;
    for(int i = start; i <= end; ++i)
    {
        sum += prefs[plan[i]];
    }
    return sum;
}

void readPlan(std::string fileName, int plan[])
{
    // try
    // {
        ifstream inFile(fileName);
        if(inFile.is_open())
        {
            //cout << "Opening file " << fileName << "...\n";
        }
        else
        {
            throw(runtime_error("Invalid plan file."));
        }
        for(int i = 1; i <= 365 && !inFile.eof(); ++i)
        {
            int index = 0;
            inFile >> index;
            if(inFile.fail())
            {
                StreamEntrySkip(inFile, 2);
            }
            else if(index > 0 && index <= 365)
            {
                inFile >> plan[index];
                if(inFile.fail())
                {
                    StreamEntrySkip(inFile, 1);
                }
            }
        }
        //PrintArray<int>(plan, 366, cout);
    // }
    // catch(runtime_error &e)
    // {
    //     //cout << "Failed to open file " << fileName << "\n";
    //     return;
    // }
}

void readPrefs(std::string fileName, int ngames, int prefs[])
{
    ifstream inFile(fileName);
    if(!inFile.is_open()) 
    {
        throw(runtime_error("Invalid preference file."));
    }

    for(int i = 0; i < ngames; i++) 
    {
        prefs[i] = 0;
    }

    int index = 0;
    int rating = 0;
    while(!inFile.eof())
    {
        inFile >> index;
        inFile >> rating;
        if(inFile.fail())
        {
            std::string garbagio = "";
            std::getline(inFile, garbagio);
        }
        else if(index >= 0 && index < ngames)
        {
            if(rating > 0 && rating <= 5)
            {
                prefs[index] = rating;
            }
        }
    }
}

