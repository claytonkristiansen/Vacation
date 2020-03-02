#include <iostream>
#include <stdexcept>
#include "functions.h"
#include "provided.h"

template<typename T>
void PrintArray(T* arr, int length, std::ostream &stream)
{
    for(int i = 0; i < length; ++i)
    {
        stream << i << ": " << arr[i] << std::endl;
    }
}

int main()
{
    int prefs[MAX_NB_GAMES];
    int plan[366];
    std::string* titles = new std::string[MAX_NB_GAMES];
    std::cout << "Please enter the number of games and the duration: ";
    int numGames = 0;
    int duration = 0;
    std::cin >> numGames >> duration;
    if(numGames > MAX_NB_GAMES)
    {
        std::cout << "Invalid input.\n";
        // delete[] prefs;
        // delete[] plan;
        // delete[] titles;
        return 1;
    }
    if(duration < 1 || duration > 365)
    {
        std::cout << "Invalid input.\n";
        // delete[] prefs;
        // delete[] plan;
        // delete[] titles;
        return 1;
    }
    
    std::cout << "Please enter name of file with titles: ";
    char* titlesFile = new char[256];
    std::cin >> titlesFile;
    std::cout << "Please enter name of file with preferences: ";
    char* prefFile = new char[256];
    std::cin >> prefFile;
    std::cout << "Please enter name of file with plan: ";
    char* planFile = new char[256];
    std::cin >> planFile;
    int date = 0;
    try
    {
        readGameTitles(titlesFile, numGames, titles);
        readPrefs(prefFile, numGames, prefs);
        //PrintArray<int>(prefs, numGames, std::cout);
        readPlan(planFile, plan);
        //PrintArray<int>(plan, 366, std::cout);
        date = findBestVacation(duration, prefs, plan);
        std::cout << "Best start day is " << date << std::endl << "Games to be played:\n";
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        delete[] titles;
        delete[] titlesFile;
        delete[] prefFile;
        delete[] planFile;
        return 1;
        // delete[] prefs;
        // delete[] plan;
        // delete[] titles;
        // delete[] titlesFile;
        // delete[] prefFile;
        // delete[] planFile;
    }
    //prefs[98] = 5;
    printGamesPlayedInVacation(date, duration, plan, titles, numGames); 
    
    
    
    // for(int i = date; i < date + duration; ++i)
    // {
    //     std::cout << std::endl << titles[plan[i]];
    // }
    //std::cout << "\n\n" << prefs[98];

    // std::cout << prefs[98];


    delete[] titles;
    delete[] titlesFile;
    delete[] prefFile;
    delete[] planFile;



    return 0;
}       