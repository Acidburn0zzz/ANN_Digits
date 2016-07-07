#include "Synapse.hh"
#include "Neuron.hh"

Synapse::Synapse(Neuron *input, Neuron *output) :
  _input(input), _output(output) {
  RandomGenerator &rng = RandomGenerator::getInstance();
  _weight = rng.d_between(-1, 1);
}

float Synapse::getInput() const {
  return _inputValue;
}

void Synapse::setInput(float inputValue) {
  _inputValue = inputValue;
}

float Synapse::getWeight() const {
  return _weight;
}

void Synapse::updateWeight(float dw) {
  _weight += dw;
  _prevDelta = dw;
}

float Synapse::getPrevDelta() const {
  return _prevDelta;
}

float Synapse::getNextNeuronDelta() const {
  return _output->getDelta();
}
