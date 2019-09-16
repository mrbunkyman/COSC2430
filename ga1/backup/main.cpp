#include <iostream>
#include "ArgumentManager.h"
#include <string>
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
        void swap(int a, int b);
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

int LinkedList::search(string name){
    Node* node = head;
    int index =-1;
    while(node!=nullptr){
        index++;
        if(node->player.getName() == name){
            return index;
        }
        node = node->next;
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

    Node* t = head;

}

void LinkedList::swap(int a, int b){
    
}


bool readFile(string filename, LinkedList &l){
    std::ifstream ifs(filename);
    std::string str;

    vector<int> splitPos;

    while (getline(ifs, str))
    {
        cout<<str<<endl;
        size_t found = str.find(',');
        splitPos.clear();
        while(found!=std::string::npos){
     
            splitPos.push_back(static_cast<int>(found));
            found = str.find(',', found+1);
        }

        string name = str.substr(0, splitPos.at(0));
        int number = stoi(str.substr(splitPos.at(0) + 1, splitPos.at(1)));
        string position = str.substr(splitPos.at(1) + 1, str.length());

        l.add(Player(name, number, position));
    }
}

void readCommand(string fileName, const LinkedList l){


}

int main(int argc, char *argv[]){

    ArgumentManager am(argc, argv);

    // string inputFile = am.get("input");
    // string outputFile = am.get("output");

    string inputFile = "input11.txt";
    string outputFile = "test_output.txt";
    string commandFile = "command1.txt";
    LinkedList l;

    cout<<"File name "<<inputFile<<endl<<endl;

    readFile(inputFile, l);
    
    cout<<"\n\n"<<endl;
    // l.print();

    int index = l.search("Thiago Silva");

    cout<<index+1<<endl;

    index = l.search("Marquinhos");

    cout<<index+1;

    return 0;

}