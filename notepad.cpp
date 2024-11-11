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
    string currentWord;
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

    void displayText(){
        system("cls");
        cout<<"--NotePad App--\n";
        cout<<"Misspelled : "<<misspelled<<endl;
        cout<<"Suggestion : "<<suggestion<<endl;
        cout<<"-----------------------------------------------\n";
        text.display();
        cout<<currentWord;
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
            if(letter == 27){
                break;
            }
            else if (letter == 8){ // backspace clear one letter at a time
                if (!currentWord.empty()){
                    currentWord = currentWord.substr(0,currentWord.length()-1);
                    w_stack.pop();
                }
                else if(!text.isempty()){
                    currentWord = text.getLastWord();
                    text.deleteLastWord();
                    w_stack.clear();
                    for (char c : currentWord) {
                        w_stack.push(c);
                    }
                    
                }
                
            }
            else if (letter == ' ' || letter == '\n'){
                if(currentWord.length() > 0){
                    if(!dict.find(dict.root , currentWord)){
                        misspelled = currentWord;
                        w_stack.clear();
                    }
                    else{
                        text.insert(currentWord);
                        currentWord = "";
                        w_stack.clear();
                    }
                }
            }
            else if(letter == 19){
                saveToFile();
            }
            else if(letter == 12){
                loadFromFile();
            }
            else{
                currentWord += letter;
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

