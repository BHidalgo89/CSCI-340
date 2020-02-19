#include "assignment8.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

// key is in form of letter-letter-digit
// compute sum <-- ascii(pos1)+ascii(pos2)+ascii(pos3)
// compute sum%htable_size
int HT::hashing(const string& key) {
    return ((int)key[0] + (int)key[1] + (int)key[2])%table_size;
}
/******************************************************************************
Function:   Entry* get_entry(const string& line)
Parameters: A constant reference to a string object
Returns:    An Entry pointer
Purpose:    This method takes a line of input and parses it to create a new
            entry.
Notes:      The line is in format of A:item-key:item-description. Three strings
            separated by ':' where the first string is just a single character.
            Global Function.
*******************************************************************************/
Entry* get_entry(const string& line)
{
  Entry* newEntry = new Entry;
  string keyCopy = line.substr(2,3);
  newEntry->key = keyCopy;
  string descCopy = line.substr(6,line.size()-6);
  newEntry->description = descCopy;
  return newEntry;
}

/******************************************************************************
Function:   string get_key(const string& line)
Parameters: A reference to a constant string object
Returns:    A string object
Purpose:    This method takes a line of input and parses it to return the item-key.
Notes:      The line is in the format of X:item-key. Two strings separated by
            ':' where the first string is just a singgle character.
Notes:      Global Function.
*******************************************************************************/
string get_key(const string& line)
{
  string key = line.substr(2,8);
  return key;
}

/*********************************************************************************
Method:     HT::HT(int size)
Parameters: An integer
Returns:    N/A
Purpose:    Dynamically creates a vector of the Entry struct.
            Properly initiallizes other data members as well.
Notes:      Constructor of the HT class. Public Method.
********************************************************************************/
HT::HT(int size = 11)
{
  hTable = new vector<Entry>(size);
  table_size = size;
  item_count = 0;
}

/******************************************************************************
Method:     HT::~HT()
Parameters: N/A
Returns:    N/A
Purpose:    Destructor of the HT class. Deletes an HT object
Notes:      Since the has table hTable is implemented as a dynamically created
            vector, it's memory is released here by delete operator.
            Public method.
*******************************************************************************/
HT::~HT()
{
  delete hTable;
}

/******************************************************************************
Method:     int HT::search(const string& key)
Parameters: A reference to a constant string
Returns:    If the search is successful, this function returns the postion of
            the found item. Otherwise, it returns -1.
Purpose:    Searches the hash table for a record with a given key. Computes
            the hash value of the given key.
Notes:      Public Method
******************************************************************************/
int HT::search(const string& key)
{
     int hValue = hashing(key);
     for(int i = 0; i < table_size; i++)
       {
     if(hTable->at(hValue).key == key)
        {
         return hValue;
        }
       hValue = (hValue + 1) % table_size;
       }
     return -1;
}

/******************************************************************************
Method:     bool HT::insert(const Entry& e)
Parameters: A constant reference to an Entry object
Returns:    A boolean value; If the item's key already exists within the hash
            table or the table is already full, return false. Otherwise, if the
            insert is successful, return true.
Purpose:    Takes an item e from the input stream and inserts it into the hash
            table. Checks if the item's key already exists in the table or not.
            If yes, this function prints out an error message. If the
            hash table is already full, this function prints and error message
            Computes the hash value of item e's key. If the hash table position
            of the hash value is empty, the item is placed on that position.
            Otherwise, an appropriate position is determined by linear probing.
            After the item is inserted, item_count is increased.
Notes:      Public Method
******************************************************************************/
bool HT::insert(const Entry& e)
{
  if(search(e.key) != -1)
    {
     cout << "Key already exists!" << endl;
     return false;
    }
  else if(item_count == table_size)
    {
     cout << "Hash table is full!" << endl;
     return false;
    }
  else
    {
     int hValue = hashing(e.key);
     for(int i = 0; i < table_size; i++)
       {
     if(hTable->at(hValue).key == "---" || hTable->at(hValue).key == "+++")
        {
         hTable->at(hValue) = e;
         item_count++;
         return true;
        }
       hValue = (hValue + 1) % table_size;
       }
        return false;
    }
}

/******************************************************************************
Method:     bool HT::remove(const string& s)
Parameters: A constant reference to a string
Returns:    If the key is not found, this function returns false. Otherwise,
            it retuns true.
Purpose:    Removes an item with a given key s. Searches for the key in the
            hash table. If the key is not found, returns false. Otherwise, it
            removes the entry of the given key by setting its key as "+++",
            decreases item_count, and returns true at the end.
Notes:      Public Method
******************************************************************************/
bool HT::remove(const string& s)
{
  if(search(s) != -1)
    {
     int found = search(s);
     hTable->at(found).key = "+++";
     item_count--;
     return true;
    }
  else
     return false;
}

/******************************************************************************
Method:     void HT::print()
Parameters: N/A
Returns:    N/A
Purpose:    Prints the existing entries in the hash table: the index value, the
            key, and the description.
Notes:      Public Method
******************************************************************************/
void HT::print()
{
 cout << endl << "----Hash Table----" << endl;
 for(int i = 0; i < table_size; i++)
 {
 if(hTable->at(i).key != "---" && hTable->at(i).key != "+++")
 cout << " " << i << ": " << hTable->at(i).key << " " << hTable->at(i).description<< endl;
 }
 cout << "------------------" << endl;
}


int main(int argc, char** argv ) {
    if ( argc < 2 ) {
        cerr << "argument: file-name\n";
        return 1;
    }

    HT ht;
    ifstream infile(argv[1], ios::in);
    string line;
    infile >> line;
    while ( !infile.eof() ) {
        if ( line[0] == 'A' ) {
            Entry* e = get_entry( line );
            ht.insert( *e );
            delete e;
        }
        else {
            string key = get_key(line);
            if ( line[0] == 'D' ) {
                cout << "Removing " << key << "...\n";
                bool removed = ht.remove( key );
                if ( removed )
                    cout << key << " is removed successfully...\n\n";
                else
                    cout << key << " does not exist, no key is removed...\n\n";
            }
            else if ( line[0] == 'S' ) {
                int found = ht.search( key );
                if ( found < 0 ) 
                    cout << key << " does not exit in the hash table ..." << endl << endl;
                else
                   cout << key << " is found at table position " << found << endl << endl;
            }
            else if ( line[0] == 'P' ) {
                cout << "\nDisplaying the table: " << endl;
                ht.print();
            }
            else
                cerr << "wrong input: " << line << endl;
        }
        infile >> line;

    }

    infile.close();
    return 0;
}
