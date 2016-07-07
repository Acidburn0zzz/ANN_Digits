#include "Network.hh"
#include <iostream>

Network::Network(const std::vector<unsigned int> &layers) :
  _outputLayer(layers.size() - 1) {
  unsigned int i;
  Synapse *s;
  Neuron *n;

  for (i = 0; i < layers.size(); i++)
    _layers.push_back(Layer(layers[i]));
  // create input synapses
  for (i = 0; i < _layers[0].getNeuronNb(); i++) {
    n = _layers[0][i];
    s = new Synapse(nullptr, n);
    n->addInput(s);
  }
  // create output synapses
  for (i = 0; i < _layers[_outputLayer].getNeuronNb(); i++) {
    n =  _layers[_outputLayer][i];
    s = new Synapse(n, nullptr);
    n->addOutput(s);
  }
}

void Network::fullyConnect(unsigned int l1, unsigned int l2) {
  unsigned int i, j;
  Neuron *n1, *n2;

  for (i = 0; i < _layers[l1].getNeuronNb(); i++) {
    n1 = _layers[l1][i];
    for (j = 0; j < _layers[l2].getNeuronNb(); j++) {
      n2 = _layers[l2][j];
      Synapse *s = new Synapse(n1, n2);
      n1->addOutput(s);
      n2->addInput(s);
    }
  }
}

std::vector<double> Network::feed(const std::vector<double> &inputs) {
  std::vector<double> outputs;
  unsigned int i, j;

  if (inputs.size() != _layers[0].getNeuronNb())
    return outputs;

  for (i = 0; i < _layers[0].getNeuronNb(); i++)
    _layers[0][i]->setInputValue(inputs[i]);

  for (i = 0; i < _layers.size(); i++)
    for (j = 0; j < _layers[i].getNeuronNb(); j++)
      _layers[i][j]->fire();

  for (i = 0; i < _layers[_outputLayer].getNeuronNb(); i++)
    outputs.push_back(_layers[_outputLayer][i]->getOutputValue());
  return outputs;
}

void Network::backpropagation(const std::vector<double> &expectedOutput) {
  unsigned int l, n, i, o;
  Synapse *s;
  float output, delta;
  float dw;

  for (n = 0; n < _layers[_outputLayer].getNeuronNb(); n++) {
    output = _layers[_outputLayer][n]->getOutputValue();
    _layers[_outputLayer][n]->setDelta(output * (1 - output) * (expectedOutput[n] - output));
  }

  for (l = _layers.size() - 2; l > 0; l--) {
    for (n = 0; n < _layers[l].getNeuronNb(); n++) {
      delta = 0;
      for (o = 0; o < _layers[l][n]->getOutputNb(); o++) {
	s = _layers[l][n]->getOutput(o);
	delta += s->getWeight() * s->getNextNeuronDelta();
      }
      output = _layers[l][n]->getOutputValue();
      _layers[l][n]->setDelta(output * (1 - output) * delta);
    }
  }

  for (l = 1; l < _layers.size(); l++)
    for (n = 0; n < _layers[l].getNeuronNb(); n++)
      for (i = 0; i < _layers[l][n]->getInputNb(); i++) {
	s = _layers[l][n]->getInput(i);
	dw = _learningRate * s->getInput() * _layers[l][n]->getDelta();
	dw += _momentum * s->getPrevDelta();
	s->updateWeight(dw);
      }
}
