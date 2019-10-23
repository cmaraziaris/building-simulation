

/* ============================= */
class visitor
{
  int floor;
  int office_num;
  unsigned int priority; 
public:
  visitor();
  ~visitor();
  void set_priority(unsigned int pr){  
    priority = pr;
  } // probz mporei na graftei kai ksexwrista gia readability
  unsigned int get_priority(){
    return priority;
  }
};

/* ============================= */
class building  //TODO: ADD STUFF
{
  unsigned int cap;  /* capacity */
  unsigned int curr; /*  current ppl inside */
  ground_level grd;
  floor fl[4];
public:
  building();
  ~building();
  void enter(visitor v);
  void exit(visitor v); // orismata?
};

/* ============================= */
class waiting_room
{
  unsigned int cap;
  unsigned int curr;
  visitor* visitors;
public:
  waiting_room();
  ~waiting_room();
  void enter(visitor v);
  void exit(visitor v); // orismata?
};

/* ============================= */
class ground_level
{
  waiting_room wr; // TODO: orismata gia init
public:
  ground_level();
  ~ground_level();
  void enter(visitor v);
  void exit(visitor v); // orismata?
  void wait(visitor v);
};

/* ============================= */
class office
{
  int number;
  unsigned int cap;
  visitor* visitors;
public:
  office();
  ~office();
  void enter(visitor v);
  void exit(visitor v);
};

/* ============================= */
class floor
{
  unsigned int cap; //opt ? 
  unsigned int curr;//opt ?
  waiting_room wr;
  office off[10];
public:
  floor();
  ~floor();
  void enter(visitor v);
  void exit(visitor v);
};

/* ============================= */
class elevator
{
  unsigned int cap;
  unsigned int curr;
  visitor* visitors;
public:
  elevator();
  ~elevator();
  void operate();
  void enter(visitor v);
  void exit(visitor v);
  void stop_up(); //TODO: orismata
  void stop_down(); //TODO: orismata  
  void empty_all(); //TODO: orismata  
};