#include<iostream>
#include<deque>	
#include<algorithm>
#include<deque> 
#include<cstring>
#include<conio.h>
#include<fstream>

using namespace std;

ofstream off;

const int n=40;
const int l=40;
char key;
int counter=1;
class Patient_Info
{
public:
	Patient_Info *left;
	Patient_Info *right;
	int Patient_id;
	unsigned long long int CNIC;
	int age;
	char Patient_Name[n];
	char Father_Name[n];
	char Doctor_Name[n];
	char Disease_Name[n];
	Patient_Info()
	{
		left = NULL;
		right = NULL;
	}
};

class Patient_tree
{
private:
	Patient_Info *root;
	Patient_Info* insertByPatientId(Patient_Info *, int);
	Patient_Info* insertByCNIC(Patient_Info *,unsigned long long int );
	int height(Patient_Info *);
	int diff(Patient_Info *);
	Patient_Info* balance(Patient_Info *);
	Patient_Info* singleLeft(Patient_Info *);
	Patient_Info* singleRight(Patient_Info *);
	Patient_Info* leftRight(Patient_Info *);
	Patient_Info* rightLeft(Patient_Info *);
	void breathFirst(Patient_Info *);

public:
	void Traverse()
	{
		cout << "\nTraversing BreathFirst\n";
		breathFirst(root);
	}
	void showRoot()
	{
		cout << endl << "Root is " << root->Patient_id << endl;
	}
	void insert1(int);	
	void insertnic(unsigned long long int);
	Patient_tree()
	{
		root = NULL;
	}
	void GetData(Patient_Info *);
	Patient_Info store;

};

void Patient_tree::insert1(int value)
{
	insertByPatientId(root,value);

}
void Patient_tree::insertnic(unsigned long long int value)
{
	insertByCNIC(root,value);
}

bool Check_CNIC(unsigned long long int);

//int Patient_Info::temp=0;


int main()
{
	Patient_tree treeobj;	
	cout << counter ;

	// Opening File
	off.open("rr.dat",ios::binary);


	cout << "Build Tree by using as key :\n1. CNIC \n2. Patient Id)\n3. Exit";
	while (cin)
	{
		key = _getch();
		if (key == '1' || key == '2' || key == '3')
			break;
	}
	if (key == '3')	//Exit
	{
		return 0;
	}

		bool validCNIC = false;
	Add_Patient:
		if (key == '1') //CNIC
		{
			unsigned long long temp;
			do
			{
				cout << "\nEnter Patient's CNIC \n";
				cin >> temp;
				if (Check_CNIC(temp) == true)
					validCNIC = true;
			} while (validCNIC == false);
			treeobj.insertnic(temp);
		}
		else //Pid
		{
			int temp;
			// cout << "\nEnter Patient Id plz\n";
			// cout << "Counet is " << counter;
			temp=counter;
	
			treeobj.insert1(temp);
		}
		char an;
		cout << "Enter Another (Y/N)\n";
		an=_getch();
		if(an == 'Y' || an=='y')
			goto Add_Patient;

	
	treeobj.Traverse();
	treeobj.showRoot();
	system("pause");	return 0;
}

Patient_Info* Patient_tree::insertByPatientId(Patient_Info *tree, int value)
{
	if (root == NULL)
	{
		root = new Patient_Info;
		root->Patient_id = counter;
		counter++;
		GetData(root);
		cout << "\n" << root->Patient_id << " inserted as root\n";
		cout << "New Counter is "<<counter;
		return root;
	}
	else if (value < tree->Patient_id)
	{
		if (tree->left == NULL)
		{
			tree->left = new Patient_Info;
			tree->left->Patient_id = counter;
			counter++;
			GetData(tree->left);
			cout << endl << tree->left->Patient_id << " inserted at left of " << tree->Patient_id << endl;
		}
		else
		{
			tree->left = insertByPatientId(tree->left, value);
			cout << endl << "Now Checking Balance function of " << tree->Patient_id;
			tree = balance(tree);
		}
	}
	else if (value > tree->Patient_id)
	{
		cout << "into value > tree->Patient_id";
		if (tree->right == NULL)
		{
			tree->right = new Patient_Info;
			tree->right->Patient_id = counter;
			counter++;
			GetData(tree->right);
			cout << endl << tree->right->Patient_id << " inserted at right of " << tree->Patient_id << endl;
		}
		else
		{
			tree->right = insertByPatientId(tree->right, value);
			cout << endl << "Now Checking Balance function of " << tree->Patient_id;
			tree = balance(tree);
		}
	}
	else
		cout << "\nValue already exists\n";
	root = tree;
	return tree;
}

