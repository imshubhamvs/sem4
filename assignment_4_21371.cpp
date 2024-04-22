#include<iostream>
using namespace std;

class Data{
	unsigned long long int telephone;
	string name;
public:
	Data(){
		telephone = 0;
		name = "";
	}
	void show(){
		cout<<name<<":	"<<telephone<<endl;
	}
	friend class HashTable;
};

class HashTable{
	Data* arr;
	int max;
	int number = 0;

	//returns hashed value
	int HashCode(unsigned long long int key){
		return key%max;
	}
	void withreplacement(Data d, int pos);
	void withoutreplacement(Data d, int pos);
	void remove(unsigned long long int key);
	void search(unsigned long long int key);
	int probing_choice;//used to change probing method
public:
	HashTable(int size, int choice){
		arr = new Data[size];
		max = size;
		probing_choice = choice;
	}

	//changes probing method
	void changeProbing(int p){
		probing_choice = p;
	}

	void addData();
	void Display();
	void Search_name();
	void remove_entry();
};

//gets data for hashing
void HashTable::addData(){
	Data d;
	cout<<"Enter telephone number: ";
	cin>>d.telephone;
	cout<<"Enter name: ";
	cin>>d.name;
	int pos = HashCode(d.telephone);
	if(probing_choice == 1){
	withreplacement(d, pos);
	}
	else if(probing_choice == 2){
		withoutreplacement(d, pos);
	}
}

//linear probing without replacement
void HashTable::withoutreplacement(Data d, int pos){
	if(pos>max){
		pos = 0;
	}
	if(number<max){
	while(arr[pos].telephone != 0){
		pos++;
		pos %= max;
	}
	arr[pos] = d;
	number++;
	}
	else{
		cout<<"Table is full\n";
	}
}

//linear probing with replacement
void HashTable::withreplacement(Data d, int pos){
	if(pos>max){
			pos = 0;
		}
		if(number<max){
		if(HashCode(arr[pos].telephone) == pos){
			while(arr[pos].telephone != 0){
				pos++;
				pos %= max;
			}
			arr[pos] = d;
			number++;
		}
		else{
			Data temp = arr[pos];
			arr[pos] = d;
			while(arr[pos].telephone != 0){
				pos++;
				pos %= max;
			}
			arr[pos] = temp;
			number++;
			}
		}

		else{
			cout<<"Table is full\n";
		}
}

//display complete hash table
void HashTable::Display(){
		if(number!= 0){
			for(int i = 0; i<max; i++){
				cout<<i<<"	";
				arr[i].show();
			}
		}
		else{
			cout<<"Table is empty!!\n";
		}
}

//search for given key
void HashTable::search(unsigned long long int key){
	int pos = HashCode(key);
	int i = 0;
	while(arr[pos].telephone != key){
		pos += 1;
		pos %= max;
		i++;
		if(i == max){
			cout<<"Not found\n";
			 break;
		}
	}
	if(i != max){
	arr[pos].show();
	}
}

//used to get key to be searched
void HashTable::Search_name(){
	unsigned long long int key;
	cout<<"Enter number to search: ";
	cin>>key;
	search(key);
}

//removes given key and its associated value
void HashTable::remove(unsigned long long int key){
	int pos = HashCode(key);
		int i = 0;
		while(arr[pos].telephone != key){
			pos += 1;
			pos %= max;
			i++;
			if(i == max){
				 break;
			}
		}
		if(arr[pos].telephone == key){
		arr[pos].telephone = 0;
		arr[pos].name = "";
		cout<<"Entry deleted\n";
		}
		else{
			cout<<"Not found\n";
		}
}

//get key to be deleted
void HashTable::remove_entry(){
	unsigned long long int key;
		cout<<"Enter number to delete: ";
		cin>>key;
		remove(key);
}


int main(){

	int c;
	int size;

	//gets initial value of size
	cout<<"Enter size : ";
	cin>>size;
	cout<<"Enter 1 for Linear probing with replacement \n";
	cout<<"Enter 2 for linear probing without replacement\n";
	cout<<"Enter choice for probing : ";
	cin>>c;
	HashTable htable(size,c);

	while(1){
		cout<<"\nEnter 0 to quit\n";
		cout<<"Enter 1 to add data\n";
		cout<<"Enter 2 to search number\n";
		cout<<"Enter 3 display all entries\n";
		cout<<"Enter 4 to delete a number\n";
		cout<<"Enter 5 to change probing method\n";
		cout<<"Enter your choice: ";
		cin>>c;
		if(c == 0){
			break;
		}
		else if(c == 1){
			//to add data in hash table
			htable.addData();
		}
		else if(c == 2){
			//to search name in hash table
			htable.Search_name();
		}
		else if(c == 3){
			//to display all entries
			htable.Display();
		}
		else if(c == 4){
			//to delete an entry
			htable.remove_entry();
		}
		else if(c == 5){
			//to change probing method
			cout<<"Enter 1 for Linear probing with replacement \n";
			cout<<"Enter 2 for linear probing without replacement\n";
			cout<<"Enter choice for probing : ";
			htable.changeProbing(c);
		}
	}
}
