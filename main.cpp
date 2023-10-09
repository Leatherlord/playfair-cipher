#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string alphabet = {'A', 'B', 'C', 'D', 'E',
                   'F', 'G', 'H', 'I', 'K',
                   'L', 'M', 'N', 'O', 'P',
                   'Q', 'R', 'S', 'T', 'U',
                   'V', 'W', 'X', 'Y', 'Z',
                   ' ', ',', '.', '?', '\''};

void format_key_word(string &s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] < 'A' || s[i] > 'Z' && s[i] < 'a' || s[i] > 'z')
        {
            s.erase(i, 1);
            i--;
        }
    }
    transform(s.begin(), s.end(), s.begin(), ::toupper);

    for (int i = 0; i < s.size(); i++)
    {
        if (i != 0 && s[i] == s[i - 1])
        {
            s.erase(i, 1);
            i--;
        }
    }
}

void format_string(string &s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if ((s[i] < 'A' || s[i] > 'Z') && (s[i] < 'a' || s[i] > 'z') &&
            s[i] != ' ' && s[i] != ',' && s[i] != '.' && s[i] != '?' && s[i] != '\'')
        {
            s.erase(i, 1);
            i--;
        }
    }
    transform(s.begin(), s.end(), s.begin(), ::toupper);

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == 'J')
        {
            s[i] = 'I';
        }
        if (i != 0 && (s[i] == s[i - 1]))
        {
            s.insert(i, "X");
            i++;
        }
    }
    if (s.size() % 2 == 1)
    {
        s.push_back('X');
    }
}

vector<string> split_into_bigrams(string &s)
{
    vector<string> bigrams;
    string current = "";
    for (auto c : s)
    {
        current.push_back(c);
        if (current.length() == 2)
        {
            bigrams.push_back(current);
            current = "";
        }
    }
    return bigrams;
}

string cipher_message(string &message, string &key_word)
{
    format_key_word(key_word);
    format_string(message);
    vector<string> bigrams = split_into_bigrams(message);
    string table;
    for (auto c : key_word)
    {
        if (table.find(c) == string::npos)
        {
            table.push_back(c);
        }
    }
    for (auto c : alphabet)
    {
        if (table.find(c) == string::npos)
        {
            table.push_back(c);
        }
    }

    vector<string> ciphered_bigrams;

    for (auto bigram : bigrams)
    {
        int first_pos = table.find(bigram[0]);
        int second_pos = table.find(bigram[1]);
        int first_row = first_pos / 5;
        int first_col = first_pos % 5;
        int second_row = second_pos / 5;
        int second_col = second_pos % 5;

        string ciphered_bigram = "";
        int alphabet_lines = alphabet.length() / 5;
        if (first_row == second_row)
        {
            int new_row = first_row;
            int new_first_column = first_col == 4 ? 0 : first_col + 1;
            int new_second_column = second_col == 4 ? 0 : second_col + 1;
            ciphered_bigram.push_back(table[new_row * 5 + new_first_column]);
            ciphered_bigram.push_back(table[new_row * 5 + new_second_column]);
            ciphered_bigrams.push_back(ciphered_bigram);

            continue;
        }
        if (first_col == second_col)
        {
            int new_col = first_col;
            int new_first_row = first_row == alphabet_lines - 1 ? 0 : first_row + 1;
            int new_second_row = second_row == alphabet_lines - 1 ? 0 : second_row + 1;
            ciphered_bigram.push_back(table[new_first_row * 5 + new_col]);
            ciphered_bigram.push_back(table[new_second_row * 5 + new_col]);
            ciphered_bigrams.push_back(ciphered_bigram);

            continue;
        }
        int new_first_col = second_col;
        int new_second_col = first_col;

        ciphered_bigram.push_back(table[first_row * 5 + new_first_col]);
        ciphered_bigram.push_back(table[second_row * 5 + new_second_col]);
        ciphered_bigrams.push_back(ciphered_bigram);
    }

    string ciphered_message;
    for (auto s : ciphered_bigrams)
    {
        ciphered_message += s;
    }

    return ciphered_message;
}

string decipher_message(string &message, string &key_word)
{
    format_key_word(key_word);
    vector<string> bigrams = split_into_bigrams(message);
    string table;
    for (auto c : key_word)
    {
        if (table.find(c) == string::npos)
        {
            table.push_back(c);
        }
    }
    for (auto c : alphabet)
    {
        if (table.find(c) == string::npos)
        {
            table.push_back(c);
        }
    }

    vector<string> deciphered_bigrams;

    for (auto bigram : bigrams)
    {
        int first_pos = table.find(bigram[0]);
        int second_pos = table.find(bigram[1]);
        int first_row = first_pos / 5;
        int first_col = first_pos % 5;
        int second_row = second_pos / 5;
        int second_col = second_pos % 5;

        string deciphered_bigram = "";
        int alphabet_lines = alphabet.length() / 5;
        if (first_row == second_row)
        {
            int new_row = first_row;
            int new_first_column = first_col == 0 ? 4 : first_col - 1;
            int new_second_column = second_col == 0 ? 4 : second_col - 1;
            deciphered_bigram.push_back(table[new_row * 5 + new_first_column]);
            deciphered_bigram.push_back(table[new_row * 5 + new_second_column]);
            deciphered_bigrams.push_back(deciphered_bigram);

            continue;
        }
        if (first_col == second_col)
        {
            int new_col = first_col;
            int new_first_row = first_row == 0 ? alphabet_lines - 1 : first_row - 1;
            int new_second_row = second_row == 0 ? alphabet_lines - 1 : second_row - 1;
            deciphered_bigram.push_back(table[new_first_row * 5 + new_col]);
            deciphered_bigram.push_back(table[new_second_row * 5 + new_col]);
            deciphered_bigrams.push_back(deciphered_bigram);

            continue;
        }
        int new_first_col = second_col;
        int new_second_col = first_col;

        deciphered_bigram.push_back(table[first_row * 5 + new_first_col]);
        deciphered_bigram.push_back(table[second_row * 5 + new_second_col]);
        deciphered_bigrams.push_back(deciphered_bigram);
    }

    string deciphered_message;
    for (auto s : deciphered_bigrams)
    {
        deciphered_message += s;
    }

    return deciphered_message;
}

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        cout << "Usage: ./application <flag> <FILENAME_READ> <FILENAME_WRITE> <KEYWORD>" << endl;
        cout << "Possible flags: (-c - cipher), (-d - decipher)" << endl;
        return 1;
    }

    string key_word(argv[4]);

    string file_read_name(argv[2]);
    ifstream file_read;
    file_read.open(file_read_name);

    string file_write_name(argv[3]);
    ofstream file_write;
    file_write.open(file_write_name);

    string flag(argv[1]);

    string message;

    if (flag == "-c")
    {
        while (getline(file_read, message))
        {
            file_write << cipher_message(message, key_word) << endl;
        }
    }
    else if (flag == "-d")
    {
        while (getline(file_read, message))
        {
            file_write << decipher_message(message, key_word) << endl;
        }
    }
    else
    {
        cout << "Unsupported flag: " << flag << endl;
        return 1;
    }
    return 0;
}
