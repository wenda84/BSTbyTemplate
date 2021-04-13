#include <iostream>
#include "../include/bTree.hpp"

using namespace std;

#define VALUE_TYPE short

int main(void)
{
    bTree::bstTree<VALUE_TYPE>  bTree_ins(100) ;

    bTree::bstTree<VALUE_TYPE>* p_bTree =  &bTree_ins;

    p_bTree->insert_value(200);
    p_bTree->insert_value(150);
    p_bTree->insert_value(89);
    p_bTree->insert_value(99);
    p_bTree->insert_value(77);
    p_bTree->insert_value(666);
    p_bTree->insert_value(33);
    p_bTree->insert_value(22);
    p_bTree->insert_value(55);
    p_bTree->insert_value(101);
    p_bTree->insert_value(333);

    p_bTree->printTree();    

    cout << "min="<< p_bTree->min() << endl;
    cout << "max="<< p_bTree->max() << endl;

    VALUE_TYPE d = 88;
    if(p_bTree->getByValue(d))
        cout << d << " found" << endl;
    else
        cout << d << " not found" << endl;

    d = 55;
    if(p_bTree->getByValue(d))
        cout << d << " found" << endl;
    else
        cout << d << " not found" << endl;

    return 0;
}
