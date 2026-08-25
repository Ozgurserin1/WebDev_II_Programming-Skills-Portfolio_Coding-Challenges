#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Store both parts of one joke
struct Joke {
    string setup;
    string punchline;
};

int main() {
    // Open the joke file and create a list
    ifstream inFile("randomJokes.txt");
    vector<Joke> jokes;

    if (!inFile.is_open()) {
        cout << "The jokes file could not be opened." << endl;
        return 1;
    }

    // Read each joke and split it at the question mark
    string line;
    while (getline(inFile, line)) {
        string::size_type questionMark = line.find('?');

        if (questionMark != string::npos && questionMark + 1 < line.length()) {
            Joke joke;
            joke.setup = line.substr(0, questionMark + 1);
            joke.punchline = line.substr(questionMark + 1);
            jokes.push_back(joke);
        }
    }
    inFile.close();

    // Stop if no valid jokes were found
    if (jokes.empty()) {
        cout << "No valid jokes were found in the file." << endl;
        return 1;
    }

    // Use the current time to change the random choice
    srand(static_cast<unsigned int>(time(nullptr)));
    string userInput;

    // Keep running until the user chooses to quit
    while (true) {
        cout << "Type 'Alexa, tell me a joke' or type 'quit':" << endl;
        getline(cin, userInput);

        if (userInput == "quit") {
            break;
        }

        if (userInput == "Alexa, tell me a joke") {
            // Choose and display one random joke
            int randomNumber = rand() % jokes.size();
            cout << jokes[randomNumber].setup << endl;
            cout << "Press Enter for the punchline." << endl;
            getline(cin, userInput);
            cout << jokes[randomNumber].punchline << endl << endl;
        } else {
            cout << "Please use the correct phrase." << endl << endl;
        }
    }

    cout << "Goodbye!" << endl;
    return 0;
}
