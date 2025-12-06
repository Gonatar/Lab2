#include "FileProcessor.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <vector>
#include <string>

using namespace std;

bool isSentenceEnd(char ch, const string& content, size_t pos) {
    if (ch == '.' || ch == '!' || ch == '?') {
        size_t nextPos = pos + 1;
        while (nextPos < content.length() && isspace(content[nextPos])) {
            nextPos++;
        }
        
        if (nextPos >= content.length()) {
            return true;
        }
        
        char nextChar = content[nextPos];
        if (isupper(nextChar)) {
            return true;
        }

        return false;
    }
    return false;
}

string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

void FileProcessor::processFileWithoutCommas() {
    const char* filename = "text.txt";
    ifstream file(filename);
    
    if (!file.is_open()) {
        throw WorkerException("Cannot open file text.txt for reading. Make sure the file exists.");
    }

    file.seekg(0, ios::end);
    if (file.tellg() == 0) {
        file.close();
        throw WorkerException("File text.txt is empty");
    }
    file.seekg(0, ios::beg);
    
    cout << "\n=== Processing file: " << filename << " ===" << endl;
    cout << "Displaying sentences without commas:" << endl;
    cout << "=====================================" << endl;
    
    string content;
    string line;
    while (getline(file, line)) {
        content += line + " ";
    }
    file.close();
    
    vector<string> sentences;
    vector<bool> hasComma;
    string currentSentence;
    bool inQuotes = false;
    bool currentHasComma = false;
    
    for (size_t i = 0; i < content.length(); i++) {
        char ch = content[i];
        
        if (ch == '"' || ch == '\'') {
            inQuotes = !inQuotes;
        }
        
        if (ch == ',' && !inQuotes) {
            currentHasComma = true;
        }
        
        currentSentence += ch;
        
        if (!inQuotes && isSentenceEnd(ch, content, i)) {
            sentences.push_back(currentSentence);
            hasComma.push_back(currentHasComma);
            
            currentSentence.clear();
            currentHasComma = false;
        }
    }
    
    if (!currentSentence.empty()) {
        sentences.push_back(currentSentence);
        hasComma.push_back(currentHasComma);
    }
    
    int displayedCount = 0;
    for (size_t i = 0; i < sentences.size(); i++) {
        if (!hasComma[i]) {
            string trimmed = trim(sentences[i]);
            
            if (!trimmed.empty()) {
                cout << (displayedCount + 1) << ". " << trimmed << endl;
                displayedCount++;
            }
        }
    }
    
    cout << "\n=== Statistics ===" << endl;
    cout << "Total sentences in file: " << sentences.size() << endl;
    cout << "Sentences without commas: " << displayedCount << endl;
    cout << "Sentences with commas: " << (sentences.size() - displayedCount) << endl;
    
    if (displayedCount == 0) {
        cout << "No sentences without commas found in the file." << endl;
    }
    
}