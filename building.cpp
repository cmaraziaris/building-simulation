/* ! CPP PROGRAM == OBJECTS THAT SEND/RECEIVE MESSAGES ! */
//~~~~~~~
//TODO: trades visitors metaksy xwrwn ???
// probz prepei oi exit na epistrefoun visitor*
// wste na mhn antigrafoume olh thn wra memory

#include <iostream>
#include <cstdio>

using namespace std;

/* ============================= */
class visitor
{
  int floor;
  int office_num;
  int priority; 
public:
  visitor(int fl, int off);
  //~visitor();
  void set_priority(int);
  int get_priority();
  int get_office_num();
  int get_floor();
};

visitor::visitor(int fl, int off){
  floor = fl;
  office_num = off;
}

void visitor::set_priority(int pr){ priority = pr; }

int visitor::get_priority()  { return priority; }
int visitor::get_office_num(){ return office_num; }
int visitor::get_floor()     { return floor; }


/* ============================= */
class waiting_room
{
  int cap;
  int curr;
  visitor* visitors;  // can be done w/ list
public:
  waiting_room(int N);
  ~waiting_room();
  void enter(visitor);
  visitor exit(visitor); // orismata?
  int get_cap();
  int get_curr();
};

/* ============================= */
class ground_level
{
  int cap;
  int curr;
  waiting_room wr; // TODO: orismata gia init
public:
  ground_level(int Ng);
  ~ground_level();
  void enter(visitor);
  visitor exit(visitor); // orismata?
  void wait(visitor); //metaferei ton visitor sto wr (?)/nai
};

/* ============================= */
class office
{
  int number; //opt ? 
  int cap;
  visitor* visitors;
public:
  office(int No, int num); // num questionable
  ~office();
  void enter(visitor);
  visitor exit(visitor);
  int get_cap();
};

/* ============================= */
class floor
{
  int cap; //opt ? 
  int curr;//opt ?
  waiting_room wr;
  office off[10]; //TODO: dynamic
public:
  floor(int Nf);
  ~floor();
  void enter(visitor);
  visitor exit(visitor);
  int get_cap();
  int get_curr();
};

/* ============================= */
class elevator  //TODO: all of it
{
  int cap;
  int curr;
  visitor* visitors;
public: // isws ola ektos apo operate prepei n mpoun private, dunno
  elevator(int Nl);
  ~elevator();
  void operate();
  void enter(visitor);
  visitor exit(visitor);
  void stop_up();   //TODO: orismata
  void stop_down(); //TODO: orismata  
  void empty_all(); //TODO: orismata
  int get_cap();
  int get_curr();
};


/* ============================= */
class building
{
  int cap;  /* capacity */
  int curr; /*  current ppl inside */
  ground_level ground;
  floor fl[4];  // TODO: dynamic
  elevator el;
public:
  building(int N, int Nf, int Ng, int No, int Nl);
  ~building();
  void enter(visitor);
  visitor exit(visitor); // orismata?
};

/* ============================= */


int main(int argc, char const *argv[])
{
  if (argc != 7) {  /* Error check */
    cerr << "\nUsage:\n" << argv[0] 
    << " <max_cap> <floor_cap> <office_cap> <elevator_cap>" 
    << " <number_of_visitors> <elevator_circles>\n" << endl;
    exit(EXIT_FAILURE); 
  }

  int max_cap = atoi(argv[1]);
  int cap_flr = atoi(argv[2]);
  int cap_off = atoi(argv[3]);
  int cap_elv = atoi(argv[4]);
  int num_vst = atoi(argv[5]);
  int l_circl = atoi(argv[6]);
  
  // test
  visitor harry(3,7);
  cout << harry.get_floor() << endl;
  cout << harry.get_office_num() << endl;
  harry.set_priority(667);
  cout << harry.get_priority() << endl;
  
  return 0;
}
