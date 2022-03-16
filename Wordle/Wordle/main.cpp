#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>
#include <map>
#define BACKGROUND(color, text) "\033[3;42;" << static_cast<int>(color) << "m" << text << "\033[0m"

using namespace std;

fstream word_file;

string text_line;
string saved_word;
string player_guess;
string play_again;

vector<string> text_lines;

int total_lines = 0;
int toal_guesses = 6;
constexpr int word_lengt = 5;

bool keep_playing = true;

enum class BackgroundColor : int
{
    Red = 41,
    Green = 42,
    Yellow = 43,
    BrightRed = 101,
    BrightGreen = 102,
    BrightYellow = 103,
    BrightBlack = 100
};

void load_word()
{
    word_file.open("WordleWords.txt", ios::in);
    srand(time(0));

    if (word_file.is_open())
    {
        while (getline(word_file, text_line))
        {
            total_lines++;
            text_lines.push_back(text_line);
        }
        word_file.close();
    }
    else
        cout << "ERROR! File could not open" << endl;

    int random_number = rand() % total_lines;
    saved_word = text_lines[random_number];
}

bool guess_word()
{
    cin >> player_guess;
    for (auto& c : player_guess) c = toupper(c);
    if (player_guess == saved_word)
    { 
        return true;
    }
    else
        return false;
}

void guess_check()
{
    map<char, int> saved_word_data;
    
    for (char c : saved_word)
    {
        saved_word_data[c]++;
    }

    for (int i = 0; i < saved_word.length(); i++)
    {
        char player_guess_char;
        char saved_word_char;
        player_guess_char = player_guess[i];
        saved_word_char = saved_word[i];

        if (player_guess_char == saved_word_char)
        {
            saved_word_data[player_guess_char]--;
        }
    }

    for (int i = 0; i < saved_word.length(); i++) 
    {
        char player_guess_char = player_guess[i];
        char saved_word_char = saved_word[i];

        if (player_guess_char == saved_word_char) // TODO. Check if the same char is in the same array slot.
        {
            cout << BACKGROUND(BackgroundColor::Green, player_guess_char);
        }
        else if (saved_word_data[player_guess_char] > 0)
        {
            cout << BACKGROUND(BackgroundColor::Yellow, player_guess_char);
            saved_word_data[player_guess_char]--;
        }
        else
        {
            cout << BACKGROUND(BackgroundColor::BrightBlack, player_guess_char);
        }
    }
    cout << endl;
}

void exit_game_or_play_again()
{
    cout << "Play agin?: Y/N" << endl;
    cin >> play_again;
    for (auto& c : play_again) c = toupper(c);
    if (play_again != "Y" || "N")
    {
        if (play_again == "Y")
        {
            keep_playing = true;
        }
        else if (play_again == "N")
        {
            cout << "Quitting Game" << endl;
            keep_playing = false;
        }
    }
}

int main()
{
    while (keep_playing)
    {
        cout << "Guess the five letter word you have: " << toal_guesses << " tries" << endl;
        load_word();
        cout << "The word is: " << BACKGROUND(BackgroundColor::BrightBlack, saved_word) << endl;

        while (toal_guesses > 0)
        {
            if (guess_word())
            {
                cout << "You win! the word was: " << BACKGROUND(BackgroundColor::Green, saved_word) << endl;
                break;
            }
            else
            {
                if (player_guess.length() != saved_word.length())
                {
                    std::cout << "Guess must consist of 5 characters. Guess again" << endl;
                    continue;
                }
                toal_guesses--;
                if (toal_guesses > 0)
                {
                    cout << "Guess again you have: " << toal_guesses << " tries left" << endl;
                }
                else
                {
                    cout << "You have " << toal_guesses << " guesses: YOU LOSE!!!" << endl;
                    cout << "The word was: " << saved_word;
                    break;
                }
            }
            guess_check();
        }
        exit_game_or_play_again();
    }
    return 0;
}