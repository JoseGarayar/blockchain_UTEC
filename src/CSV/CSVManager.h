#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class CSVManager {
private:
    ifstream file;
public:

    void openFile(const string& filePath) {
        file.open(filePath);
        if (!file) {
            throw "File does not exist.";
        }
        if (!file.is_open()) {
            throw "Failed to open the file";
        }
    }

    bool isFileOpen() {
        return file.is_open();
    }

    vector<string> splitString(const string& str, char delimeter) {
        vector<string> tokens;
        stringstream ss(str);
        string token;

        while (getline(ss, token, delimeter)) {
            tokens.push_back(token);
        }
        
        return tokens;
    }

    vector<vector<string>> readFile(const string& filePath) {
        openFile(filePath);
        string line;
        vector<vector<string>> rows;
        
        while (getline(file, line)) {
            vector<string> row = splitString(line, ',');
            rows.push_back(row);
        }
        
        return rows;
    }

    

};

