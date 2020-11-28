#include<iostream>
#include<deque>	
#include<algorithm>
#include<deque> 
#include<cstring>
#include<conio.h>
#include<fstream>

using namespace std;

ifstream iff;

const int n = 40;
const int l = 40;
char cho;
int counter = 0;

bool Check_CNIC(unsigned long long int);

class Patient_info
{
public:
	Patient_info *left;
	Patient_info *right;
	int Patient_id;
	static int temp;
	unsigned long long CNIC;
	int age;
	char Patient_Name[n];
	char Father_Name[n];
	char Doctor_Name[n];
	char Disease_Name[n];
	Patient_info()
	{
		left = NULL;
		right = NULL;
	}
};
class Patient_tree
{
private:
	Patient_info *root;
	Patient_info* insert(Patient_info *, int);
	int height(Patient_info *);
	int diff(Patient_info *);
	Patient_info* balance(Patient_info *);
	Patient_info* singleLeft(Patient_info *);
	Patient_info* singleRight(Patient_info *);
	Patient_info* leftRight(Patient_info *);
	Patient_info* rightLeft(Patient_info *);
	void Ascending(Patient_info *);
	void Descending(Patient_info *);
	void Smallest(Patient_info *);
	void Greatest(Patient_info *);
	Patient_info* small_of_right(Patient_info *);
	Patient_info* Delete(Patient_info *, int);
	void Search(Patient_info *, int);


public:
	void Traverse()
	{
		cout << "\nTraversing  - Ascending\n";
		Ascending(root);
	}
	void insert1(int v)
	{
		insert(root, v);
	}
	void del1(int v)
	{
		Delete(root, v);
	}
	void Great()
	{
		Greatest(root);
	}
	void 	Small()
	{
		Smallest(root);
	}
	void Find(int t)
	{
		Search(root,t);
	}
	void ascend()
	{
		Ascending(root);
	}
	void descend()
	{
		Descending(root);
	}

	

	void showRoot()
	{
		cout << endl << "Root is " << root->Patient_id << endl;
	}
	Patient_tree()
	{
		root = NULL;
	}
	void GetData(Patient_info *);
	Patient_info store;
	void StoreData(int value)
	{
		insert(root, value);
	}

	void readData()
	{
		iff.read(reinterpret_cast<char*>(&store), sizeof(store));



		while (!iff.eof())
		{
			StoreData(store.Patient_id);

			// cout << store.Patient_id;
			// cout << endl;
			// cout << store.CNIC; cout << endl;
			// cout << store.age; cout << endl;
			// cout << store.Patient_Name; cout << endl;
			// cout << store.Father_Name; cout << endl;
			// cout << store.Doctor_Name; cout << endl;
			// cout << store.Disease_Name; cout << endl;

			iff.read(reinterpret_cast<char*>(&store), sizeof(store));
		}
	}




};

