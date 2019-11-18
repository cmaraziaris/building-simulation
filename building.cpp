
#include <iostream>
#include <cstdio>

#include "classes.h"

using namespace std;

/* ============================================||  V I S I T O R   F U N C T I O N S  ||============================================ */ 

visitor::visitor(const short fl, const short off, const unsigned int pr) 
: floor(fl), office_num(off), priority(pr), is_satisfied(false) {}

void visitor::set_satisfaction(const bool sat) { is_satisfied = sat; }

bool visitor::get_satisfaction() const { return is_satisfied; }

unsigned int visitor::get_priority() const { return priority; }

short visitor::get_office_num() const { return office_num; }

short visitor::get_floor() const { return floor; }


/* ============================================||  W A I T I N G    R O O M    F U N C T I O N S  ||============================================ */ 

waiting_room::waiting_room() : curr(0) {}

waiting_room::~waiting_room() { std::cout << "End of waiting people!\n"; }

void waiting_room::enter(visitor* vst) {
  curr++;
  visitors.push(vst);
}

visitor* waiting_room::exit() {
  visitor* vst=visitors.front();      // Get and return the front visitor in queue
  visitors.pop();
  curr--;
  return vst;
}

queue<visitor*> waiting_room::get_vst(void) const { return visitors; }

unsigned int waiting_room::get_curr() const { return curr; }


/* ============================================||  G R O U N D   L E V E L   F U N C T I O N S  ||============================================ */ 

ground_level::ground_level (const int Ng, building *const bldg)
: cap(Ng), curr(0), bld(bldg) 
{
  wr  = new waiting_room;
  std::cout << "The Entrance has been created!\n";
}

ground_level::~ground_level(){ 
  delete wr;
  std::cout << "End of service!\n";
}

waiting_room* ground_level::get_wr(void) const { return wr; }

unsigned int ground_level::get_cap() const { return cap; }

unsigned int ground_level::get_curr() const { return curr; }

