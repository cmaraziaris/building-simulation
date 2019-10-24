#include <iostream>
#include "list_impl.h"
using namespace std;

visitor_list* list_insert (visitor* v,visitor_list* l) {
    visitor_list* n=new visitor_list;       // Create a new visitor listBlock
    n->member=v;                            // Put the info in
    if (!l) {                        // If the are no visitors this will be the first one
        l=n;
        l->link=NULL; 
     } else {                               
         n->link=l->link;
         n->link=l;
     } return n;
}

void list_remove (visitor* v,visitor_list** l) {
    visitor_list* tmp=*l,*prev;

    if ((tmp)&&(tmp->member->priority==v->priority)) {
        *l=tmp->link;
        delete tmp;
        return;
    }
    while ((tmp)&&(tmp->member->priority!=v->priority)) {
        prev=tmp;
        tmp=tmp->link;
    }
    if (!tmp) return;
    prev->link=tmp->link;
    delete tmp;
}