int main()
{
	Patient_tree obj;
	iff.open("rr.dat", ios::binary);

	if (!iff)
	{
		cout << "ERROR opening file";
		return 0;
	}





	obj.readData();




	obj.Traverse();

	char c;
	while (true)
	{		
		
		cout << "\n1.Addnew\n2.Delete\n3.Greatest\n4.Smallest\n5.Acsending Traverse\n6.Descending Traverse\n7.Search\n0.Exit The Program";
		c = _getch();
		switch (c)
		{
		case '1':
		{
					cout << string(50, '\n');
					int g;
					cout << "\nEnter Patient id to ";
					cin >> g;

					obj.insert1(g);
					break;
		}
		case '2':
		{
					cout << string(50, '\n');
					int g;
					cout << "\nEnter Patient Id";
					cin >> g;

					obj.del1(g);
					break;
		}
		case '3':
		{
			cout << string(50, '\n');

					obj.Great();
					break;
		}
		case '4':
		{
			cout << string(50, '\n');

					obj.Small();
					break;
		}
		case '5':
		{
			cout << string(50, '\n');

					obj.ascend();
					break;
		}
		case '6':
		{
			cout << string(50, '\n');

					obj.descend();
					break;
		}
		case '7':
		{
			cout << string(50, '\n');

					int tt;
					cout << "\nEnter Patient Id which you wanna search\n";
					cin >> tt;
					obj.Find(tt);
		}
		case '0':
		{
			return 0;
		}
		default:
		{
			cout << string(50, '\n');

				cout << "Bad Choice";
		}
	}
}
	//iff.read(reinterpret_cast<char*>(store))


	/*bool cc = false;
	int temp;

	cout << "\nEntering Patient Id Bro\n";
	cout << "Counet is " << counter;
	temp=counter;

	obj.insert1(temp);



	obj.showRoot();*/
	system("pause");
	return 0;
}
Patient_info* Patient_tree::insert(Patient_info *tree, int value)
{
	if (root == NULL)
	{
		root = new Patient_info;
		root->Patient_id = value;
		GetData(root);
		cout << "\n" << root->Patient_id << " inserted as root\n";
		return root;
	}
	else if (value < tree->Patient_id)
	{
		if (tree->left == NULL)
		{
			tree->left = new Patient_info;
			tree->left->Patient_id = value;
			GetData(tree->left);
			cout << endl << tree->left->Patient_id << " inserted at left of " << tree->Patient_id << endl;
		}
		else
		{
			tree->left = insert(tree->left, value);
			// cout << endl << "Now Checking Balance function of " << tree->Patient_id;
			tree = balance(tree);
		}
	}
	else if (value > tree->Patient_id)
	{
		cout << "into value > tree->Patient_id";
		if (tree->right == NULL)
		{
			tree->right = new Patient_info;
			tree->right->Patient_id = value;
			GetData(tree->right);
			cout << endl << tree->right->Patient_id << " inserted at right of " << tree->Patient_id << endl;
		}
		else
		{
			tree->right = insert(tree->right, value);
			// cout << endl << "Now Checking Balance function of " << tree->Patient_id;
			tree = balance(tree);
		}
	}
	else
		cout << "\nValue already exists\n";
	root = tree;
	return tree;
}
int Patient_tree::height(Patient_info *tree)
{
	int lh, rh;
	if (tree == NULL)
		return 0;
	if (tree->left == NULL)
		lh = 0;
	else
		lh = height(tree->left) + 1;
	if (tree->right == NULL)
		rh = 0;
	else
		rh = height(tree->right) + 1;
	return max(lh, rh);
}
int Patient_tree::diff(Patient_info *tree)
{
	return height(tree->left) - height(tree->right);
}
Patient_info* Patient_tree::balance(Patient_info *tree)
{
	cout << "\n I am into the balance Function of " << tree->Patient_id << " Sir !\n";
	int bfactor = diff(tree);
	if (bfactor > 1) //Left Skewed
	{
		cout << "\nSir! " << tree->Patient_id << "is Left skewed\n";
		if (diff(tree->left) > 0)
		{
			cout << "\nSir! " << tree->Patient_id << "is going into Single Right Rotation\n";
			tree = singleRight(tree);
			//cout << "AFter rotation tree is \n"; Ascending(tree);
		}
		else
		{
			cout << "\nSir! " << tree->Patient_id << "is going into Left Right Double Rotation\n";
			tree = leftRight(tree);
		}
	}
	else if (bfactor < -1) //Right Skewed
	{
		cout << "\nSir! " << tree->Patient_id << "is Right skewed\n";
		if (diff(tree->right) < 0)
		{
			cout << "\nSir! " << tree->Patient_id << "is going into Single Left Rotation\n";
			singleLeft(tree);
		}
		else
		{
			cout << "\nSir! " << tree->Patient_id << "is going into Right Left Double Rotation\n";
			rightLeft(tree);
		}
	}
	else
		// cout << endl << tree->Patient_id << " is already balanced Sir ! \n";
	//cout << "After rotation tree is \n"; Ascending(tree);
	return tree;
}
Patient_info* Patient_tree::singleLeft(Patient_info *tree)
{
	Patient_info* temp;
	temp = tree->right;
	tree->right = temp->left;
	temp->right = tree;
	return tree;
}
Patient_info* Patient_tree::singleRight(Patient_info *tree)
{
	Patient_info* temp;
	temp = tree->left;
	tree->left = temp->right;
	temp->right = tree;
	return temp;
}
Patient_info* Patient_tree::leftRight(Patient_info *tree)
{
	tree->left = singleLeft(tree->left);
	tree = singleRight(tree);
	return tree;
}
Patient_info* Patient_tree::rightLeft(Patient_info *tree)
{
	tree->right = singleRight(tree->right);
	tree = singleLeft(tree);
	return tree;
}


