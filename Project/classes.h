/* ___________________________________________________________________________________________________________________________________________ */
/* ===========================================================||  C L A S S E S  ||=========================================================== */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#pragma once

#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

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
  short floor;
  short office_num;
  unsigned int priority; 
  bool is_satisfied;
public:
  visitor(short fl, short off, unsigned int pr);
  unsigned int get_priority();
  short get_office_num();
  short get_floor();
  void set_satisfaction(bool);
  bool get_satisfaction(); 
};

/* ===========================================================||  W A I T I N G    R O O M  ||=========================================================== */

class waiting_room
{
  unsigned int curr;
  queue<visitor*> visitors;  
public:
  waiting_room();    /* Waiting room does not have maximum capacity */
  ~waiting_room();
  void enter(visitor*);
  visitor* exit(); 
  unsigned int get_curr();
  queue<visitor*> get_vst();
};

/* ===========================================================||  G R O U N D   L E V E L  ||=========================================================== */

class ground_level
{
  unsigned int cap;
  unsigned int curr;
  building* bld;  
  waiting_room* wr;
public:
  ground_level(int Ng, building *);
  ~ground_level();
  bool enter(visitor*); 
  void exit(visitor*); 
  void wait(visitor*); //metaferei ton visitor sto wr 
  unsigned int get_cap();
  unsigned int get_curr();
  waiting_room* get_wr();
};

/* ===========================================================||  O F F I C E  ||=========================================================== */

class office
{
  short number;
  unsigned int cap;
  queue<visitor*> visitors;
public:
  office(unsigned int No, short num);
  ~office();
  bool enter(visitor *);
  visitor *exit();
  unsigned int get_cap();
  bool is_empty();  //[Harry] used in elev::stop_down
};

/* ===========================================================||  F L O O R  ||=========================================================== */

class floor
{
  short number; // [1,4]
  unsigned int cap; 
  unsigned int curr;
  waiting_room* wr;
  office** off;
public:
  floor(unsigned int Nf, unsigned int No, short num);
  ~floor();
  bool enter(visitor *);    
  visitor *exit();
  unsigned int get_cap();
  unsigned int get_curr();
  waiting_room* get_wr();
  office *get_office(short office_n); //[Harry] added this one used on elevator::stop_down
};

/* ===========================================================||  E L E V A T O R  ||=========================================================== */

class elevator
{
  unsigned int cap;
  short curr_fl;
  floor** fl;
  ground_level* grl;
  unsigned int curr;
  unsigned int crcl_rem;   // circles remaining // ousiastika termatizei th diadikasia
  queue<visitor*> visitors;
  bool enter(visitor*);     
  void exit(visitor*);   
  void empty_all(); 
  void stop_up();
  void stop_down();
public:                          
  elevator(unsigned int Nl, unsigned int lc, floor **, ground_level*);    
  ~elevator();
  void operate();
  unsigned int get_cap();
  unsigned int get_curr();
};

/* ===========================================================||  B U I L D I N G  ||=========================================================== */

class building
{
  unsigned int cap;  /* capacity */
  unsigned int curr; /*  current ppl inside */
  ground_level* gr_lvl;
  floor** fl;  // Floor pointer (create floors dynamically during construction)
  elevator* el;
public:
  building(unsigned int N, unsigned int Nf, unsigned int Ng, unsigned int No, unsigned int Nl, unsigned int lc);  
  ~building();                                
  void enter(visitor *);
  void exit(visitor *);
  elevator* get_elevator();
  ground_level* get_gr_lvl();
};