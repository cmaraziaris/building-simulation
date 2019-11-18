/* ___________________________________________________________________________________________________________________________________________ */
/* ===========================================================||  C L A S S E S  ||=========================================================== */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#pragma once

#include <queue>

/* Declarations */
class visitor;
class waiting_room;
class floor;
class office;
class ground_level;
class building;
class elevator;

/* ===========================================================||  V I S I T O R  ||=========================================================== */

class visitor 
{
  const short floor;
  const short office_num;
  const unsigned int priority; 
  bool is_satisfied;
public:
  visitor(const short fl, const short off, const unsigned int pr);
  unsigned int get_priority() const;
  short get_office_num() const;
  short get_floor() const;
  void set_satisfaction(const bool);
  bool get_satisfaction() const; 
};

/* ===========================================================||  W A I T I N G    R O O M  ||=========================================================== */

class waiting_room
{
  unsigned int curr;  // Waiting room does not have maximum capacity 
  std::queue<visitor*> visitors;  
public:
  waiting_room();
  ~waiting_room();
  void enter(visitor*);
  visitor* exit(); 
  unsigned int get_curr() const;
  std::queue<visitor*> get_vst() const;
};

/* ===========================================================||  G R O U N D   L E V E L  ||=========================================================== */

class ground_level
{
  const unsigned int cap; // cap  == capacity 
  unsigned int curr;      // curr == current # of people inside 
  building* const bld;  
  waiting_room* wr;
public:
  ground_level(const int Ng, building *const);
  ~ground_level();
  bool enter(visitor*);
  void exit(visitor*);
  void wait(visitor*);
  unsigned int get_cap() const;
  unsigned int get_curr() const;
  waiting_room* get_wr() const;
};

/* ===========================================================||  O F F I C E  ||=========================================================== */

class office
{
  const short number;
  const unsigned int cap;
  std::queue<visitor*> visitors;
public:
  office(const unsigned int No, const short num);
  ~office();
  bool enter(visitor *);
  visitor *exit();
  unsigned int get_cap() const;
  bool is_empty();
};

/* ===========================================================||  F L O O R  ||=========================================================== */

class floor
{
  const short number; // [1,4]
  const unsigned int cap; 
  unsigned int curr;
  waiting_room* wr;
  office** off;
public:
  floor(const unsigned int Nf, const unsigned int No, const short num);
  ~floor();
  bool enter(visitor *);    
  visitor *exit();
  unsigned int get_cap() const;
  unsigned int get_curr() const;
  waiting_room * get_wr() const;
  office *get_office(const short office_n) const;
};

/* ===========================================================||  E L E V A T O R  ||=========================================================== */

class elevator
{
  const unsigned int cap;
  floor **const fl;
  ground_level *const grl;
  unsigned int curr;
  unsigned int crcl_rem;   // Elevator circles remaining 
  std::queue<visitor*> visitors;
  bool enter(visitor *);     
  void exit(visitor *);   
  void empty_all(); 
  void stop_up();
  void stop_down();
public:                          
  elevator(const unsigned int Nl, const unsigned int lc, floor **const, ground_level *const);    
  ~elevator();
  void operate();
  unsigned int get_cap() const;
  unsigned int get_curr() const;
};

/* ===========================================================||  B U I L D I N G  ||=========================================================== */

class building
{
  const unsigned int cap;  
  unsigned int curr;       
  ground_level * gr_lvl;
  floor ** fl;
  elevator * el;
public:
  building(const unsigned int N, const unsigned int Nf, const unsigned int Ng, const unsigned int No, const unsigned int Nl, const unsigned int lc);  
  ~building();                                
  void enter(visitor *);
  void exit(visitor *);
  elevator * get_elevator() const;
  ground_level * get_gr_lvl() const;
};

/* =============================================================||  END OF FILE  ||============================================================== */