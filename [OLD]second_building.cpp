/* ! CPP PROGRAM == OBJECTS THAT SEND/RECEIVE MESSAGES ! */

//TODO: 1) exit/enter -> visitor trades
//      2) Elevator
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
}

void visitor::set_priority(int pr){ priority = pr; }

int visitor::get_priority()  { return priority; }
int visitor::get_office_num(){ return office_num; }
int visitor::get_floor()     { return floor; }


/* ============================= */
class waiting_room
{
  int curr;
  queue<visitor*> visitors;  
public:
  waiting_room();                           /* Waiting room does not have maximum capacity */
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
  curr=0;
}

waiting_room::~waiting_room(){ 
  while (!visitors.empty()) visitors.pop(); // opt?
  cout << "End of waiting people!\n";
}

/* ============================= */
class ground_level
{
  int cap;
  int curr;
  waiting_room* wr; // TODO: orismata gia init
  //elevator *el; //[Harry] ADDED: so it will communicate w/ the elev, instead of args
public:
  ground_level(int Ng);
  ~ground_level();
  void enter(visitor*);
  void exit(visitor*);  //[Harry][Questionable argument] Epistrefei void afou meta to ground level bgainei e3w 
  void wait(visitor*); //metaferei ton visitor sto wr 
  int get_cap();
  int get_curr();
};
int ground_level::get_cap() { return cap; }
int ground_level::get_curr(){ return curr; }

void ground_level::enter(visitor* vst) {  //[Harry] deleted additional arg; added @private
  curr++;
  wait(vst);
}

void ground_level::wait (visitor* vst) {//[Harry] deleted additional arg; added @private
  wr->enter(vst);
}

ground_level::ground_level (int Ng) {
  cap=Ng; curr=0;
  wr=new waiting_room;
  cout<<"The Entrance has been created!\n";
}

ground_level::~ground_level(){ 
  delete wr;
  cout << "End of service!\n";
}
/* ============================= */
// TODO: 1) decide whether cap is needed 
//       2) decide how2communicate w/ waiting rooms
class office
{
  int number;
  int cap;
  int total; // total visitors, used to prioritize ppl (bank-style)
  queue<visitor*> visitors;
public:
  office(int No, int num);
  ~office();
  bool enter(visitor *);
  visitor *exit();
  int get_cap(); // opt?
};

office::office(int No, int num){
  cap    = No;
  number = num;
  total  = 0;
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

visitor *office::exit(){ 
  visitor *vst = visitors.front();
  visitors.pop();
  return vst;    
}

/* ============================= */
class floor
{
  int cap; //opt ? 
  int curr;//opt ?
  waiting_room* wr;
  office** off;
public:
  floor(int Nf,int No);  // To floor einai o monos tropos na ftia3eis grapheio epomenws pernas kai to No san orisma
  ~floor();
  void enter(visitor *);
  visitor *exit();
  int get_cap();
  int get_curr();
};

int floor::get_cap() { return cap; }
int floor::get_curr(){ return curr; }

floor::floor(int Nf,int No) {
  cap=Nf; 
  curr=0;
  wr=new waiting_room;
  off=new office*[10];
  for (int i = 0; i < 10; i++) off[i]=new office(No,i);
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
  int cap;
  int curr_fl;
  floor** fl;
  int curr;
  int crcl_rem;   // circles remaining // ousiastika termatizei th diadikasia
  queue<visitor*> visitors;
  void enter(visitor*);
  visitor* exit();
  void stop_up();   //TODO: orismata  // [Spiros] Orisma : (curr_fl++)%4 etsi wste na 3eroume ton orofo ka8e fora
  void stop_down(); //TODO: orismata  //  -//-
  void empty_all(); //TODO: orismata  // [Spiros] Orisma : void , Epistrofh : int (ousiastika 8a kanei delete olous tous  
public:                          // satisfied visitors) kai epistrefei ton ari8mo ekeinwn pou e3uphreth8hkan gia na kaneis
  elevator(int Nl, int lc, floor **);    // builiding->current -= tosoi
  ~elevator();
  void operate();
  int get_cap();
  int get_curr();
};

int elevator::get_cap() { return cap; }
int elevator::get_curr(){ return curr; }

elevator::elevator(int Nl, int l_circl, floor **fl_arr) {
  fl = fl_arr;
  cap  = Nl; 
  curr = 0;
  curr_fl  = 0;    // Initially , the floor is 0
  crcl_rem = l_circl;
}

elevator::~elevator() {
  while (!visitors.empty()) visitors.pop(); //opt
  cout << "No more ups and downs!\n";
}

/* ============================= */
class building
{
  int cap;  /* capacity */
  int curr; /*  current ppl inside */
  ground_level* ground;
  floor** fl;  // Floor pointer (create floors dynamically during construction)
  elevator* el;
public:
  building(int N, int Nf, int Ng, int No, int Nl, int lc);  
  ~building();                                
  void enter(visitor*);
  void exit();
};

void building::enter (visitor* vst) {
  if ((curr<cap)&&(ground->get_curr()<ground->get_cap())) { // einai anagkaios nomizw o 2os elegxos , alla check it 
    curr++;
    cout<<"A new customer wants to go to floor "<<vst->get_floor()<<" and office "<<vst->get_office_num()<< endl;
    ground->enter(vst); //[Harry] deleted "el" as additional arg
  }
  else cout<<"Please, come tomorrow.\n";
  return;
}

building::building(int N, int Nf, int Ng, int No, int Nl, int l_circl) {
  cap=N; curr=0;
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

  for (int i = 0; i < num_vst; ++i)
    service->enter(ppl[i]);


  /* Cleanup section */
  delete service;

  for (int i = 0; i < num_vst; ++i)
    delete ppl[i];
  delete[] ppl;

  return 0;
}