// Insert Patient using CNIC as tree key
Patient_Info* Patient_tree::insertByCNIC(Patient_Info *tree, unsigned long long int  value)
{
	
	if (root == NULL)	{
		
		root = new Patient_Info;
		root->CNIC = value;
		GetData(root);
		cout << "\nCNIC\t" << root->CNIC << " Inserted as root of Patient Tree\n";
		return root;
	}
	else if(value == tree->CNIC) {
		// CNIC / key cannot repeat
		cout << "\nCNIC \t"  << value << "  already exists\n";
	}
	else if (value < tree->CNIC)
	{
		if (tree->left == NULL)
		{
			tree->left = new Patient_Info;
			tree->left->CNIC = value;
			cout << endl << tree->left->CNIC << " Inserted in left of " << tree->CNIC << endl;
		}
		else
		{
			tree->left = insertByCNIC(tree->left, value);
			cout << endl << "Now Checking Balance function of id" << tree->Patient_id;
			tree = balance(tree);
		}
	}
	else if (value > tree->CNIC)
	{
		cout << "into value > tree->Patient_id";
		if (tree->right == NULL)
		{
			tree->right = new Patient_Info;
			tree->right->CNIC = value;
			//tree->right->left = NULL;
			//tree->right->right = NULL;
			cout << endl << tree->right->CNIC << " Inserted at right of " << tree->CNIC << endl;
		}
		else
		{
			tree->right = insertByCNIC(tree->right, value);
			cout << endl << "Now Checking Balance function of " << tree->CNIC;
			tree = balance(tree);
		}
	}
	
	root = tree;
	return tree;
}


int Patient_tree::height(Patient_Info *tree)
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
int Patient_tree::diff(Patient_Info *tree)
{
	return height(tree->left) - height(tree->right);
}
Patient_Info* Patient_tree::balance(Patient_Info *tree)
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
			//cout << "AFter rotation tree is \n"; breathFirst(tree);
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
		cout << endl << tree->Patient_id << " is already balanced Sir ! \n";
	//cout << "After rotation tree is \n"; breathFirst(tree);
	return tree;
}
Patient_Info* Patient_tree::singleLeft(Patient_Info *tree)
{
	Patient_Info* temp;
	temp = tree->right;
	tree->right = temp->left;
	temp->right = tree;
	return tree;
}
Patient_Info* Patient_tree::singleRight(Patient_Info *tree)
{
	Patient_Info* temp;
	temp = tree->left;
	tree->left = temp->right;
	temp->right = tree;
	return temp;
}
Patient_Info* Patient_tree::leftRight(Patient_Info *tree)
{
	tree->left = singleLeft(tree->left);
	tree = singleRight(tree);
	return tree;
}
Patient_Info* Patient_tree::rightLeft(Patient_Info *tree)
{
	tree->right = singleRight(tree->right);
	tree = singleLeft(tree);
	return tree;
}
void Patient_tree::breathFirst(Patient_Info *tree)
{
	deque<Patient_Info*> dq;
	dq.push_back(tree);
	while (!dq.size() == 0)
	{
		if (dq.front()->left != NULL)
			dq.push_back(dq.front()->left);
		if (dq.front()->right != NULL)
			dq.push_back(dq.front()->right);
		cout << dq.front()->Patient_id << endl;
		cout <<dq.front()->CNIC<<endl;
		dq.pop_front();
	}
}

bool Check_CNIC(unsigned long long int nic)
{
	int digits = 0;
	while (nic != 0)
	{
		digits++;
		nic /= 10;
	}
	if (digits != 13)
	{
		cout << "Digits =\t" << digits;
		cout << "Wrong CNIC\nCNIC must contain 15 digits\nEnter CNIC again";
		return false;
	}
	return true;
}

void Patient_tree::GetData(Patient_Info *tree)
{
	// cout <<"itogetdata";
	if (key == '1')	//CNIC is Key , so Pid is to be entered
	{
		cout << "\ Patient's Id\n";
		tree->Patient_id=counter+1;
		//counter++;
	}
	else //Pid is key , getting CNIC
	{
		bool c = false; unsigned long long int k;
		while (c == false)
		{
			cout << "\nEnter CNIC\n";
			cin >> tree->CNIC;
			// cout << "entered";
			k = tree->CNIC;
			if ( Check_CNIC(k) == true)
				c = true;
		}
	}

	cout << "\nEnter Patient's Age\n";
	cin >> tree->age;
	cout << "\nEnter Patient's Name\n";
	cin.ignore();
	cin.get(tree->Patient_Name,l);
	//Objarr[0].Diseases = tree->Diseasec;
	cout << "\nEnter his Father's Name\n";
	//getline(cin, tree->Father_Name);
	cin.ignore();
	cin.get(tree->Father_Name, l);

	cout << "\nEnter Doctors's Name\n";
	//getline(cin, tree->Doctor_Name);
	cin.ignore();
	cin.get(tree->Doctor_Name, l);
	cout << "\nEnter Patient's Disease\n";
	//getline(cin, tree->Disease);
	cin.ignore();
	cin.get(tree->Disease_Name, l);

	store.Patient_id=tree->Patient_id;

	
	store.age=tree->age;
	store.CNIC=tree->CNIC;
	for(int   i=0;i<n;i++)
	{
		store.Father_Name[i]=tree->Father_Name[i];
		store.Disease_Name[i]=tree->Disease_Name[i];
		store.Doctor_Name[i]=tree->Doctor_Name[i];
		store.Patient_Name[i]=tree->Patient_Name[i];
	}
	
	cout << "age is "<< store.age<<endl;
	cout << "Cnin is "<< store.CNIC<<endl;
	cout << "Name is "<< store.Patient_Name<<endl;
	cout << "fna is "<< store.Father_Name<<endl;
	cout << "d is "<< store.Doctor_Name<<endl;
	cout << "disease is "<< store.Disease_Name<<endl;

	off.write(reinterpret_cast<char*>(&store),sizeof(store));
}
