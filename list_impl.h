#include <iostream>
// #include kati na mou dikaiologei ta visitor

using namespace std;

struct visitor_list {
    visitor* member;
    visitor_list* link;
};

visitor_list* list_insert (visitor*,visitor_list*);
void list_remove (visitor*,visitor_list**);