#include<iostream>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;
//data structure using class
class Node{
	int data;
	Node *rchild,*lchild;
public:
	friend class tree;
	Node(){
		data=0;
		lchild=rchild=NULL;
	}
};
class tree{
	Node *root;
	Node *makeTree();
	//traversal
	void inorder(Node *r);
	void preorder(Node *r);
	void postorder(Node *r);
	//iterative functions
	void itInorder(Node *r);
	void itPreorder(Node *r);
	void itPostorder(Node *r);
	//level order traversal
	void levelorder(Node *r);
	//delete tree
	void rec_Delete(Node *r);
	void it_delete(Node *r);
	//counting max height
	int count_height(Node *r);
	//counting leaf node
	int count_leaf(Node *r);
public:
	tree(){
		//constructor
		root=NULL;
	}
	void create(){
		//function to create a tree which returns root node
		root=makeTree();
	}
	void operator =(const tree t1);
	void traversal(int o);
	void delete_Tree();
	void max_height();
	void leaf_num();
	~tree(){
	}
};
Node *tree::makeTree(){
	//create a binary tree through recursive call
	Node *temp;
	temp=new Node;
	cout<<"\nEnter data:";
	cin>>temp->data;
	cout<<"\n\tDo you want to enter left child "<<temp->data<<" (y/n): ";
	char ch;
	cin>>ch;
	if(ch=='y'){
		temp->lchild=makeTree();
	}
	cout<<"\n\tDo you want to enter right child of "<<temp->data<<" (y/n): ";
	cin>>ch;
	if(ch=='y'){
		//appends right child to respective node
		temp->rchild=makeTree();
	}
	return temp;
}
void tree::delete_Tree(){
	int c;
	cout<<"\n1.Recursive delete\n2.iterative delete: ";
	cin>>c;
	switch(c){
	case 1:
		rec_Delete(root);
		break;
	case 2:
		it_delete(root);
		break;
	default:
		cout<<"\n Invalid choice !!!\n";
	}
	root=NULL;
}
void tree::traversal(int val){
	//calls appropriate function for traversal of tree
	if(!root){
		cout<<"\nTree is empty\n";
		return;
	}
	if(val==1){
		cout<<"\n-----inorder:-----\n";
		inorder(root);
		cout<<"\n---------------------\n";
	}
	else if(val==2){
		cout<<"\n-----Preorder:-----\n";
		preorder(root);
		cout<<"\n-------------------\n";
	}
	else if(val==3){
		cout<<"\n-----Post order:-----\n";
		postorder(root);
		cout<<"\n---------------------\n";
	}
	else if(val==4){
		cout<<"\n-----inorder:-----\n";
		itInorder(root);
		cout<<"\n---------------------\n";
	}
	else if(val==5){
		cout<<"\n-----pre order:-----\n";
		itPreorder(root);
		cout<<"\n---------------------\n";
	}
	else if(val==6){
		cout<<"\n-----post order:-----\n";
		itPostorder(root);
		cout<<"\n---------------------\n";
	}
	else if(val==7){
		cout<<"\n-----post order:-----\n";
		levelorder(root);
		cout<<"\n---------------------\n";
	}
	else{
		cout<<"\n-----Enter valid input!!!-----\n";
	}
}
void tree::inorder(Node *r){
	if(r){
		inorder(r->lchild);
		cout<<r->data<<" ";
		inorder(r->rchild);
	}
}
void tree::preorder(Node *r){
	if(r){
		cout<<r->data<<" ";
		preorder(r->lchild);
		preorder(r->rchild);
	}
}
void tree::postorder(Node *r){
	if(r){
		postorder(r->lchild);
		postorder(r->rchild);
		cout<<r->data<<" ";
	}
}
//iterative inorder function
void tree::itInorder(Node *r){
	stack<Node *> s;
	Node *curr;
	curr=r;
	while(1){
		while(curr){
			s.push(curr);
			curr=curr->lchild;
		}
		if(s.empty()){
			return;
		}
		curr=s.top();
		cout<<curr->data<<" ";
		s.pop();
		curr=curr->rchild;
	}
}
void tree::itPreorder(Node *r){
	stack<Node *> s;
	stack <Node *> v;
	Node *curr;
	curr=r;
	s.push(r);
	while(!s.empty()){
		curr=s.top();
		cout<<curr->data<<" ";
		s.pop();
		if(curr->rchild){
			s.push(curr->rchild);
		}
		if(curr->lchild){
			s.push(curr->lchild);
		}
	}
}
void tree::itPostorder(Node *r){
	stack<Node *> s;
	stack<Node *> val;
	Node *curr;
	curr=r;
	s.push(r);
	while(!s.empty()){
		curr=s.top();
		val.push(curr);
		s.pop();
		if(curr->lchild){
			s.push(curr->lchild);
		}
		if(curr->rchild){
			s.push(curr->rchild);
		}
	}
	while(!val.empty()){
		cout<<val.top()->data<<" ";
		val.pop();
	}
}
void tree::levelorder(Node *r){
	queue <Node *> q;
	Node *curr;
	curr=r;
	while(curr){
		cout<<curr->data<<" ";
		if(curr->lchild){
			q.push(curr->lchild);
		}
		if(curr->rchild){
			q.push(curr->rchild);
		}
		if(q.empty()){
			return ;
		}
		curr=q.front();
		q.pop();
	}
}
//delete tree by recursion
void tree::rec_Delete(Node *r){
	if(r){
		rec_Delete(r->lchild);
		rec_Delete(r->rchild);
		delete r;
	}
}
//delete tree by iteration
void tree::it_delete(Node *r){
	stack<Node *> s;
	stack<Node *> val;
	Node *curr;
	curr=r;
	s.push(r);
	while(!s.empty()){
		curr=s.top();
		val.push(curr);
		s.pop();
		if(curr->lchild){
			s.push(curr->lchild);
		}
		if(curr->rchild){
			s.push(curr->rchild);
		}
	}
	while(!s.empty()){
		delete s.top();
	}
}
//counting height of tree
void tree::max_height(){
	cout<<"Maximum height of the tree is: "<<count_height(root)<<endl;
}
int tree::count_height(Node *r){
    if (r == NULL)
        return 0;
    else {

        int lDepth = count_height(r->lchild);
        int rDepth = count_height(r->rchild);

        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}
//counting leaf nodes
void tree::leaf_num(){
	cout<<"\nNumber of leaf nodes: "<<count_leaf(root)<<endl;
}
int tree::count_leaf(Node *r){
    if(r == NULL)
        return 0;
    if(r->lchild == NULL && r->rchild == NULL)
        return 1;
    else
        return count_leaf(r->lchild)+ count_leaf(r->rchild);
}
//overloading '=' operator
void tree::operator =(const tree t2){
	this->root=t2.root;
}
int main(){
	tree t1,t2;     //object
	int choice;
	//Menu
	while(1){
		cout<<"\n\t--------------------";
		cout<<"\n\tEnter \n\t1.To create tree:\n\t2.For traversal\n\t3.delete tree\n\t4.copy tree\n\t5.Height of tree\n\t6.Number of leaf nodes : ";
		cin>>choice;
		if(choice==0){
			break;
		}
		else if(choice==1){
			t1.create();
		}
		else if(choice==2){
			int order;
			cout<<"\n\tEnter \n\t1.Inorder traversal\n\t2.Preorder Traversal\n\t3.Postorder Traversal:";
			cout<<"\n\t4.Iterative inorder \n\t5.Iterative preorder \n\t6.Iterative postoder \n\t7.Level order : ";
			cin>>order;
			t1.traversal(order);
		}
		else if(choice==3){
			t1.delete_Tree();
			cout<<"\n Tree deleted successfully\n";
		}
		else if(choice==4){
			t2=t1;
			cout<<"\nTree copied!!!\n";
		}
		else if(choice==5){
			t1.max_height();
		}
		else if(choice==6){
			t1.leaf_num();
		}
		else{
			cout<<"\n\t!!!Enter valid input!!!\n";
		}
	}

	cout<<"\n\t\t-----------Thank you----------";
return 0;
}
