#include <iostream>
#include <cstdio>
#include "classes.h"

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
    service->enter(ppl[i]);           // Get EVERY person in (building->ground_level->waiting_room)

  service->get_elevator()->operate();           // Operate 


  /* Cleanup section */
  delete service;

  for (int i = 0; i < num_vst; ++i)
    delete ppl[i];
  delete[] ppl;

  return 0;
}