bool ground_level::enter(visitor* vst) {
  if (get_curr() == get_cap())            // If the ground level has as many visitors as its maximum capacity, entry is prohibited
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


/* ============================================||  O F F I C E   F U N C T I O N S  ||============================================ */

office::office(const unsigned int No, const short num) 
: number(num), cap(No)
{ std::cout << "Office #" << number << " has been created\n"; }

office::~office() { std::cout << "End of the work!\n"; }

bool office::is_empty() { return (visitors.size() == 0); } 

unsigned int office::get_cap() const { return cap; }

bool office::enter(visitor *vst) {
  if (visitors.size() == (unsigned int)(get_cap())){
    std::cout << "Please, wait outside for entrance in the office. Your priority is: " << vst->get_priority() << endl;
    return false;
  } else {
    visitors.push(vst);
    std::cout << "Entering office #" << number << endl;
    return true;
  }
} 

visitor *office::exit() { 
  visitor *vst = visitors.front();
  vst->set_satisfaction(true);        //  After the office visit, people are satisfied and ready to leave
  visitors.pop();
  return vst;  
}


/* ============================================||  F L O O R   F U N C T I O N S  ||============================================ */ 

floor::floor(const unsigned int Nf, const unsigned int No, const short num) 
: number(num), cap(Nf), curr(0)
{
  wr=new waiting_room;
  off=new office*[10];
  for (short i = 0; i < 10; i++) off[i]=new office(No,i+1);
}

floor::~floor() {
  delete wr;
  for (short i = 0; i < 10; i++)
    delete off[i];
  delete[] off;
  std::cout<<"End of service!\n";
}

waiting_room* floor::get_wr(void) const { return wr; }

office *floor::get_office(const short off_n) const { return off[off_n-1]; }  

unsigned int floor::get_cap() const { return cap; }

unsigned int floor::get_curr() const { return curr; }

bool floor::enter(visitor *vst) {
  if (get_curr() < get_cap()) {         //  As long as current visitors are less than maximum capacity
    if (get_office(vst->get_office_num())->enter(vst) == false)  // If a visitor cannot have access to his preferred office, he enters the floor's waiting room
      wr->enter(vst); 
    curr++;
    return true;
  }
  std::cout << "Sorry, floor number " << number << " is full." << endl;
  std::cout << "Your priority is: "   << vst->get_priority()  << endl;
  return false;
}

visitor * floor::exit() {   // Randomly chooses and returns a person from an office
  --curr;                   
  while(1){
    short i = rand() % 10 + 1;
    if( get_office(i)->is_empty() == false ) {    // Care about an empty floor 
      return get_office(i)->exit();
    }
  }
}


/* ============================================||  E L E V A T O R   F U N C T I O N S  ||============================================ */ 

elevator::elevator(const unsigned int Nl, const unsigned int l_circl, floor **const fl_arr, ground_level*const  gr_lvl)
: cap(Nl), fl(fl_arr), grl(gr_lvl), curr(0), crcl_rem(l_circl) {}

elevator::~elevator() { std::cout << "No more ups and downs!\n"; }

bool elevator::enter(visitor *vst) {
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

void elevator::stop_down() {
  for (short fl_num = 4; fl_num >= 1; --fl_num)
  {
    floor *flr = fl[fl_num-1];
    std::cout << "Going down to floor " << fl_num  << std::endl;
    unsigned int sel = get_cap() - get_curr();                      // See how many visitors can fit in the elevator each time
    for (unsigned int i = 0; i < sel && (flr->get_curr() != flr->get_wr()->get_curr()); ++i)    //  If the offices have people inside, get them out
    {
      ++curr;
      visitors.push(flr->exit());         //  Push them in the elevator
    }
  }
}

void elevator::stop_up() {
  for (short cur_fl = 1; cur_fl <= 4; ++cur_fl)
  {
    std::cout << "Going up to floor " << cur_fl << std::endl;
    //  This is done, to prevent people from being stuck eternally in the waiting room
    for (unsigned int i = 0, max = fl[cur_fl-1]->get_wr()->get_vst().size(); i < max; ++i)
    {
      visitor *vst = fl[cur_fl-1]->get_wr()->exit();      //  Get them out
      office *off =fl[cur_fl-1]->get_office(vst->get_office_num());
      if (off->enter(vst) == false)   //  But if they get rejected
        fl[cur_fl-1]->get_wr()->enter(vst);   // Put them back in the waiting room
    }

    for (unsigned int i = 0, max = visitors.size(); i < max; ++i)
    {
      visitor *vst = visitors.front();
      if (!(vst->get_floor() == cur_fl && fl[cur_fl-1]->enter(vst)))   // If a visitor's choice is to get in the current floor, he tries to enter
        visitors.push(vst);
      else  curr--;
      visitors.pop();
    }
  }
}

void elevator::operate() {
  while (crcl_rem--) {        //  While elevator circles remaining are non-zero
    while (get_curr() < get_cap() && grl->get_wr()->get_curr()){  //  While current people are less than the elevator's maximum capacity 
      visitor* vst=grl->get_wr()->exit();                                   //   and there are people waiting to get in the elevator
      if(!enter(vst))                                         // Try to put them in
        grl->get_wr()->enter(vst);                            // If not, put them back to the ground level
    }                                               
    stop_up();                                                // Go all the way up 
    stop_down();                                              // Go all the way down
    empty_all();                                              // Let the satisfied visitors leave
  }
}

void elevator::empty_all() {        // Only the satisfied visitors leave the elevator
  for (unsigned int i = 0, max = visitors.size();  i < max; i++)  
  { 
    visitor *vst = visitors.front();
    if (vst->get_satisfaction() == false)                      
      visitors.push(vst);  
    else 
      exit(vst);
    
    visitors.pop();
  }
}

unsigned int elevator::get_cap() const { return cap; }

unsigned int elevator::get_curr() const { return curr; }


/* ============================================||  B U I L D I N G   F U N C T I O N S  ||============================================ */ 

building::building(const unsigned int N, const unsigned int Nf, const unsigned int Ng, const unsigned int No, const unsigned int Nl, const unsigned int l_circl)
: cap(N), curr(0) {
  std::cout << "A new building is ready for serving citizens!\n\n";
  gr_lvl = new ground_level(Ng, this);
  std::cout << "A Floor has been created with number 0!\n";
  fl = new floor*[4];
  for (short i = 0; i < 4; i++) {
    fl[i] = new floor(Nf, No, i+1);
    std::cout << "A Floor has been created with number " << i+1 << "!\n";
  }
  el = new elevator(Nl, l_circl, fl,gr_lvl);
  std::cout << "A lift has been created!\n";
}

building::~building() {
  delete el;
  for (short i = 0; i < 4; i++)
    delete fl[i];
  delete[] fl;
  delete gr_lvl;
  std::cout<<"Service not available any longer. Go elsewhere!\n";
}

void building::enter (visitor* vst) {
  if ((curr == cap) || gr_lvl->enter(vst) == false)
    std::cout << "Please, come tomorrow. P: " << vst->get_priority() << std::endl;
  else {
    curr++;
    std::cout << "A new customer wants to go to Floor " << vst->get_floor()
              << " and Office " << vst->get_office_num() << " with Priority "
              << vst->get_priority() << std::endl; 
  }
}

void building::exit(visitor *vst) {
  --curr;
  std::cout << "\n\"I can't believe I finished!\" - " 
            << "F: " << vst->get_floor() << "  O: " << vst->get_office_num()
            << "  P: " << vst->get_priority() << " " << std::endl;
}

ground_level* building::get_gr_lvl(void) const { return gr_lvl; }

elevator* building::get_elevator(void) const { return el; }

/* ========================================================||  END OF FILE  ||======================================================== */ 