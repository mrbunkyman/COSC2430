#include <iostream>
#include "ArgumentManager.h"
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

class Player{
    private:
        string name;
        int number;
        string position;
    public:
        Player();
        Player(string name, int number, string position);
        string getName(){return name;}
        int getNumber(){return number;}
        string getPosition(){return position;}
        bool operator==(const Player& other);
};

Player::Player():name(""), number(-1), position(""){}

Player::Player(string name, int number, string position):name(name), number(number), position(position){
}
bool Player::operator==(const Player& other){
    if(name == other.name && number == other.number && position == other.position){
        return true;
    } else{
        return false;
    }
}

struct Node {
    Node* next = nullptr;
    Player player;    
};

class LinkedList {
    
    private:
        Node* head;
        Node* tail;
        int length;    
    public:
        LinkedList();
        ~LinkedList();
        bool add(Player player);
        int search(string name);
        void print();
        void alphabet_sort();
        void print_commands();
};

LinkedList::LinkedList(){
    head = nullptr;
    tail = nullptr;
    length = 0;
}

LinkedList::~LinkedList(){
    delete head;
    length = 0;

}

bool LinkedList::add(Player player){
    Node* node = new Node;
    length++;
    node->player = player;
    
    if(head == nullptr){
        head = node;
        tail = node;
    } else {
        tail->next = node;
        tail = tail->next;
    }
    return true;
}

int LinkedList::search(string inputName){
    Node* node = head;
    int index = 0;
    while(node!=nullptr){
        //cout << "Check: " << node -> player.getName() << " Input name: " << inputName << " Index: " << index << endl;
        string check = node -> player.getName();
        //cout << endl << check << "  " << inputName;
        if(check.compare(inputName)==0){
            return index;
        }
        node = node->next;
        index++;
    }
    return -1;
}

void LinkedList::print(){
    Node* node = head;
    string name;
    int number;
    string position;
    while(node!=nullptr){
        name = node->player.getName();
        number = node->player.getNumber();
        position = node->player.getPosition();

        cout<<name<<"\t"<<number<<"\t"<<position<<endl;
        node = node->next;
    }
}

void LinkedList::alphabet_sort(){
    for(int i = 0; i < length; i++){
        Node *curr = head;
        for(int j = 0; j < length-1; j++){
            bool found = false;
            int count = 0;

            while((!found)&&(count < curr -> player.getName().length())&&(count < curr -> next -> player.getName().length())){
                
                char tempInit = curr -> player.getName().at(count);
                char nextInit = curr -> next -> player.getName().at(count);
                if(tempInit == nextInit){
                    count++;
                }
                else if(tempInit > nextInit){
                    //cout << curr -> player.getName() << " " << curr -> next -> player.getName() << endl;
                    //cout << tempInit << " " << nextInit << endl;
                    //cout << "found" << endl;
                    found = true;
                }
                else{
                    break;
                }
            }



            if(found){
                //cout << "test" << endl;
                Player temp = curr -> player;
                curr -> player = curr -> next -> player;
                curr -> next -> player = temp;
                curr = curr -> next;
            }
            else{
                curr = curr -> next;
            }
        }
    }

}

void print_commands();

void readFile(string filename, LinkedList &l){
    std::ifstream ifs(filename);
    std::string str;
    // getline(ifs, str);

    // if (str.empty())
    // {
    //     std::cout << "ERROR! Input file EMPTY!" << std::endl;
    //     return false;
    // }

    // int n =0;
    vector<int> splitPos;

    while (getline(ifs, str))
    {
        size_t found = str.find(',');
        splitPos.clear();
        while(found!=std::string::npos){
     
            splitPos.push_back(static_cast<int>(found));
            found = str.find(',', found+1);
        }
        str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);

        string name = str.substr(0, splitPos.at(0));
        
        int number = stoi(str.substr(splitPos.at(0) + 1, splitPos.at(1)));
        string position = str.substr(splitPos.at(1) + 1, str.length());

        l.add(Player(name, number, position));
    }
}

void readCommand(string fileName, string outFileName, LinkedList &l){
    std::ifstream ifs(fileName);
    std::ofstream ofs(outFileName);
    std::string str;
    while(getline(ifs, str)){
        str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
        ofs<<str<<": "<<l.search(str)<<endl;
    }
}

int main(int argc, char *argv[]){
    
    LinkedList l;
    ArgumentManager am(argc, argv);
    
    
    const string inputFile = am.get("input");
    const string commandFile = am.get("command");
    const string outputFile = am.get("output");
    /*
    const string inputFile = "/Users/alonsomunoz/Desktop/Group Assignment 1/input12.txt";
    const string commandFile = "/Users/alonsomunoz/Desktop/Group Assignment 1/command12.txt";
    const string outputFile = "/Users/alonsomunoz/Desktop/Group Assignment 1/output12.txt";
    */
    
    // Trying to see if it is sorting from before reading the file, after reading the file, the list gets sorted
    readFile(inputFile, l);
    l.alphabet_sort();
    //l.print();
    readCommand(commandFile, outputFile, l);
    
    return 0;
}
