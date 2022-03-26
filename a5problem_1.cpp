//Alexander Overley
//CECS 302 problem 1 assignment 5

#include <iostream>


using namespace std;

class HashTable
{
	public:
		int table[10];
		int key;
		
		HashTable()
		{
			table[10] = {0};
			key = 0;
		}
		
		void HashFunction(int x)
		{
			key = x % 10;
		}
		
		int insert(int num)
		{
			int index = 0;
			int count = 0;
			
			HashFunction(num);
			
			if(table[key] == NULL)
			{
				table[key] = num;
			}
			else
			{
				key++;
				while(key < 10)
				{
					if(table[key] == NULL)
					{
						table[key] = num;
						break;
					}
					else
					{
						key++;
					}
				}
				
				key = 0;
				
			}
		}
	private:	
};

int main()
{
	HashTable hash;
	
	int hasht[10];
	int hold;
	
	for(int i = 0; i < 10; i++)
	{
		cout << "Enter An Integer: " << endl;
		cin >> hold;
		
		hold = hasht[i];
		hash.insert(hold);
		
		
	}
	
	for(int i = 0; i < 10; i++)
	{
		cout << hasht[i] << endl;
		
		
	}
}

// address = key mod n

//store input 66, 47, 87, 90, 126, 140, 145, 393

//hash function h(x) = x mod 10


//show techniques results
//separate chaining hash table,  hash table using linear probing, i.e. h(x) = (x mod 10 + i) mod 10,
// hash table using quadratic probing, i.e. h(x) = (x mod 10 + i2) mod 10,  hash table with second hash function h2(x) = 7 - (x mod 7), i.e. h(x) = (x mod 10 + i . h2(x)) mod 10.  
