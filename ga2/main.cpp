#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//Player data class
class Player{

    private:
        int number;
        int age;
        int minutes;
        bool isOnCourt; // if not on Court then on Bench
    public:
        static float REPLACE; // replace when the minutes played is or greater than 10% of age

        Player():number(-1), age(-1), minutes(-1), isOnCourt(false){};
        Player(int number, int age, int minutes, bool isOnCourt):number(number), age(age), minutes(minutes), isOnCourt(isOnCourt){};
        ~Player(){};
        int getNumber(){return number;}
        int getAge(){return age;}
        int getMinutes(){return minutes;}
        bool getIsOnCourt(){return isOnCourt;}
        float getReplaceTime(){ return age * REPLACE; }

        void setNumber(int n){number = n;}
        void setAge(int a){age = a;}
        void setMinutes(int m){minutes = m;}
        void setIsOnCourt(bool s){isOnCourt = s;}

        void print(){
            cout<<"*"<<endl;
            cout<<"no.: "<<number<<endl;
            cout<<"age: "<<age<<endl;
            cout<<"mins: "<<minutes<<endl;
        }
};

float Player::REPLACE = .1;


struct Node {
    Node* next = nullptr;
    Node* prev = nullptr;
    Player player;
};

class DoublyLinkedList{
    private:
        Node* head;
        Node* tail;
    public:
        DoublyLinkedList( int numberOfPlayers, bool isOnCourt);
        ~DoublyLinkedList();

        // bool pushHead(Player player);
        Node* getHead(){return head;}
        Node* getTail(){return tail;}

        bool pushBack(Player player);
        Node*  pop();
        void print();
        int length();
        void merge(DoublyLinkedList other);

        //Sort goes here

        //Input output goes here

};

DoublyLinkedList::DoublyLinkedList( int numberOfPlayers, bool isOnCourt){
    /**
     * @params: 
     * 
     * int number of players
     * bool isOnCourt, is this player on court or bench
     * 
     * */
    head = nullptr;
    int randomAge = 0;
    int randomNumber =0;
    int minutesPlayedInitial = 0;
    srand(static_cast <unsigned int> (time(0)));

    head =  nullptr;
    tail = nullptr;

    Node* indexNode = new Node();

    for(int i = 0;i <numberOfPlayers;i++){
        randomAge = rand() % 80 +1;
        randomNumber = rand() % 100 +1;
        
        Player player(randomNumber, randomAge, minutesPlayedInitial, isOnCourt);
        pushBack(player);
    }
}

DoublyLinkedList::~DoublyLinkedList(){
    delete head;
    delete tail;
}


bool DoublyLinkedList::pushBack(Player player){
    /**
     * Push the new element to the end of the list
     * @return bool whether the operation is successful or not
    */
    Node* newNode = new Node();
    newNode->player = player;

    if(tail == nullptr){
        head = new Node();
        tail = new Node();

        head->next = newNode;
        tail->prev = newNode;
    } else {
        Node* temp = tail->prev;
        
        temp->next = newNode;
        newNode->next = tail;
        newNode->prev = temp;
        tail->prev = newNode;
    }
    return true;
}

Node* DoublyLinkedList::pop(){
    /**
     * Returns the first element and remove it from the list
     * @returns Node* or nullptr if list is empty
    */
    if(head->next==nullptr){
        return nullptr;
    } else if(head->next == tail->prev){
            Node* temp = head->next;
            head->next =nullptr;
            tail->prev = nullptr;
            return temp;    
    }

    Node* temp =  head->next;


    head->next = temp->next;
    
    return temp; 
}

void DoublyLinkedList::print(){
/**
 * Start from the head to the tail
 * print the player
 * 
*/
    Node* index = head->next;
    if(index!=nullptr){
        while(index!=tail){
            index->player.print();
            index = index->next;
        }
    }
}

int DoublyLinkedList::length(){
    Node* index = head->next;
    int length =0;

    if(index!=nullptr){
        while(index!=tail){
            length ++;
            index = index->next;
        }
    }

    return length;
}

void DoublyLinkedList::merge(DoublyLinkedList other){
    Node* index = other.getHead()->next;
    if(index!=nullptr){
        while(index!=other.getTail()){
            pushBack(index->player);
            index = index->next;
        }
    }
}


void game(int quarters = 4, float quarter_time = 12){
    //Create 5 players on court
    DoublyLinkedList courtPlayers(5, true);

    //Create 7 players on the bench
    DoublyLinkedList benchPlayers(7, false);

    //create a merged list
    DoublyLinkedList merged = courtPlayers;

    merged.merge(benchPlayers);

    merged.print();

    cout<<"Total players "<<merged.length()<<endl;

}

int main(int argc, char *argv[]){

    game();

    return 0;
}