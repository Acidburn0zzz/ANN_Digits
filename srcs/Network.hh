#pragma once

#include "Layer.hh"

class Network {
public:
  /*
  ** Network constructor - create layers.size() layers
  **
  ** @param layers: vector of unsigned int describing the number of neurons in each layer
  */
  Network(const std::vector<unsigned int> &layers);

  /*
  ** Get the output of the neural network according to an input
  **
  ** @param inputs: list of data to give to the network
  ** @return: the outputs corresponding to the input or an empty vector if inputs are not valid
  */
  std::vector<double>	feed(const std::vector<double> &inputs);

  /*
  ** Connect each neuron of layer l1 with each neuron of layer l2
  **
  ** @param l1: id of first layer
  ** @param l2: id of second layer
  ** @return: whether the operation has succeeded
  */
  bool			fullyConnect(unsigned int l1, unsigned int l2);

  /*
  ** Correct the weights in the network depending on the expectedOutput
  **
  ** @param expectedOutput: vector of outputs normally expected
  */
  void			backpropagation(const std::vector<double> &expectedOutput);

private:
  // rate at which the network correct itself
  float			_learningRate	= 0.09;
  // keep a portion of the precedent weights during learning
  float			_momentum	= 0.02;
  // id of the output layer
  unsigned int		_outputLayer;
  // vector of existing layers
  std::vector<Layer>	_layers;
};
