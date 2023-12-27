/*
 * Riddles chooses a random riddle from a text file and reads the user's answer before showing the correct answer.
 * 
 * John Strong
 */

# include <iostream>
# include <string>
# include <fstream>
# include <stdlib.h>
# include <set>

int main()
{
    srand(time(0));

    // Open text file. riddles.txt must contain a riddle on one line, the answer on the next, and a blank line in between these riddle-answer pairs.
    std::ifstream riddleFile;
    riddleFile.open("riddles.txt");

    std::cout << "Welcome to Riddles!" << '\n';

    std::string currentLine{}; // we use this to store the current line being read from the txt file
    
    // Count the number of lines in the txt file to determine the size of our array
    int lineCount{ 0 };
    for (lineCount; std::getline(riddleFile, currentLine); lineCount++);
    riddleFile.clear();
    riddleFile.seekg(0, riddleFile.beg);

    // Find the number of riddles/answers, and create an array for both.
    int riddleCount{ (lineCount - 2) / 3 };
    std::cout << "There are " << riddleCount << " riddles!" << '\n';
    std::string riddleArray[100]{};
    std::string answerArray[100]{};

    // Read the file to populate the riddle and answer arrays.
    if (riddleFile.is_open())
    {
        // Iteration number tracks line we are processing, and this value is used to determine which type of line it is.
        int iterationNumber{ 0 };
        int lineType{ 0 };
        int currentRiddle{ 0 };
        while (riddleFile)
        {
            std::getline(riddleFile, currentLine);
            iterationNumber++;
            lineType = iterationNumber % 3;
            switch (lineType)
            {
            case 0:
                currentRiddle++;
                break;
            case 1:
                riddleArray[currentRiddle] = currentLine;
                break;
            case 2:
                answerArray[currentRiddle] = currentLine;
                break;
            default:
                break;
            }
        }
    }

    int randomNum{ 0 };
    bool run{ true };
    char checker{};
    std::string answer{};

    do
    {
        std::cout << "Would you like a riddle? (enter y/n)" << '\n';
        std::cin >> checker;
        std::cin.ignore(1000, '\n');
        if (checker == 'y')
        {
            randomNum = rand() % riddleCount;
            std::cout << riddleArray[randomNum] << '\n';
            std::getline(std::cin, answer);
            std::cout << "Your answer: " << answer << '\n' << answerArray[randomNum] << '\n' << '\n';
        }
        else
        {
            std::cout << "Thanks for playing!";
            run = false;
        }
    } while (run);
    
    return 0;
}