#include<iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "dict.h"
#include "linkedlist.h"
#include "wordStack.h"
using namespace std;

class NotePad{
private:
    Dict dict;
    Text text;
    string suggestion;
    string misspelled;
    WordStack w_stack;

    void loadDictionary(){
        ifstream file("dictionary.txt");
        if (file.is_open())
        {
            string line;
            while (getline(file, line)){
                dict.insert(line);
            }
            file.close();
        }
        //cout<<"Dictionary Loaded.\n";
    }

    void generateSuggestion(const string& misspelledWord){
        suggestion = "";

        // Method 1 : Letter Substitution
        for(int i=0;i<misspelledWord.length();++i){
            string temp = misspelledWord;
            for (char c = 'a'; c <= 'z'; ++c){
                if(misspelledWord[i] != c){
                    temp[i] = c;
                    if (dict.find(dict.root, temp)){
                        suggestion = temp;
                        if (suggestion.empty()) {
                            suggestion = "No Suggestion Found for this misspelled word.";  // Suggest the original word if no suggestion was found
                        }
                        return;
                    }
                }
                
            }
        }

        // Method 2 : Letter Deletion
        for (int i = 0; i < misspelledWord.length(); ++i){
            string temp = misspelledWord;
            temp.erase(i, 1);
            if (dict.find(dict.root, temp)){
                suggestion = temp;
                if (suggestion.empty()) {
                    suggestion = "No Suggestion Found for this misspelled word.";  // Suggest the original word if no suggestion was found
                }
                return;
            }
        }

        // Method 3 : Letter Insertion
        for(int i=0;i<=misspelledWord.length();i++){
            for (char c = 'a'; c <= 'z'; ++c){
                string temp = misspelledWord;
                temp.insert(temp.begin()+i, c);
                if (dict.find(dict.root, temp)){
                    suggestion = temp;
                    if (suggestion.empty()) {
                        suggestion = "No Suggestion Found for this misspelled word.";  // Suggest the original word if no suggestion was found
                    }
                    return;
                }
            }
        }

        // Method 4 : Letter Reversal
        for(int i=0; i<misspelledWord.length();i++){
            string temp = misspelledWord;
            swap(temp[i], temp[i + 1]);
            
            if (dict.find(dict.root, temp)){
                suggestion = temp;
                if (suggestion.empty()) {
                    suggestion = "No Suggestion Found for this misspelled word.";  // Suggest the original word if no suggestion was found
                }
                return;
            }
        }
    }

    void displayText(){
        cout << "\x1B[2J\x1B[H"; 
        cout<<"--NotePad App--\n";
        cout<<"-----------------------------------------------\n";
        text.display();
        cout<< w_stack.getWord(); 
    }

public:
    NotePad(){
        loadDictionary();
        displayText();
        suggestion = "";
        misspelled = "";
    }

    void run(){
        char letter;
        while (true){
            letter = _getch();
            if(letter == 27){ // ESC to quit
                cout<<"\nWant to Save your file before closing(y to save otherwise exit)?";
                char ch;
                cin>>ch;
                if(ch == 'y' || ch=='Y'){
                    saveToFile();
                }
                text.clear();
                w_stack.clear();
                dict.clear();
                exit(1);
            }
            else if (letter == 8){ // backspace clear one letter at a time
                if (!w_stack.isEmpty()){
                    w_stack.pop();
                }
                else if(!text.isempty()){
                    string lastWord = text.getLastWord();
                    text.deleteLastWord();
                    w_stack.clear();
                    for (char c : lastWord) {
                        w_stack.push(c);
                    }
                    
                }
                
            }

            else if (letter == ' ' || letter == '\n'){
                string currentWord = w_stack.getWord();
                if(currentWord.length() > 0){
                    if(!dict.find(dict.root , currentWord)){
                        misspelled = currentWord;
                        generateSuggestion(misspelled);
                        cout<<"\n\nYou misspelled the word \""<<suggestion<<"\" as \""<<misspelled<<"\". Want to accept suggestion(y to accept otherwise reject)?";
                        char ch;
                        cin>>ch;
                        if (ch == 'y' || ch == 'Y'){
                            text.insert(suggestion);
                            misspelled = "";
                            suggestion = "";
                        }
                        else{
                            text.insert(currentWord);
                            misspelled = "";
                            suggestion = "";
                        }
                    }
                    else{
                        text.insert(currentWord);
                        misspelled = "";
                    }
                    
                    w_stack.clear();
                }
                if(letter == '\n'){
                    text.insert("\n");
                }
            }
            else if(letter == 19){
                saveToFile();
            }
            else if(letter == 12){
                loadFromFile();
            }
            else{
                w_stack.push(letter);
            }

            displayText();
        }
    }

    void saveToFile(){
        cout<<"\nEnter File Name : ";
        string fileName;
        cin >> fileName;
        cin.ignore();
        ofstream file(fileName+".txt");
        if (file.is_open()){
            file << text.getText() << endl;
            file.close();
            cout << "\nText Saved in File.\n";
        }
        else{
            cout<<"\nError : Unable to open file.\n";
        }
    }

    void loadFromFile(){
        cout << "\nEnter File Name : ";
        string fileName;
        cin >> fileName;
        cin.ignore();
        ifstream file(fileName + ".txt");
        if (file.is_open())
        {
            text.clear();
            string word;
            while (file >> word){
                text.insert(word);
            }
            file.close();
            cout << "\nText Loaded from File.\n";
            displayText();
        }
        else
        {
            cout << "\nError : Unable to open file.\n";
        }
    }

    void displayDict(){
        dict.display(dict.root);
    }
};

int main(){
    NotePad np;
    np.run();
    return 0;

}

