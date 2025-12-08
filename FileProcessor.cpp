#include "FileProcessor.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

bool isSentenceEnd(char ch, const char* content, size_t pos, size_t length) {
    if (ch == '.' || ch == '!' || ch == '?') {
        size_t nextPos = pos + 1;
        
        while (nextPos < length && isspace(content[nextPos])) {
            nextPos++;
        }
        
        if (nextPos >= length) {
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

char* trim(const char* str) {
    if (!str) return nullptr;
    
    while (*str && isspace(*str)) {
        str++;
    }
    
    if (*str == '\0') {
        char* result = new char[1];
        result[0] = '\0';
        return result;
    }
    
    const char* end = str;
    while (*end) {
        end++;
    }
    end--;
    
    while (end > str && isspace(*end)) {
        end--;
    }
    
    size_t len = end - str + 1;
    char* result = new char[len + 1];
    
    strncpy(result, str, len);
    result[len] = '\0';
    
    return result;
}

void freeStringArray(char** array, int count) {
    if (!array) return;
    
    for (int i = 0; i < count; i++) {
        delete[] array[i];
    }
    delete[] array;
}

void FileProcessor::processFileWithoutCommas() {
    const char* filename = "text.txt";
    ifstream file(filename);
    
    if (!file.is_open()) {
        throw WorkerException("Cannot open file text.txt for reading. Make sure the file exists.");
    }

    file.seekg(0, ios::end);
    long fileSize = file.tellg();
    
    if (fileSize == 0) {
        file.close();
        throw WorkerException("File text.txt is empty");
    }
    
    file.seekg(0, ios::beg);
    
    char* content = new char[fileSize + 1];
    if (!content) {
        file.close();
        throw WorkerException("Memory allocation failed for file content");
    }
    
    file.read(content, fileSize);
    content[fileSize] = '\0';
    file.close();
    
    cout << "\n=== Processing file: " << filename << " ===" << endl;
    cout << "Displaying sentences without commas:" << endl;
    cout << "=====================================" << endl;
    
    int capacity = 100;
    int count = 0;
    
    char** sentences = new char*[capacity];
    if (!sentences) {
        delete[] content;
        throw WorkerException("Memory allocation failed for sentences array");
    }
    
    bool* hasComma = new bool[capacity];
    if (!hasComma) {
        delete[] content;
        delete[] sentences;
        throw WorkerException("Memory allocation failed for hasComma array");
    }
    
    for (int i = 0; i < capacity; i++) {
        sentences[i] = nullptr;
        hasComma[i] = false;
    }
    
    char* currentSentence = new char[fileSize + 1];
    int sentencePos = 0;
    bool inQuotes = false;
    bool currentHasComma = false;
    
    if (!currentSentence) {
        delete[] content;
        delete[] sentences;
        delete[] hasComma;
        throw WorkerException("Memory allocation failed for sentence buffer");
    }
    
    for (long i = 0; i < fileSize; i++) {
        char ch = content[i];
        
        if (ch == '"' || ch == '\'') {
            inQuotes = !inQuotes;
        }
        
        if (ch == ',' && !inQuotes) {
            currentHasComma = true;
        }
        
        currentSentence[sentencePos++] = ch;
        currentSentence[sentencePos] = '\0';
        
        if (!inQuotes && isSentenceEnd(ch, content, i, fileSize)) {
            if (count >= capacity) {
                capacity *= 2;
                
                char** newSentences = new char*[capacity];
                if (!newSentences) {
                    delete[] content;
                    freeStringArray(sentences, count);
                    delete[] hasComma;
                    delete[] currentSentence;
                    throw WorkerException("Memory expansion failed for sentences");
                }
                
                for (int j = 0; j < count; j++) {
                    newSentences[j] = sentences[j];
                }
                delete[] sentences;
                sentences = newSentences;
                
                bool* newHasComma = new bool[capacity];
                if (!newHasComma) {
                    delete[] content;
                    freeStringArray(sentences, count);
                    delete[] hasComma;
                    delete[] currentSentence;
                    throw WorkerException("Memory expansion failed for hasComma");
                }
                
                for (int j = 0; j < count; j++) {
                    newHasComma[j] = hasComma[j];
                }
                delete[] hasComma;
                hasComma = newHasComma;
                
                for (int j = count; j < capacity; j++) {
                    sentences[j] = nullptr;
                    hasComma[j] = false;
                }
            }
            
            sentences[count] = new char[sentencePos + 1];
            if (!sentences[count]) {
                delete[] content;
                freeStringArray(sentences, count);
                delete[] hasComma;
                delete[] currentSentence;
                throw WorkerException("Memory allocation failed for sentence copy");
            }
            strcpy(sentences[count], currentSentence);
            
            hasComma[count] = currentHasComma;
            count++;
            
            sentencePos = 0;
            currentSentence[0] = '\0';
            currentHasComma = false;
        }
    }
    
    if (sentencePos > 0) {
        if (count >= capacity) {
            capacity++;
            char** newSentences = new char*[capacity];
            bool* newHasComma = new bool[capacity];
            
            for (int j = 0; j < count; j++) {
                newSentences[j] = sentences[j];
                newHasComma[j] = hasComma[j];
            }
            
            delete[] sentences;
            delete[] hasComma;
            sentences = newSentences;
            hasComma = newHasComma;
            
            sentences[count] = nullptr;
            hasComma[count] = false;
        }
        
        sentences[count] = new char[sentencePos + 1];
        strcpy(sentences[count], currentSentence);
        hasComma[count] = currentHasComma;
        count++;
    }
    
    int displayedCount = 0;
    for (int i = 0; i < count; i++) {
        if (!hasComma[i]) {
            char* trimmed = trim(sentences[i]);
            
            if (trimmed && trimmed[0] != '\0') {
                cout << (displayedCount + 1) << ". " << trimmed << endl;
                displayedCount++;
            }
            
            delete[] trimmed;
        }
    }
    
    cout << "\n=== Statistics ===" << endl;
    cout << "Total sentences in file: " << count << endl;
    cout << "Sentences without commas: " << displayedCount << endl;
    cout << "Sentences with commas: " << (count - displayedCount) << endl;
    
    if (displayedCount == 0) {
        cout << "No sentences without commas found in the file." << endl;
    }
    
    delete[] content;
    delete[] currentSentence;
    delete[] hasComma;
    
    for (int i = 0; i < count; i++) {
        delete[] sentences[i];
    }
    delete[] sentences;
}