template <class type>
void readLISP(binTreeNode<type> * r,  ifstream& infile)
{
	binTreeNode<int> * tmp;
	char parenthesis;
	int value;

	//get
	infile >> parenthesis;
	if (parenthesis == '(')
	{
		// left
		infile >> parenthesis; //get right parenthesis, but
		// this parenthesis can be either an integer or a "("
		if (parenthesis != ')')	// if it is a digit, put value in tree
		{
			infile.putback(parenthesis);
			infile >> value;
			r->left = new binTreeNode<int>;
			tmp = r->left;
			tmp->item = value;
			readLISP(r->left, infile);
			infile >> parenthesis; // get right parenthesis
		}
		else
		{
			r->left = nullptr;
		}

		//right
		infile >> parenthesis; // get left parenthesis
		cout << "parenthesis one " << parenthesis << endl;
		if (parenthesis == '(')
		{
			infile >> parenthesis; //get right parenthesis, but
			cout << "parenthesis two " << parenthesis << endl;
			cout << endl;
			if (parenthesis != ')')	// if it is a digit, put value in tree
			{
				infile.putback(parenthesis);
				infile >> value;
				r->right = new binTreeNode<int>;
				tmp = r->right;
				tmp->item = value;
				readLISP(r->right, infile);
				infile >> parenthesis; // get right parenthesis
			}
			else
			{
				r->right = nullptr;
			}
		}
	}
};
