#include "Network.hh"
#include <iostream>

Network::Network(const std::vector<unsigned int> &layers) :
  _outputLayer(layers.size() - 1) {
  unsigned int	i;
  Synapse	*s;
  Neuron	*n;

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

bool		Network::fullyConnect(unsigned int l1, unsigned int l2) {
  unsigned int	i, j;
  Neuron	*n1, *n2;

  if (l1 >= _layers.size() || l2 >= _layers.size())
    return false;
  for (i = 0; i < _layers[l1].getNeuronNb(); i++) {
    n1 = _layers[l1][i];
    for (j = 0; j < _layers[l2].getNeuronNb(); j++) {
      n2 = _layers[l2][j];
      Synapse *s = new Synapse(n1, n2);
      n1->addOutput(s);
      n2->addInput(s);
    }
  }
  return true;
}

std::vector<double>	Network::feed(const std::vector<double> &inputs) {
  std::vector<double>	outputs;
  unsigned int		i, j;

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

void		Network::backpropagation(const std::vector<double> &expectedOutput) {
  unsigned int	l, n, i, o;
  Synapse	*s;
  float		output, delta, dw;

  // for each neuron in the output layer
  for (n = 0; n < _layers[_outputLayer].getNeuronNb(); n++) {
    // get its output value
    output = _layers[_outputLayer][n]->getOutputValue();
    // compute the change in the weights depending on the output and the expected output
    _layers[_outputLayer][n]->setDelta(output * (1 - output) * (expectedOutput[n] - output));
  }

  // for each hidden layer
  for (l = _layers.size() - 2; l > 0; l--) {
    // for each neuron in the hidden layer
    for (n = 0; n < _layers[l].getNeuronNb(); n++) {
      delta = 0;
      // for each neuron output synapse in the hidden layer
      for (o = 0; o < _layers[l][n]->getOutputNb(); o++) {
	// get one output synapse
	s = _layers[l][n]->getOutput(o);
	// compute the change in th neuron weight depending on its current weight and the change in the previous layer
	delta += s->getWeight() * s->getNextNeuronDelta();
      }
      // get the neuron output value
      output = _layers[l][n]->getOutputValue();
      // compute the change in its weight
      _layers[l][n]->setDelta(output * (1 - output) * delta);
    }
  }

  // for each layer exepted the input layer
  for (l = 1; l < _layers.size(); l++)
    // for each neuron
    for (n = 0; n < _layers[l].getNeuronNb(); n++)
      // for each input synapse
      for (i = 0; i < _layers[l][n]->getInputNb(); i++) {
	// get a synapse
	s = _layers[l][n]->getInput(i);
	// compute the new weight value
	dw = _learningRate * s->getInput() * _layers[l][n]->getDelta();
	// add a sample of the neuron experiment in the weight change
	dw += _momentum * s->getPrevDelta();
	// and finally update the weight
	s->updateWeight(dw);
      }
}
