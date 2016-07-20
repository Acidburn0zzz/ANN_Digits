#pragma once

#include <vector>

#include "Neuron.hh"

class Layer {
public:
  /*
  ** Create a Layer of neuronNb neurons
  **
  ** @param neuronNb: number of neuron to create in the layer
  */
  Layer(unsigned int neuronNb);

  /*
  ** Get the neuron "id" from the layer
  **
  ** @param id: id of the neuron to get
  ** @return the pointer to the neuron "id"
  */
  Neuron	*operator[](unsigned int id);

  /*
  ** Get the number of neuron in the layer
  **
  ** @return the number of neurons in the layer
  */
  unsigned int	getNeuronNb()			const;

private:
  // vector of neurons
  std::vector<Neuron>	_neurons;
};
