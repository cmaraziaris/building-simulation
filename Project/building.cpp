#include "classes.h"

/* ============================================||  V I S I T O R   F U N C T I O N S  ||============================================ */ 

visitor::visitor(int fl, int off){
  floor = fl;
  office_num = off;
  is_satisfied = false;
}

void visitor::set_satisfaction(bool sat) { is_satisfied = sat; }

void visitor::set_priority(int pr) { priority = pr; }

bool visitor::get_satisfaction() { return is_satisfied; }

int visitor::get_priority() { return priority; }

int visitor::get_office_num() { return office_num; }

int visitor::get_floor()  { return floor; }

/* ============================================||  W A I T I N G    R O O M    F U N C T I O N S  ||============================================ */ 

void waiting_room::enter(visitor* vst) {
  curr++;
  visitors.push(vst);
}

visitor* waiting_room::exit() {
  visitor* vst=visitors.front();
  visitors.pop();
  curr--;
  return vst;
}

queue<visitor*> waiting_room::get_vst(void) { return visitors; }

int waiting_room::get_curr() { return curr; }

waiting_room::waiting_room() { curr = 0; }

waiting_room::~waiting_room() {  std::cout << "End of waiting people!\n"; }

/* ============================================||  G R O U N D   L E V E L   F U N C T I O N S  ||============================================ */ 
// CARE: mh metrame sto sum tous an8rwpous sto wr or smthg

waiting_room* ground_level::get_wr(void) { return wr; }

int ground_level::get_cap() { return cap; }

int ground_level::get_curr() { return curr; }

bool ground_level::enter(visitor* vst) {
  if (get_curr() == get_cap())
    return false;
  curr++;
  wait(vst);
  return true;
}

void ground_level::wait (visitor* vst) { wr->enter(vst); }

void ground_level::exit(visitor *vst){
  --curr;
  bld->exit(vst);
}

ground_level::ground_level (int Ng, building* bldg) {
  cap  = Ng; 
  curr = 0;
  wr  = new waiting_room;
  bld = bldg;
  std::cout << "The Entrance has been created!\n";
}

ground_level::~ground_level(){ 
  delete wr;
  std::cout << "End of service!\n";
}

/* ============================================||  O F F I C E   F U N C T I O N S  ||============================================ */ 

bool office::is_empty(){ return (visitors.size() == 0) ? true : false; } 

office::office(int No, int num) {
  cap    = No;
  number = num;
  total  = 0;
  std::cout << "Office #" << number << " has been created" << endl;
}

office::~office() { 
  while (!visitors.empty()) visitors.pop(); //[Harry] pretty sure that's optional
  std::cout << "End of the work!" << endl;  //[Harry] will delete before finalisation
}

int office::get_cap(){ return cap; }

bool office::enter(visitor *vst) {
  ++total;
  vst->set_priority(total);
  if (visitors.size() == (unsigned int)(get_cap())){
    std::cout << "Please, wait outside for entrance in the office. Your priority is: " << total << endl;
    return false;
  } else {
    visitors.push(vst);
    std::cout << "Entering office #" << number << endl;
    return true;
  }
} 

visitor *office::exit() { 
  visitor *vst = visitors.front();
  vst->set_satisfaction(true);
  visitors.pop();
  return vst;  
}

/* ============================================||  F L O O R   F U N C T I O N S  ||============================================ */ 

waiting_room* floor::get_wr(void) { return wr; }

office *floor::get_office(int off_n){ return off[off_n-1]; } //[Harry] args from 1-10

int floor::get_cap() { return cap; }

int floor::get_curr() { return curr; }

