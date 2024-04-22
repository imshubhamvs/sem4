#include <iostream>
using namespace std;

class Node{
	int data;
	Node* left;
	Node* right;
	bool rthread;
	bool lthread;
public:
	Node(){
		data = 0;
		left = NULL;
		right = NULL;
		rthread = false;
		lthread = false;
	}
	friend class TBST;
};


class TBST{
	Node* root;
	void inorder();
	void preorder();
	void add_node(Node* n);
	void delete_TBST(Node* r);
	void delete_node(Node* par, Node* curr);
	void A(Node* par, Node* curr);
	void B(Node* par, Node* curr);
	void C(Node* par, Node* curr);
public:
	TBST(){
		this->root = NULL;
	}
	~TBST(){
		delete_TBST(root);
	}
	void make();
	void traversal(int c);
	void remove_node();
	void clear_tree(){
		delete_TBST(root);
	}
};

//create a new node
void TBST::make(){
	cout<<"Enter data: ";
	int d;
	cin>>d;
	Node* newnode;
	newnode = new Node;
	newnode->data = d;
	this->add_node(newnode);
	
}

//add node n to Threaded binary search tree
void TBST::add_node(Node* n){
	if(!this->root){
		root = n;
		root->lthread = true;
		root->rthread = true;
	}
	else{
		Node* temp = root;
		while(1){
			if(temp->data > n->data){
				if(temp->lthread){
					//adding left node to temp
					n->right = temp;
					n->left = temp->left;
					temp->left = n;
					n->rthread = true;
					n->lthread = temp->lthread;
					temp->lthread = false;
					break;
				}
				else{
					temp = temp->left;
				}
			}
			else{
				if(temp->rthread){
					//adding right node to temp
					n->right = temp->right;
					n->left = temp;
					temp->right = n;
					n->rthread = temp->rthread;
					n->lthread = true;
					temp->rthread = false;
					break;
				}
				else{
					temp = temp->right;
				}
			}
		}
	}
}

//inorder traversal
void TBST::inorder(){
	Node* temp = this->root;
	//pointing left most element in inorder
	while(!temp->lthread){
		temp = temp->left;
	}
	cout<<temp->data<<" ";
	while(1){
		if(temp->rthread){
			temp = temp->right;
		}
		else{
			temp = temp->right;
			while(!temp->lthread){
				temp = temp->left;
			}
		}
		if(temp){
		cout<<temp->data<<" ";
		}
		else{
			break;
		}
	}
	cout<<endl;
}

void TBST::preorder(){
	Node* temp = root;
	while(temp){
		cout<<temp->data<<" ";
		if(!temp->lthread){
			temp = temp->left;
		}
		else if(!temp->rthread){
			temp = temp->right;
		}
		else{
			while(temp && temp->rthread){
				temp = temp->right;
			}
			if(temp){
				temp = temp->right;
			}
		}
	}
	cout<<endl;
}

void TBST::traversal(int c){
	if(!root){
		cout<<"Tree is empty!\n";
		return;
	}

	if(c == 2){
		this->inorder();
	}
	else if(c == 3){
		this->preorder();
	}
}

void TBST::delete_TBST(Node* r){
	Node* temp = r;
	Node* succ = r;
	while(!temp->lthread){
		temp = temp->left;
	}
	while(temp){
		if(temp->rthread){
			succ = temp->right;
		}
		else{
			succ = temp->right;
			while(!succ->lthread){
				succ = succ->left;
			}
		}
		cout<<temp->data<<" ";
		delete temp;
		temp = succ;
	}
	this->root = NULL;
	cout<<"Tree deleted\n";
}

void TBST::remove_node(){
	int c;
	cout<<"Enter node to be deleted: ";
	cin>>c;
	Node* par = NULL;
	Node* curr = root;
	bool flag = false;
	do{
		if(curr->data > c){
			if(curr->lthread){
				break;
			}
			else{
				par = curr;
				curr = curr->left;
			}
		}
		else if(curr->data < c){
			if(curr->rthread){
				break;
			}
			else{
				par = curr;
				curr = curr->right;
			}
		}
		if(curr->data == c){
			flag = true;
			break;
		}
	}
	while(!curr->lthread || !curr->rthread);
	if(flag){

		delete_node(par, curr);
	}
	return;
}

void TBST::delete_node(Node* par, Node* curr){
	if(curr->lthread && curr->rthread){
		A(par, curr);
	}
	else if(!curr->lthread && !curr->rthread){
		C(par, curr);
	}
	else if(!curr->lthread){
		B(par, curr);
	}
	else if(!curr->rthread){
		B(par, curr);
	}
}

void TBST::A(Node* par, Node* curr){
	if(curr == root){
		root = NULL;
	}
	else if(par->left == curr){
		par->lthread = true;
		par->left = curr->left;
	}
	else{
		par->rthread = true;
		par->right = curr->right;
	}
	delete curr;
	return;
}

void TBST::B(Node* par, Node* curr){
	if(!curr->lthread){
		Node* child;
		if(par->left == curr){
			par->left = curr->left;
			par = par->left;
		}
		else{
			par->right = curr->left;
			par = par->right;
		}
		while(!par->rthread){
			par = par->right;
		}
		par->right = curr->right;
	}
	else{
		if(par->left == curr){
			par->left = curr->right;
			par = par->left;
		}
		else{
			par->right = curr->right;
			par = par->right;
		}
		while(!par->lthread){
			par = par->left;
		}
		par->left = curr->left;
	}
	delete curr;
}

void TBST::C(Node* par, Node* curr){
	par = curr;
	Node* curr_suc = curr->right;
	while(!curr_suc->lthread){
		par = curr_suc;
		curr_suc = curr_suc->left;
	}
	curr->data = curr_suc->data;
	delete_node(par, curr_suc);
}

int main(){
	TBST t;
	int choice;
	bool f = true;
	cout<<"Enter 1 to enter value\n";
	cout<<"Enter 2 to get inorder traversal\n";
	cout<<"Enter 3 to get preorder traversal\n";
	cout<<"Enter 4 to delete tree\n";
	cout<<"Enter 5 to delete a node\n";
	while(f){
		cout<<"Enter choice: ";
		cin>>choice;
		switch (choice){
		case 0:
			f = false;
			break;
		case 1:
			t.make();
			break;
		case 2:
			t.traversal(2);
			break;
		case 3:
			t.traversal(3);
			break;
		case 4:
			t.clear_tree();
		case 5:
			t.remove_node();
		}
	}
}






