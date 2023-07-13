/*********************************************************************************
* Lukas Licon, llicon
* 2023 Winter CSE101 PA#8
* WordFrequency.cpp
* 03/12/2023
* Implemention file of RBT Dictionary ADT
*********************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {

    Dictionary dict;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    size_t begin, end, len;
    string line;
    string token = "";
    ifstream in;
    ofstream out;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        exit(EXIT_FAILURE);
    }
    in.open(argv[1]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }
    out.open(argv[2]);
    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }
        while (getline(in, line)) {
            len = line.length();
            begin = min(line.find_first_not_of(delim, 0), len);
            end = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end - begin);

            while (token != "") {
                transform(token.begin(), token.end(), token.begin(), ::tolower);

                if (dict.contains(token))
                    dict.setValue(token, dict.getValue(token)+1);
                else
                    dict.setValue(token, 1);
                begin = min(line.find_first_not_of(delim, end+1), len);
                end = min(line.find_first_of(delim, begin), len);
                token = line.substr(begin, end-begin);
            }
        }
    out << dict << endl;
    in.close();
    out.close();
    return 0;
}
