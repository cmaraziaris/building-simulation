/* ! CPP PROGRAM == OBJECTS THAT SEND/RECEIVE MESSAGES ! */

//TODO: 1) exit/enter -> visitor trades
//      2) Elevator
//      3) Na mpainoun sto ktirio panw apo 1 episkeptes
// isws i enter prepei na ginei bool wste n kseroume an to enter itan successful
// opt == optional

#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

/* ============================= */ 
/* [Harry] Finished class */
class visitor
{
  int floor;
  int office_num;
  int priority; 
  bool is_satisfied;
public:
  visitor(int fl, int off);
  void set_priority(int);
  int get_priority();
  int get_office_num();
  int get_floor();
};

visitor::visitor(int fl, int off){
  floor = fl;
  office_num = off;
  is_satisfied = false;
}

void visitor::set_priority(int pr){ priority = pr; }

int visitor::get_priority()  { return priority; }
int visitor::get_office_num(){ return office_num; }
int visitor::get_floor()     { return floor; }


/* ============================= */
/* [Harry] TODO: Check whether curr is needed (and we're done here) */
class waiting_room
{
  int curr;
  queue<visitor*> visitors;  
public:
  waiting_room();    /* Waiting room does not have maximum capacity */
  ~waiting_room();
  void enter(visitor*);
  visitor* exit(); 
  int get_curr();
};

void waiting_room::enter(visitor* vst) {
  curr++;
  visitors.push(vst);
  return;
}

visitor* waiting_room::exit() {
  visitor* vst=visitors.front();
  visitors.pop();
  curr--;
  return vst;
}

int waiting_room::get_curr(){ return curr; }

waiting_room::waiting_room() {
  curr = 0;
}

waiting_room::~waiting_room(){ 
  cout << "End of waiting people!\n";
}
// CARE: mh metrame sto sum tous an8rwpous sto wr or smthg
/* ============================= */
class ground_level
{
  int cap;
  int curr;
  building* bld;  //[Harry] Questionable alla to kratame & vlepoume
  elevator* el;
public:
  waiting_room* wr;   // [Spiros] Des elevator line 291
  ground_level(int Ng);
  ~ground_level();
  bool enter(visitor*); //[Harry] TODO: bool + capacity check 
  visitor* exit(visitor*); 
  void wait(visitor*); //metaferei ton visitor sto wr 
  int get_cap();
  int get_curr();
};
int ground_level::get_cap() { return cap; }
int ground_level::get_curr(){ return curr; }

bool ground_level::enter(visitor* vst) {
  if (curr == cap)
    return false;
  curr++;
  wait(vst);
  return true;
}

/* [Harry] den katalavainw tpt apo ta comments alla dn mou paei h kardia na ta svisw. Kane mia ekka8arish otan mporeis x] */
void ground_level::wait (visitor* vst) {
  // if (el->enter(vst))                   // [Spiros] An mpei sto elevator tote eimai ok
  //   cout<< "Visitor in the lift.\n";        
  // else {
    wr->enter(vst);                       // [Spiros] Alliws ton bazw sthn anamonh mexri --> thn epomenh gura tou elev <-- TODO 
    //cout << "You are not allowed to enter !\n"; 
  //} return;
}

void ground_level::exit(visitor *vst){
  --curr;
  bld->exit(vst);
}

ground_level::ground_level (int Ng,elevator* elev,building* bldg) {
  cap  = Ng; 
  curr = 0;
  wr  = new waiting_room;
  el  = elev;
  bld = bldg;
  cout << "The Entrance has been created!\n";
}

ground_level::~ground_level(){ 
  delete wr;
  cout << "End of service!\n";
}
/* ============================= */
// TODO: 1) decide whether cap is needed [Harry] idk why I put this here :wheelchair:
//       2) decide how2communicate w/ waiting rooms
class office
{
  int number;
  int cap;
  int total; // total visitors, used to prioritize ppl (bank-style)
  floor** fl;
  elevator* el;       // [Spiros] Mallon xreiazetai kai edw to elevator gt sto exit paei kateu8eian sto elev
  queue<visitor*> visitors;
public:
  office(int No, int num);
  ~office();
  bool enter(visitor *);
  visitor *exit();
  int get_cap(); // opt?
  bool is_empty();  //[Harry] used in elev::stop_down
};

bool office::is_empty(){ return (visitors.size() == 0) ? true : false; } //[Harry] TODO:check

office::office(int No, int num,floor** flr,elevator* elv){
  cap    = No;
  number = num;
  total  = 0;
  fl=flr;
  el=elv;
  std::cout << "Office #" << number << "has been created" << endl;
}

office::~office(){ 
  while (!visitors.empty()) visitors.pop(); //[Harry] pretty sure that's optional
  std::cout << "End of the work!" << endl;  //[Harry] will delete before finalisation
}

int office::get_cap(){ return cap; }

