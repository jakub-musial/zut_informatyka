#include "BinarySearchTree.h"

using namespace std;

int main()
{
    BinarySearchTree<int> bts;
    bts.add(5);
    bts.add(3);
    bts.add(2);
    bts.add(4);
    bts.add(8);
    bts.add(7);
    bts.add(9);
    bts.display_tree();
    
    cout << bts.find(7)->data << endl;
    cout << "-------------------------------" << endl;

   bts.clear();
   bts.display_tree();
   
   bts.preorder();
}