void Patient_tree::Ascending(Patient_info *tree)
{
	if (tree != NULL)
	{
		Ascending(tree->left);
		cout <<"\nPatiend's Id :\t" << tree->Patient_id << endl;
		cout <<"\nPatiend's Name :\t" << tree->Patient_Name << endl;
		cout <<"\nPatiend's Doctor :\t" << tree->Doctor_Name << endl;
		cout <<"\nPatiend's Father:\t" << tree->Father_Name << endl;
		cout <<"\nPatiend's Disease:\t" << tree->Disease_Name << endl;
		Ascending(tree->right);
	}
}
void Patient_tree::Descending(Patient_info *tree)
{
	if (tree != NULL)
	{
		Descending(tree->right);
		cout << "\nPatient Id :\t" << tree->Patient_id <<endl;
		Descending(tree->left);

	}
}
void Patient_tree::Smallest(Patient_info *tree)
{
	if (tree->left == NULL)
	{
		cout << "Smallest is " << tree->Patient_id << endl;
	}
	else
		Smallest(tree->left);
}
void Patient_tree::Greatest(Patient_info *tree)
{
	if (tree->right == NULL)
	{
		cout << "Greatest is " << tree->Patient_id << endl;
	}
	else
		Greatest(tree->left);
}
void Patient_tree::GetData(Patient_info *tree)
{
	//Storing in Tree
	tree->Patient_id = store.Patient_id;
	tree->CNIC = store.CNIC;
	tree->age = store.age;
	for (unsigned short int i = 0; i<l; i++)
	{
		tree->Patient_Name[i] = store.Patient_Name[i];
		tree->Father_Name[i] = store.Father_Name[i];
		tree->Doctor_Name[i] = store.Doctor_Name[i];
		tree->Disease_Name[i] = store.Disease_Name[i];
	}
}

Patient_info* Patient_tree::Delete(Patient_info *root, int value)
{
	if (root == NULL)
		return NULL;
	// Now Searching for that node which we wanna Delete
	if (value < root->Patient_id)
		root->left = Delete(root->left, value);
	else if (value > root->Patient_id)
		root->right = Delete(root->right, value);

	//Node Founded which is to be deleted
	else if ((root->left == NULL) && (root->right == NULL))
	{
		//cout << "Deleting node :- " << root->Patient_id;
		delete root;
		root = NULL;
		return root;
	}
	//Case 2 : One Child
	else if (root->left == NULL)
	{
		Patient_info *temp = root;
		root = root->right;
		delete temp;
		return root;
	}
	else if (root->right == NULL)
	{
		Patient_info *temp = root;
		root = root->left;
		delete temp;
		return root;
	}
	//Case 3 : Two Children
	else
	{
		Patient_info* smallest = small_of_right(root->right); //Find the Smallest in Right Subroot
		//Delete by Copying
		// Step 1 : Copy Smallest->Patient_id to root->Patient_id
		root->Patient_id = smallest->Patient_id; cout << "Value copied ";
		//Step 2 : Delete the Smallest
		Delete(root->right, smallest->Patient_id);
	}
	return root;
}

Patient_info* Patient_tree::small_of_right(Patient_info *root) {
	if (root->left == NULL)
		return root;
	else
		return small_of_right(root->left);
}
void Patient_tree::Search(Patient_info *tree, int value)
{
	counter++;
	if (tree == NULL)
	{
		cout << "Tree is Empty";
		return;
	}
	// Now Searching for that node which we wanna Delete
	if (value < tree->Patient_id)
		Search(tree->left, value);
	else if (value > tree->Patient_id)
		Search(tree->right, value);
	else
		cout << "Node Founded after " << counter << " Traversal(s) ";
}