bool office::enter(visitor *vst){
  ++total;
  vst->set_priority(total);
  if (visitors.size() == cap){
    std::cout << "Please, wait outside for entrance in the office. Your priority is: " << total << endl;
    return false;
  } else {
    visitors.push(vst);
    std::cout << "Entering office #" << number << endl;
    return true;
  }
} 
// [Harry] Resurrected this from the dead  [Spiros] It'll soon return to Davy Jones' locker AGAIN :)
visitor *office::exit(){ 
  visitor *vst = visitors.front();
  vst->is_satisfied=true;
  visitors.pop();
  return vst;  
}

/* ============================= */
// TODO: na knme kati gia tous ppl sto waiting room pou prepei n mpoun sto office
class floor
{
  int number; // [1,4]
  int cap; //opt ? 
  int curr;//opt ?
  waiting_room* wr;
  elevator* el;
  office** off;
public:
  floor(int Nf,int No);
  ~floor();
  bool enter(visitor *);    // [Spiros] bool enter klassika //[Harry] :heart_eyes:
  visitor *exit();
  int get_cap();
  int get_curr();
  office *get_office(int office_n); //[Harry] added this one used on elevator::stop_down
};

office *floor::get_office(int off_n){ return off[off_n-1]; } //[Harry] args from 1-10
int floor::get_cap() { return cap; }
int floor::get_curr(){ return curr; }

bool floor::enter(visitor* vst) {
  
  if (curr < cap) {
    if (off[vst->get_office_num()]->enter(vst) == false)  // An [den] xwraei sto grafeio
      wr->enter(vst);
    curr++;
    return true;
  }
  std::cout << "Sorry, floor number " << number << "is full." << endl;
  std::cout << "Your priority is: "   << vst->get_priority()  << endl;
  return false;
}

// Randomly chooses and returns a person from an office
// Please care about an empty floor
visitor *floor::exit(){
  --curr;
  while(1){
    int i = rand() % 10 + 1;
    if(fl[curr_fl-1]->get_office(i)->is_empty() == false){
      return fl[curr_fl-1]->get_office(i)->exit();
    }
  }
}


floor::floor(int Nf,int No,elevator* elv) {
  cap=Nf; 
  curr=0;
  wr=new waiting_room;
  off=new office*[10];
  for (int i = 0; i < 10; i++) off[i]=new office(No,i);
  el=elv;
}

floor::~floor() {
  delete wr;
  for (int i = 0; i < 10; i++)
    delete off[i];
  delete[] off;
  cout<<"End of service!\n";
}


/* ============================= */
class elevator  //TODO: all of it
{
  int total; // [Harry] used to prioritize ppl as usual
  int cap;
  int curr_fl;
  floor** fl;
  ground_level* grl;
  int curr;
  int crcl_rem;   // circles remaining // ousiastika termatizei th diadikasia
  queue<visitor*> visitors;
  bool enter(visitor*);     // [Spiros] Added bool as a return type
  void exit(int);   // [Spiros] Nomizw eimaste ok an epistrefei void 
 
  void empty_all(); /* //TODO: orismata    // [Spiros] I think we're ok with int // [Harry] No I don't think we are :innocent: */
  void stop_up();
  void stop_down();
public:                          
  elevator(int Nl, int lc, floor **);    
  ~elevator();
  void operate();
  int get_cap();
  int get_curr();
};

// selects visitors ready2leave from the floor and puts them in the elevator
void elevator::stop_down(){
  for (int fl_num = 4; fl_num >= 1; --fl_num)
  {
    int sel = cap - curr;
    for (int i = 0; i < sel && fl[curr_fl-1]->get_curr() > 0; ++i)
    {
      ++curr;
      visitors.push(fl[curr_fl-1]->exit());
    }
  }
}
// [Harry] my comments, no use using the tag on this 1
void elevator::stop_up(){
  for (int cur_fl = 1; cur_fl <= 4; ++cur_fl)
  {
    // this is done so that ppl avoid being stuck eternally in the wr
    for (int i = 0; i < fl[cur_fl-1]->wr->visitors.size(); ++i) // meh meh metavliti syn8iki termatismou // should be slow but still work
    {
      visitor *vst = wr->exit();
      if (fl[cur_fl-1]->off[vst->get_office_num()]->enter(vst) == false) // if they get rejected
        fl[cur_fl-1]->wr->enter(vst);
    }

    for (int i = 0; i < visitors.size(); ++i) //!!care: metavliti syn8iki
    {
      visitor *vst = visitors.front();
      // makes no sense. should add wr check first
      if (!(vst->get_floor() == cur_fl && fl[cur_fl-1]->enter(vst))) // if correct floor -> try to enter
        visitors.push(vst);
      visitor.pop();
    }
  }
}

void elevator::operate() {
  while (crcl_rem--) {
    
  /* [Harry] Kales idees genika, you paved the way for this, sorry pou sou esvisa kwdika :< */

    while (curr <= cap && grl->wr->get_curr()){ // while not cap + has ppl w8ting
      enter(grl->wr->exit()); // val'tous olous apo isogeio //TODO: this, but on floorz
    }
    
    stop_up();
    stop_down();
    empty_all();
  }
}

