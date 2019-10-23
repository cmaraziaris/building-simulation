/* ! CPP PROGRAM == OBJECTS THAT SEND/RECEIVE MESSAGES ! */

//TODO: trades visitors metaksy xwrwn ???
// probz prepei oi exit na epistrefoun visitor*
// wste na mhn antigrafoume olh thn wra memory

/* ============================= */
class visitor
{
  int floor;
  int office_num;
  int priority; 
public:
  visitor(int fl, int off);
  ~visitor();
  void set_priority(int);
  int get_priority();
  int get_office_num();
  int get_floor();
};

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
  return 0;
}