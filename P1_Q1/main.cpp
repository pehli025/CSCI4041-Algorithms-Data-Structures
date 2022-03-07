#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

class node{
  public:
    node(string, int);
    node *next;
    int data;
    string name;
};

node::node(string n, int x) {
    name = n;
    data = x;
    next = NULL;
}

class queue {
  public:
    queue();
    void Insert(string, int);
    string Extract_Max();
    bool isEmpty() { return (head == NULL); }
  private:
    node* head; 
};

queue::queue() { head = NULL; }

void queue::Insert(string n, int x) {
    node* temp = new node(n,x);
    if(head == NULL || x > head->data){
        temp->next = head;
        head = temp;
    } else {
        node* h = head;
        while(h->next != NULL && h->next->data >= x){
            h = h->next;
        }
        temp->next = h->next;
        h->next = temp;
    }
}

string queue::Extract_Max(){
	if (!isEmpty()){
		node *temp = head;
		head = head->next;
		return temp->name; //return name
	}
}

int main(int argc, const char * argv[]){
    queue *bankQueue = new queue();
    int inInt = 0, count = 0;
    string inName = "";
    string delim = "";
    ifstream in;
    in.open(argv[1]);

    if(in.fail()){ // file checking
        cout << "ERROR: FILE " << argv[1] << " COULD NOT OPEN" << endl;
        return 1; 
    } 
    while (in >> inName >> delim >> inInt){
        bankQueue->Insert(inName, inInt);
        ++count;
    }

    ofstream out;
    out.open("output.txt");
    for(int i = 0; i < count; i++){
        out << bankQueue->Extract_Max() << " ";
    }
    out << "\n";
    out.close();
}