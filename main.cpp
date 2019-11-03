#include <iostream>
#include <cstdio>
#include <chrono>
#include "classes.h"
#include <random>

using namespace std;

int main(int argc, char const *argv[])
{
  if (argc != 8) {  /* Error check */
    std::cerr << "\nUsage:\n" << argv[0] 
    << " <max_cap> <floor_cap> <ground_cap> <office_cap> <elevator_cap>" 
    << " <number_of_visitors> <elevator_circles>\n" << std::endl;
    exit(EXIT_FAILURE); 
  }

  unsigned int max_cap = atoi(argv[1]);
  unsigned int cap_flr = atoi(argv[2]);
  unsigned int cap_grd = atoi(argv[3]);
  unsigned int cap_off = atoi(argv[4]);
  unsigned int cap_elv = atoi(argv[5]);
  unsigned int num_vst = atoi(argv[6]);
  unsigned int l_circl = atoi(argv[7]);
#if 0
  /* Generate visitors required */
  mt19937 randomGen(chrono::steady_clock::now().time_since_epoch().count());      //   Waaaay better than rand()
  uniform_int_distribution<short> rnd4(1,4),rnd10(1,10);

  visitor **ppl = new visitor *[num_vst];
  for (unsigned int i = 0; i < num_vst; ++i)
  {
    short fl  = rnd4(randomGen); 
    short off = rnd10(randomGen); 
    ppl[i]  = new visitor(fl, off, i+1);
  }
#else // Useful when debugging; Can recreate results; Will remove before finalisation
  srand(2);
  visitor **ppl = new visitor *[num_vst];
  for (unsigned int i = 0; i < num_vst; ++i)
  {
    short fl  = rand() %  4 + 1; 
    short off = rand() % 10 + 1; 
    ppl[i]  = new visitor(fl, off, i+1);
  }
#endif
  /* Create a building, visitors attempt to enter */
  building *service = new building(max_cap, cap_flr, cap_grd, cap_off, cap_elv, l_circl);

  for (unsigned int i = 0; i < num_vst; ++i)
    service->enter(ppl[i]);           // Get EVERY person in (building->ground_level->waiting_room)

  service->get_elevator()->operate();           // Operate 

  /* Cleanup section */
  delete service;

  for (unsigned int i = 0; i < num_vst; ++i)
    delete ppl[i];
  delete[] ppl;

  return EXIT_SUCCESS;
}