bool floor::enter(visitor* vst) {
  if (get_curr() < get_cap()) {
    if (get_office(vst->get_office_num())->enter(vst) == false)  // An [den] xwraei sto grafeio
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
visitor *floor::exit() {
  --curr;
  while(1){
    int i = rand() % 10 + 1;
    if( get_office(i)->is_empty() == false ) {
      return get_office(i)->exit();
    }
  }
}

floor::floor(int Nf,int No) {
  cap=Nf; 
  curr=0;
  wr=new waiting_room;
  off=new office*[10];
  for (int i = 0; i < 10; i++) off[i]=new office(No,i+1);
}

floor::~floor() {
  delete wr;
  for (int i = 0; i < 10; i++)
    delete off[i];
  delete[] off;
  std::cout<<"End of service!\n";
}

/* ============================================||  E L E V A T O R   F U N C T I O N S  ||============================================ */ 

// selects visitors ready2leave from the floor and puts them in the elevator
void elevator::stop_down() {
  for (int fl_num = 4; fl_num >= 1; --fl_num)
  {
    std::cout<<"Going down to floor "<<fl_num<<endl;
    int sel = get_cap() - get_curr();
    for (int i = 0; i < sel && fl[fl_num-1]->get_curr() > 0; ++i)
    {
      ++curr;
      visitors.push(fl[fl_num-1]->exit());
    }
  }
}

// [Harry] my comments, no use using the tag on this 1
void elevator::stop_up() {
  for (int cur_fl = 1; cur_fl <= 4; ++cur_fl)
  {
    std::cout<<"Going up to floor "<<cur_fl<<endl;
    // this is done so that ppl avoid being stuck eternally in the wr
    for (int i = 0, max = fl[cur_fl-1]->get_wr()->get_vst().size(); i < max; ++i)
    {
      visitor *vst = fl[cur_fl-1]->get_wr()->exit();
      office *off =fl[cur_fl-1]->get_office(vst->get_office_num());
      if (off->enter(vst) == false) // if they get rejected
        fl[cur_fl-1]->get_wr()->enter(vst);
    }

    for (int i = 0, max = visitors.size(); i < max; ++i)
    {
      visitor *vst = visitors.front();
      if (!(vst->get_floor() == cur_fl && fl[cur_fl-1]->enter(vst)))   // if correct floor -> try to enter
        visitors.push(vst);
      else  curr--;
      visitors.pop();
    }
  }
}

void elevator::operate() {
  while (crcl_rem--) {
    while (get_curr() < get_cap() && grl->get_wr()->get_curr()){ // while not cap + has ppl w8ting
      visitor* vst=grl->get_wr()->exit();
      if(!enter(vst))                             // val'tous olous apo isogeio
        grl->get_wr()->enter(vst);                // Stin periptwsh pou den mpei sto asanser, 3anavalton mesa sto grl 
    }                                               
    stop_up();
    stop_down();
    empty_all();
  }
}

bool elevator::enter(visitor* vst) {
  vst->set_priority(++total);
  if (get_curr() < get_cap()) {
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
  for (unsigned int i = 0; i < visitors.size() ; i++) 
  { 
    visitor *vst = visitors.front();
    if (vst->get_satisfaction() == false)
      visitors.push(vst);  
    else 
      exit(vst);
    
    visitors.pop();
  }
}

int elevator::get_cap() { return cap; }

int elevator::get_curr() { return curr; }

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
  std::cout << "No more ups and downs!\n";
}

/* ============================================||  B U I L D I N G   F U N C T I O N S  ||============================================ */ 

ground_level* building::get_gr_lvl(void) { return gr_lvl; }

elevator* building::get_elevator(void) { return el; }

void building::enter (visitor* vst) {
  if ((curr == cap) || gr_lvl->enter(vst) == false)
    std::cout << "Please, come tomorrow." << endl;
  else {
    curr++;
    std::cout << "A new customer wants to go to Floor " << vst->get_floor()
         << " and Office " << vst->get_office_num() << endl; 
  }
}

void building::exit(visitor *vst) {
  --curr;
  std::cout << "\"OOF, I FINALLY FINISHED! BEST DAY EVER!\"  -" 
            << "FL: " << vst->get_floor() << "  OF: " << vst->get_office_num()
            << "  PR: " << vst->get_priority() << endl;
}

building::building(int N, int Nf, int Ng, int No, int Nl, int l_circl) {
  cap=N; 
  curr=0;
  std::cout<< "A new building is ready for serving citizens!\n\n";
  gr_lvl=new ground_level(Ng, this);
  std::cout<< "A Floor has been created with number 0!\n";
  fl=new floor*[4];
  for (int i = 0; i < 4; i++) {
    fl[i]=new floor(Nf,No);
    std::cout<<"A Floor has been created with number "<<i+1<<"!\n";
  }
  el=new elevator(Nl, l_circl, fl,gr_lvl);
  std::cout<<"A lift has been created!\n";
}

building::~building() {
  delete el;
  for (int i = 0; i < 4; i++)
    delete fl[i];
  delete[] fl;
  delete gr_lvl;
  std::cout<<"Service not available any longer. Go elsewhere!\n";
}