#pragma once

#include <vector>

#include "Neuron.hh"

class Layer {
public:
  Layer(unsigned int neuronNb);
  Neuron	*operator[](unsigned int id);
  unsigned int	getNeuronNb()			const;

private:
  std::vector<Neuron>	_neurons;
};
