#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

class Word{
public:
    string word;
    Word *next;

    Word(const string& w) : word(w), next(NULL) {}
};

class Text{
public:
    Word* head;
    Word* tail;
    int size;

    Text(){
        head = NULL;
        tail = NULL;
    }

    void insert(const string& word){
        Word* newWord = new Word(word);
        if(tail){
            tail->next = newWord;
            tail = newWord;
        }
        else{
            head = tail = newWord;
        }
    }

    void deleteLastWord(){
        if (!head){
            return;
        }
        if(head == tail){
            delete head;
            head = tail = NULL;
        }
        else{
            Word *temp = head;
            while (temp->next != tail)
            {
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = NULL;
        }
    }

    void display(){
        Word *temp = head;
        while (temp)
        {
            cout << temp->word << " ";
            temp = temp->next;
        }
    }

    void clear(){
        while (head)
        {
            Word *temp = head;
            head = head->next;
            delete temp;
        }
        tail = NULL;
    }

    string getText(){
        string text;
        Word *temp = head;
        while (temp)
        {
            text += temp->word + " ";
            temp = temp->next;
        }
        return text;
    }

    string getLastWord(){
        return tail->word;
    }

    bool isempty(){
        return head == NULL;
    }
};


#endif