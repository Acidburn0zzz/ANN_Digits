#pragma once

#include "RandomGenerator.hpp"

class Neuron;

class Synapse {
public:
  Synapse(Neuron *input, Neuron *output);
  void	setInput(float inputValue);
  void	updateWeight(float dw);
  float	getInput()				const;
  float	getWeight()				const;
  float	getNextNeuronDelta()			const;
  float	getPrevDelta()				const;

private:
  Neuron	*_input;
  Neuron	*_output;
  float		_inputValue;
  float		_weight;
  float		_prevDelta	= 0;
};
