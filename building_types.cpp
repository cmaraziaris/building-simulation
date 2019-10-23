/* ! CPP PROGRAM == OBJECTS THAT SEND/RECEIVE MESSAGES ! */

//TODO: trades visitors metaksy xwrwn ???

/* ============================= */
class visitor
{
  int floor;
  int office_num;
  int priority; 
public:
  visitor();
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
  waiting_room();
  ~waiting_room();
  void enter(visitor);
  void exit(visitor); // orismata?
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
  ground_level();
  ~ground_level();
  void enter(visitor);
  void exit(visitor); // orismata?
  void wait(visitor);
};

/* ============================= */
class office
{
  int number;
  int cap;
  visitor* visitors;
public:
  office();
  ~office();
  void enter(visitor);
  void exit(visitor);
  int get_cap();
};

/* ============================= */
class floor
{
  int cap; //opt ? 
  int curr;//opt ?
  waiting_room wr;
  office off[10];
public:
  floor();
  ~floor();
  void enter(visitor);
  void exit(visitor);
  int get_cap();
  int get_curr();
};

/* ============================= */
class elevator  //TODO: all of it
{
  int cap;
  int curr;
  visitor* visitors;
public:
  elevator();
  ~elevator();
  void operate();
  void enter(visitor);
  void exit(visitor);
  void stop_up(); //TODO: orismata
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
  floor fl[4];
  elevator el;
public:
  building(int N, int Nf, int Ng, int No, int Nl);
  ~building();
  void enter(visitor);
  void exit(visitor); // orismata?
};

/* ============================= */

int main(int argc, char const *argv[])
{
  return 0;
}