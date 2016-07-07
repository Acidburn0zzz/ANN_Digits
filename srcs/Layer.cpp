#include "Layer.hh"

Layer::Layer(unsigned int neuronNb) {
  for (unsigned int i = 0; i < neuronNb; i++)
    _neurons.push_back(Neuron());
}

Neuron *Layer::operator[](unsigned int id) {
  return &_neurons[id];
}

unsigned int Layer::getNeuronNb() const {
  return _neurons.size();
}
