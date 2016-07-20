#include <iostream>
#include "Simulation.hh"

int	main() {
  try {
    // create the simulation
    Simulation simulation;

    // run it
    simulation.run();
  }
  catch (const char *ex) {
    std::cerr << "[Error]: " << ex << std::endl;
    return -1;
  }
  return 0;
}
