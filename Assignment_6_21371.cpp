#include <iostream>
using namespace std;
template <typename T>
class stack
{
    int max = 50;
    T arr[50];
    int top;

public:
    stack()
    {
        top = -1;
    }
    void push(T data)
    {
        top++;
        arr[top] = data;
    }
    T pop()
    {
        top--;
        return arr[top + 1];
    }
    bool isEmpty()
    {
        return (top == -1);
    }
};

template <typename T>
class queue
{
    int max = 50;
    T arr[50];
    int f;
    int r;

public:
    queue()
    {
        f = -1;
        r = -1;
    }
    void enqueue(T data)
    {
        if (r == -1)
        {
            r++;
            f++;
            arr[r] = data;
        }
        else
        {
            r++;
            arr[r] = data;
        }
    }
    T dequeue()
    {
        T data;
        if (f == r)
        {
            data = arr[r];
            r = -1;
            f = -1;
        }
        else
        {
            data = arr[f];
            f++;
        }
        return data;
    }
    bool isEmpty()
    {
        if (r == -1)
        {
            return true;
        }
        return false;
    }
};

class Node
{
    string landmark;
    Node *next;
    int visited_bit;
    int index;

public:
    Node()
    {
        landmark = "";
        next = NULL;
        visited_bit = 0;
        index = 0;
    }
    friend class Graph;
};

class Graph
{
    Node *GraphArr;
    int n;
    void creatgraph()
    {
        for (int i = 0; i < n; i++)
        {
            int choice;
            cout << "Enter landmarks connected to " << GraphArr[i].landmark << endl;
            while (true)
            {
                cout << "Enter 0 to exit\n Enter 1 to add landmark\n";
                cout << "Enter choice: ";
                cin >> choice;
                if (choice == 0)
                {
                    break;
                }
                else if (choice == 1)
                {
                    cout << "Select Landmark\n";
                    for (int j = 0; j < n; j++)
                    {
                        cout << j + 1 << " " << GraphArr[j].landmark << endl;
                    }
                    cout << "Enter choice for landmark: ";
                    cin >> choice;
                    if (choice < n + 1)
                    {
                        Node *t = new Node;
                        t->landmark = GraphArr[choice - 1].landmark;
                        t->index = GraphArr[choice - 1].index;
                        Node *temp = &GraphArr[i];
                        while (temp->next)
                        {
                            temp = temp->next;
                        }
                        temp->next = t;
                    }
                }
            }
        }
    }

    void BFS();
    void DFS();

public:
    Graph()
    {
        cout << "Enter number of landmarks: ";
        cin >> n;
        GraphArr = new Node[n];

        for (int i = 0; i < n; i++)
        {
            cout << "Enter landmark: ";
            cin >> GraphArr[i].landmark;
            GraphArr[i].index = i;
        }
        creatgraph();
    }
    void traversal(){
        int choice;
        cout<<"Enter 1 for BFS\n";
        cout<<"Enter 2 for DFS\n";
        cout<<"Enter choice: ";
        cin>>choice;
        if(choice == 1){
            BFS();
        }
        else if(choice == 2){
            DFS();
        }
    }
    void disply()
    {
        Node *temp;
        for (int i = 0; i < n; i++)
        {
            temp = &GraphArr[i];
            while (temp)
            {
                cout << temp->landmark << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

void Graph::BFS()
{
    Node *temp;
    queue<int> q;
    temp = &GraphArr[0];
    q.enqueue(0);
    cout << temp->landmark << " ";
    temp->visited_bit = 1;
    while (!q.isEmpty())
    {
        temp = &GraphArr[q.dequeue()];

        while (temp)
        {
            temp = temp->next;
            if (temp)
            {
                if (!GraphArr[temp->index].visited_bit)
                {
                    cout << temp->landmark << " ";
                    GraphArr[temp->index].visited_bit = 1;
                    q.enqueue(temp->index);
                }
            }
        }
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        GraphArr[i].visited_bit = 0;
    }
}

void Graph::DFS()
{
    stack<int> s;
    Node *temp = &GraphArr[0];
    s.push(0);
    while (!s.isEmpty())
    {
        temp = &GraphArr[s.pop()];
        if(!GraphArr[temp->index].visited_bit){
        cout << temp->landmark << " ";
        }
        GraphArr[temp->index].visited_bit = 1;
        while (temp)
        {
            temp = temp->next;
            if (temp)
            {

                if (!GraphArr[temp->index].visited_bit)
                {
                    s.push(temp->index);
                }
            }
        }
    }
}

int main()
{
    Graph G;
    cout<<"0 to exit\n";
    cout<<"1 for traversal\n";
    int c;
    while(true){
        cout<<"Enter choice:";
        cin>>c;
        if(c == 1){
            cout<<"--------------------------------------\n";
            G.traversal();
            cout<<"\n--------------------------------------\n";
        }
        else if(c == 0){
            break;
        }
    }
}
