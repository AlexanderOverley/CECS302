//Alexander Overley
//CECS 302 Assignment 4


#include <iostream>
using namespace std;

template<typename Comparable>
class BinarySearchTree
{
	public:
		//int count;
		
		BinarySearchTree()
		{
			root = NULL;
		}
		BinarySearchTree(const BinarySearchTree & rhs);
		/**
		 * Destructor for the tree
		 */
		~BinarySearchTree()
		{
			makeEmpty();
		}

		const Comparable & findMin() const
		{
			return findMin(root);
		}

		const Comparable & findMax() const
		{
			return findMax(root);
		}

		/**
		 * Returns true if x is found in the tree.
		 */
		bool contains(const Comparable & x) const
		{
			return contains(x, root);
		}

		bool isEmpty() const
		{
			return ((root == NULL) ? true : false);
		}
		/**
		 * Print the tree contents in sorted order.
		 */
		void printTree(ostream & out = cout) const
		{
			out << "Start Traversing" << endl;
			if (isEmpty())
				out << "Empty tree" << endl;
			else
				printTree(root, out);
			out << "End Traversing" << endl;
		}

		void makeEmpty()
		{
			makeEmpty(root);
		}
		/**
		 * Insert x into the tree; duplicates are ignored.
		 */
		void insert(const Comparable & x)
		{
			insert(x, root);
			//count++;
		}

		/**
		 * Remove x from the tree. Nothing is done if x is not found.
		 */
		void remove(const Comparable & x)
		{
			remove(x, root);
			//count--;
		}
		
		bool replace(const Comparable & item, const Comparable & replacementItem)
		{
			replace(item, replacementItem, root);
		}

		/**
		 * Deep copy.
		 */
		const BinarySearchTree & operator=(const BinarySearchTree & rhs)
		{
			if (this != &rhs)
			{
				makeEmpty();
				root = clone(rhs.root);
			}
			return *this;
		}
		
		/*int getNumberOfNodes() 
		{
			return count;
		}*/

	private:
		struct BinaryNode
		{
				Comparable element;
				BinaryNode *left;
				BinaryNode *right;

				BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt) :
						element(theElement), left(lt), right(rt)
				{
				}
		};

		BinaryNode *root;
		
		//int count;

		/**
		 * Internal method to insert into a subtree.
		 * x is the item to insert.
		 * t is the node that roots the subtree.
		 * Set the new root of the subtree.
		 */
		void insert(const Comparable & x, BinaryNode * & t)
		{
			if (t == NULL)
			{
				t = new BinaryNode(x, NULL, NULL);
			//	count++;
			}
			else if (x < t->element)
			{
				insert(x, t->left);
			//	count++;
			}
			else if (t->element < x)
			{
				insert(x, t->right);
				//count++;
			}
			else
				; // Duplicate; do nothing
		}
		/**
		 * Internal method to remove from a subtree.
		 * x is the item to remove.
		 * t is the node that roots the subtree.
		 * Set the new root of the subtree.
		 */
		void remove(const Comparable & x, BinaryNode * & t)
		{
			if (t == NULL)
				return; // Item not found; do nothing
			if (x < t->element)
			{
				remove(x, t->left);
			//	count--;
			}
			else if (t->element < x)
			{
				remove(x, t->right);
				//count--;
			}
			else if (t->left != NULL && t->right != NULL) // Two children
			{
				t->element = findMin(t->right)->element;
				remove(t->element, t->right);
				//count--;
			}
			else
			{
				BinaryNode *oldNode = t;
				t = (t->left != NULL) ? t->left : t->right;
				delete oldNode;
			}
		}
		/**
		 * Internal method to find the smallest item in a subtree t.
		 * Return node containing the smallest item.
		 */
		BinaryNode * findMin(BinaryNode *t) const
		{
			if (t == NULL)
				return NULL;
			if (t->left == NULL)
				return t;
			return findMin(t->left);
		}
		/**
		 * Internal method to find the largest item in a subtree t.
		 * Return node containing the largest item.
		 */
		BinaryNode * findMax(BinaryNode *t) const
		{
			if (t != NULL)
				while (t->right != NULL)
					t = t->right;
			return t;
		}

		/**
		 * Internal method to test if an item is in a subtree.
		 * x is item to search for.
		 * t is the node that roots the subtree.
		 */
		bool contains(const Comparable & x, BinaryNode *t) const
		{
			if (t == NULL)
				return false;
			else if (x < t->element)
				return contains(x, t->left);
			else if (t->element < x)
				return contains(x, t->right);
			else
				return true; // Match
		}
		/**
		 * Internal method to make subtree empty.
		 */
		void makeEmpty(BinaryNode * & t)
		{
			if (t != NULL)
			{
				makeEmpty(t->left);
				makeEmpty(t->right);
				delete t;
			}
			t = NULL;
		}
		/**
		 * Internal method to compute the height of a subtree rooted at t.
		 */
		int height(BinaryNode *t)
		{
			if (t == NULL)
				return -1;
			else
				return 1 + max(height(t->left), height(t->right));
		}
		/**
		 * Internal method to print a subtree rooted at t in sorted order.
		 */
		void printTree(BinaryNode *t, ostream & out) const
		{
			if (t != NULL)
			{
				// out << t->element << "\n";
				printTree(t->left, out);
				// out << t->element << "\n";
				printTree(t->right, out);
				out << t->element << "\n";
			}
		}
		/**
		 * Internal method to clone subtree.
		 */
		BinaryNode * clone(BinaryNode *t) const
		{
			if (t == NULL)
				return NULL;

			return new BinaryNode(t->element, clone(t->left), clone(t->right));
		}
		
		bool replace(const Comparable & item, const Comparable & replacementItem, BinaryNode * & t)
		{
			if (t == NULL)
				return NULL; // Item not found; do nothing
			if (item < t->element)
			{
				remove(item, t->left);
				insert(replacementItem, t->left);
			}
			else if (t->element < item)
			{
				remove(item, t->right);
				insert(replacementItem, t->right);
			}
			else if (t->left != NULL && t->right != NULL) // Two children
			{
				t->element = findMin(t->right)->element;
				remove(t->element, t->right);
			}
			else
			{
				BinaryNode *oldNode = t;
				t = (t->left != NULL) ? t->left : t->right;
				delete oldNode;
			}
		}
		
		int getNumberOfNodes(BinaryNode * & t) const
		{
			
		}
};

int main()
{
	int count = 0; //counting manually because nothing else works
	
	cout << "Starting!" << endl;

	BinarySearchTree<int> myTree;

	myTree.insert(11);
	count++;
	cout << "Inserted  11" << endl;
	myTree.insert(12);
	count++;
	cout << "Inserted 12" << endl;
	myTree.insert(6);
	count++;
	cout << "Inserted  6" << endl;
	myTree.insert(8);
	count++;
	cout << "Inserted  8" << endl;
	myTree.insert(7);
	count++;
	cout << "Inserted  7" << endl;
	myTree.insert(9);
	count++;
	cout << "Inserted  9" << endl;
	myTree.insert(2);
	count++;
	cout << "Inserted  2" << endl;
	myTree.insert(4);
	count++;
	cout << "Inserted  4" << endl;
	myTree.insert(10);
	count++;
	cout << "Inserted  10" << endl;
	myTree.insert(5);
	count++;
	cout << "Inserted  5" << endl;
	myTree.insert(14);
	count++;
	cout << "Inserted  14" << endl;
	myTree.insert(13);
	count++;
	cout << "Inserted  13" << endl;

	myTree.printTree(cout);
	myTree.remove(13);
	count--;
	cout << "Removed  13" << endl;
	myTree.printTree(cout);
	myTree.remove(5);
	count--;
	cout << "Removed  5" << endl;
	myTree.replace(14, 22);
	cout << "Replaced 14 with 22" << endl;
	myTree.printTree(cout);
	cout << "Ending!" << endl;
	cout << "Total Number of Nodes: " << count << endl;
	return 0;
}
