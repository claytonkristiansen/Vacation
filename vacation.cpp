#include <iostream>
#include <stdexcept>
#include "functions.h"
#include "provided.h"

int main()
{
    int *prefs = new int[MAX_NB_GAMES];
    int *plan = new int[366];
    std::string* titles = new std::string[MAX_NB_GAMES];
    std::cout << "Please enter the number of games and the duration: ";
    int numGames = 0;
    int duration = 0;
    std::cin >> numGames >> duration;
    if(numGames > MAX_NB_GAMES)
    {
        std::cout << "Invalid Input";
        delete[] prefs;
        delete[] plan;
        delete[] titles;
        return 0;
    }
    
    std::cout << "\nPlease enter name of file with titles: ";
    char* titlesFile = new char[256];
    std::cin >> titlesFile;
    std::cout << "\nPlease enter name of file with preferences: ";
    char* prefFile = new char[256];
    std::cin >> prefFile;
    std::cout << "\nPlease enter name of file with plan: ";
    char* planFile = new char[256];
    std::cin >> planFile;
    try
    {
        readPrefs(prefFile, 100, prefs);
        readPlan(planFile, plan);
        readGameTitles(titlesFile, numGames, titles);
    
        int date = findBestVacation(7, prefs, plan);

        std::cout << "Best start day is " << date << std::endl << "Games to be played:";
        printGamesPlayedInVacation(date, duration, plan, titles, numGames);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    // for(int i = date; i < date + duration; ++i)
    // {
    //     std::cout << std::endl << titles[plan[i]];
    // }

    delete[] prefs;
    delete[] plan;
    delete[] titles;
    delete[] titlesFile;
    delete[] prefFile;
    delete[] planFile;



    return 0;
}   