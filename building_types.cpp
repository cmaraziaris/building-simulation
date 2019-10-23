

/* ============================= */
class visitor
{
  int floor;
  int office_num;
  int priority; 
public:
  visitor();
  ~visitor();
  void set_priority(int pr){  
    priority = pr;
  } // probz mporei na graftei kai ksexwrista gia readability
  int get_priority(){
    return priority;
  }
};

/* ============================= */
class waiting_room
{
  int cap;
  int curr;
  visitor* visitors;
public:
  waiting_room();
  ~waiting_room();
  void enter(visitor);
  void exit(visitor); // orismata?
};

/* ============================= */
class ground_level
{
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
};

/* ============================= */
class elevator
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
};


/* ============================= */
class building
{
  int cap;  /* capacity */
  int curr; /*  current ppl inside */
  ground_level grd;
  floor fl[4];
public:
  building();
  ~building();
  void enter(visitor);
  void exit(visitor); // orismata?
};

/* ============================= */

int main(int argc, char const *argv[])
{
  return 0;
}