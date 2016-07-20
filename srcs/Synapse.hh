#pragma once

#include "RandomGenerator.hpp"

class Neuron;

class Synapse {
public:
  /*
  ** Synapse constructor - set input and output neuron and randomly initialize its weight
  ** @param input: the neuron used as input
  ** @param output: the neuron used as output
  */
  Synapse(Neuron *input, Neuron *output);

  /*
  ** Set the input value in the synapse
  **
  ** @param inputValue: The value to set as input
  */
  void		setInput(float inputValue);

  /*
  ** Update the synapse weight (so update a neuron input weight)
  **
  ** @param dw: change in the weight
  */
  void		updateWeight(float dw);

  /*
  ** Get the current input value
  **
  ** @return: the current input value
  */
  float		getInput()		const;

  /*
  ** Get the current weight
  **
  ** @return: the current weight value
  */
  float		getWeight()		const;

  /*
  ** get the delta of the next neuron (delta of the output neuron)
  **
  ** @return: the change in the weight of the next neuron
  */
  float		getNextNeuronDelta()	const;

  /*
  ** get the delta of the previous neuron (delta of the input neuron)
  **
  ** @return: the change in the weight of the previous neuron
  */
  float		getPrevDelta()		const;

private:
  // Neuron used as input
  Neuron	*_input;
  // Neuron used as output
  Neuron	*_output;
  // current input value
  float		_inputValue;
  // current neuron weight
  float		_weight;
  // previous delta value
  float		_prevDelta	= 0;
};