bool elevator::enter(visitor* vst) {
  vst->set_priority(++total);
  if (curr<cap) {
    visitors.push(vst);
    curr++;
    std::cout << "Visitor in the lift!" << endl;
    return true;
  }
  std::cout << "You are not allowed to enter!\n" << "Your priority is: " 
            << vst->get_priority() << endl; 
  return false;
}


void elevator::exit(visitor *vst) {
  --curr;
  grl->exit(vst);
}



// calls elevator::exit on every satisfied client inside the lift
void elevator::empty_all() {
  for (int i = 0; i < visitors.size() ; i++) 
  {
    visitor *vst = visitors.front();
    if (!(vst->is_satisfied))
      visitors.push(vst);  
    else
      exit(vst);
    
    visitors.pop();
  }
}

int elevator::get_cap() { return cap; }
int elevator::get_curr(){ return curr; }

elevator::elevator(int Nl, int l_circl, floor **fl_arr,ground_level* grlvl) {
  fl  = fl_arr;
  cap = Nl; 
  curr  = 0;
  total = 0;
  curr_fl  = 0;    // Initially , the floor is 0
  crcl_rem = l_circl;
  grl=grlvl;
}

elevator::~elevator() {
  while (!visitors.empty()) visitors.pop(); //opt
  cout << "No more ups and downs!\n";
}

/* ============================= */
//TODO: 1) check whether el is needed
//      2) it's ready (?)
class building
{
  int cap;  /* capacity */
  int curr; /*  current ppl inside */
  ground_level* gr_lvl;
  floor** fl;  // Floor pointer (create floors dynamically during construction)
public:
  elevator* el;  //[Harry] ?? // [Spiros] Made it public in order to do stuff in main (operate)
  building(int N, int Nf, int Ng, int No, int Nl, int lc);  
  ~building();                                
  void enter(visitor *);
  void exit(visitor *);
};

void building::enter (visitor* vst) {
  if ((curr == cap) || gr_lvl->enter(vst) == false)
    std::cout << "Please, come tomorrow." << endl;
  else {
    curr++;
    cout << "A new customer wants to go to floor " << vst->get_floor()
         << " and office " << vst->get_office_num() << endl; //debug printf
  }
}

void building::exit(visitor *vst){
  --curr;
  std::cout << "\"OOF, I FINALLY FINISHED! BEST DAY EVER!\"  -" 
            << "FL: " << vst->get_floor() << "OF: " << vst->get_office_num()
            << "PR: " << vst->get_priority() << endl; //debug printf
}

building::building(int N, int Nf, int Ng, int No, int Nl, int l_circl) {
  cap=N; 
  curr=0;
  cout<< "A new building is ready for serving citizens!\n\n";
  ground=new ground_level(Ng);
  cout<< "A Floor has been created with number 0!\n";
  fl=new floor*[4];
  for (int i = 0; i < 4; i++) {
    fl[i]=new floor(Nf,No);
    cout<<"A Floor has been created with number "<<i+1<<"!\n";
  }
  el=new elevator(Nl, l_circl, fl);
  cout<<"A lift has been created!\n";
}

building::~building() {
  delete el;
  for (int i = 0; i < 4; i++)
    delete fl[i];
  delete[] fl;
  delete ground;
  cout<<"Service not available any longer. Go elsewhere!\n";
}

/* ============================= */


int main(int argc, char const *argv[])
{
  if (argc != 8) {  /* Error check */
    std::cerr << "\nUsage:\n" << argv[0] 
    << " <max_cap> <floor_cap> <ground_cap> <office_cap> <elevator_cap>" 
    << " <number_of_visitors> <elevator_circles>\n" << endl;
    exit(EXIT_FAILURE); 
  }

  int max_cap = atoi(argv[1]);
  int cap_flr = atoi(argv[2]);
  int cap_grd = atoi(argv[3]);
  int cap_off = atoi(argv[4]);
  int cap_elv = atoi(argv[5]);
  int num_vst = atoi(argv[6]);
  int l_circl = atoi(argv[7]);
  
  /* Generate visitors required */
  srand(45);
  visitor **ppl = new visitor *[num_vst];
  for (int i = 0; i < num_vst; ++i)
  {
    int fl  = rand() % 4  + 1;  // opt: den exei kalh diaspora
    int off = rand() % 11 + 1; 
    ppl[i]  = new visitor(fl, off);
  }

  /* Create a building, visitors attempt to enter */
  building *service = new building(max_cap, cap_flr, cap_grd, cap_off, cap_elv, l_circl);

  for (int i = 0; i < num_vst; ++i) {
    service->enter(ppl[i]);           // Get one person in (building->ground_level->waiting_room)
    service->el->operate();           // Operate 
  }


  /* Cleanup section */
  delete service;

  for (int i = 0; i < num_vst; ++i)
    delete ppl[i];
  delete[] ppl;

  return 0;
}
