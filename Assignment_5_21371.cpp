#include <iostream>
using namespace std;

class Node
{
    string key;
    string meaning;
    Node *next;
    Node()
    {
        key = "0";
        meaning = "0";
        next = NULL;
    }
    Node(string k, string m)
    {
        this->key = key;
        this->meaning = m;
        next = NULL;
    }
    friend class Dictionary;
};

class Dictionary
{
    Node *arr;
    int max;
    void insert(Node n);
    void removedata(string key);
    void find(string key);

public:
    Dictionary(int size)
    {
        arr = new Node[size];
        max = size;
    }
    int HashCode(string key);
    void insertdata();
    void delete_data();
    void search();
    void display();
};

int Dictionary::HashCode(string key)
{
    int code = 0;
    int len = key.length();
    // for (int i = 0; i < len; i++)
    // {
    //     code += key[i];
    // }
    // code %= this->max;
    code = key[len-1]%max;
    return code;
}

void Dictionary::insertdata()
{
    Node n;
    cout << "Enter key: ";
    cin>>n.key;
    cout << "Enter meaning: ";
    cin>>n.meaning;
    this->insert(n);
}

void Dictionary::delete_data()
{
    string key;
    cout << "Enter kye:";
    cin>>key;
    this->removedata(key);
}

void Dictionary::search()
{
    string key;
    cout << "Enter key : ";
   cin>>key;
    this->find(key);
}

void Dictionary::insert(Node n)
{   Node* newnode = new Node;
    newnode->key = n.key;
    newnode->meaning = n.meaning;
    int pos = HashCode(n.key);
    if (arr[pos].key == "0")
    {
        arr[pos] = n;
    }
    else
    {
        Node *c = &arr[pos];
        while (c->next)
        {
            c = c->next;
        }
        c->next = newnode;
    }
}

void Dictionary::removedata(string key)
{
    int pos = HashCode(key);
    Node *c = arr[pos].next;
    if (arr[pos].key == key)
    {
        if(arr[pos].next){
        arr[pos].key = arr[pos].next->key;
        arr[pos].meaning = arr[pos].next->meaning;
        delete c;
        }
        else{
            arr[pos].key = "0";
            arr[pos].meaning = "0";
        }
    }
    else
    {
        Node *c = &arr[pos];
        while (c->next)
        {
            if (c->next->key == key)
            {
                Node *temp = c->next;
                c->next = temp->next;
                delete temp;
                return;
            }
            else
            {
                c = c->next;
            }
        }
        cout << "No element is found\n";
    }
}

void Dictionary::find(string key)
{
    int pos = HashCode(key);

        Node *c = &arr[pos];
        while (c)
        {
            if (c->key == key)
            {
                cout << "Key: " << c->key << endl;
                cout << "Meaning: " << c->meaning << endl;
                return;
            }
            c = c->next;
        }
        cout<<"Not found\n";
}

void Dictionary::display(){
    Node* c;
    cout<<"--------------------------------------\n";
    for(int i = 0; i<max; i++){
        c = &arr[i];
        while(c){
            cout<<c->key<<" "<<c->meaning<<"  ||  ";
            c = c->next;
        }
        cout<<endl;
    }
    cout<<"--------------------------------------\n";

}

int main(){
    int size;
    cout<<"Enter size: ";
    cin>>size;
    Dictionary d(size);
    int choice;
    while(1){
        cout<<"Enter 0 to exit\n";
        cout<<"Enter 1 to insert data\n";
        cout<<"Enter 2 to search data\n";
        cout<<"Enter 3 to delete data\n";
        cout<<"Enter 4 to display complete data\n";
        cout<<"\nEnter choice: ";
        cin>>choice;
        if(choice == 0){
            break;
        }
        else if(choice == 1){
            d.insertdata();
        }
        else if(choice == 2){
            d.search();
        }
        else if(choice == 3){
            d.delete_data();
        }
        else if(choice == 4){
            d.display();
        }
    }

}