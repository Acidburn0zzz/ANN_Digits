#pragma once

#include "Layer.hh"

class Network {
public:
  Network(const std::vector<unsigned int> &layers);
  std::vector<double>	feed(const std::vector<double> &inputs);
  void			fullyConnect(unsigned int l1, unsigned int l2);
  void			backpropagation(const std::vector<double> &expectedOutput);

private:
  float			_learningRate	= 0.09; // 0.1
  float			_momentum	= 0.01; // 0
  float			_outputLayer;
  std::vector<Layer>	_layers;
};
