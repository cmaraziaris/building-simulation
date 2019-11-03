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
  unsigned int get_priority();
  short get_office_num();
  short get_floor();
  void set_satisfaction(const bool);
  bool get_satisfaction(); 
};

/* ===========================================================||  W A I T I N G    R O O M  ||=========================================================== */

class waiting_room
{
  unsigned int curr;  /* Waiting room does not have maximum capacity */
  std::queue<visitor*> visitors;  
public:
  waiting_room();
  ~waiting_room();
  void enter(visitor*);
  visitor* exit(); 
  unsigned int get_curr();
  std::queue<visitor*> get_vst();
};

/* ===========================================================||  G R O U N D   L E V E L  ||=========================================================== */

class ground_level
{
  const unsigned int cap;
  unsigned int curr;
  building* const bld;  
  waiting_room* wr;
public:
  ground_level(const int Ng, building *const);
  ~ground_level();
  bool enter(visitor*);
  void exit(visitor*);
  void wait(visitor*);
  unsigned int get_cap();
  unsigned int get_curr();
  waiting_room* get_wr();
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
  unsigned int get_cap();
  bool is_empty();  //[Harry] used in elev::stop_down
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
  unsigned int get_cap();
  unsigned int get_curr();
  waiting_room * get_wr();
  office *get_office(const short office_n); //[Harry] added this one used on elevator::stop_down
};

/* ===========================================================||  E L E V A T O R  ||=========================================================== */

class elevator
{
  const unsigned int cap;
  floor **const fl;
  ground_level *const grl;
  unsigned int curr;
  unsigned int crcl_rem;   // circles remaining // ousiastika termatizei th diadikasia
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
  unsigned int get_cap();
  unsigned int get_curr();
};

/* ===========================================================||  B U I L D I N G  ||=========================================================== */

class building
{
  const unsigned int cap;  /* capacity */
  unsigned int curr; /*  current ppl inside */
  ground_level * gr_lvl;
  floor ** fl;  // Floor pointer (create floors dynamically during construction)
  elevator * el;
public:
  building(const unsigned int N, const unsigned int Nf, const unsigned int Ng, const unsigned int No, const unsigned int Nl, const unsigned int lc);  
  ~building();                                
  void enter(visitor *);
  void exit(visitor *);
  elevator * get_elevator();
  ground_level * get_gr_lvl();
};

/* =============================================================||  END OF FILE  ||============================================================== */