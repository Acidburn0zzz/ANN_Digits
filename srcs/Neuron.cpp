#include "Neuron.hh"

void		Neuron::addInput(Synapse *input) {
  _inputs.push_back(input);
}

void		Neuron::addOutput(Synapse *output) {
  _outputs.push_back(output);
}

// only used by input layers
void		Neuron::setInputValue(float inputValue) {
  _inputs[0]->setInput(inputValue);
}

// only used by output layer
float		Neuron::getOutputValue() const {
  return _outputs[0]->getInput();
}

void		Neuron::setDelta(float delta) {
  _delta = delta;
}

void		Neuron::fire() {
  double	netInput = 0, outputValue;

  for (const auto &iSynapse : _inputs)
    netInput += iSynapse->getInput() * iSynapse->getWeight();
  //netInput += -1;//_bias;
  outputValue = sigmoid(netInput);
  for (const auto &oSynapse : _outputs)
    oSynapse->setInput(outputValue);
}

double		Neuron::sigmoid(double netInput) const {
  return 1.0 / (1.0 + std::exp(-netInput));
}

float		Neuron::getDelta() const {
  return _delta;
}

unsigned int	Neuron::getOutputNb() const {
  return _outputs.size();
}

unsigned int	Neuron::getInputNb() const {
  return _inputs.size();
}

Synapse		*Neuron::getInput(unsigned int synapseId) {
  return synapseId > _inputs.size() ? nullptr : _inputs[synapseId];
}

Synapse		*Neuron::getOutput(unsigned int synapseId) {
  return synapseId > _outputs.size() ? nullptr : _outputs[synapseId];
}
