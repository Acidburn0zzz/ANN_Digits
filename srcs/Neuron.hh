#pragma once

#include <vector>
#include <cmath>

#include "Synapse.hh"

class Neuron {
public:
  /*
  ** Add an input Synapse in the neuron
  **
  ** @param input: the Synapse to add as input
  */
  void		addInput(Synapse *input);

  /*
  ** Add an output Synapse in the neuron
  **
  ** @param output: the Synapse to add as output
  */
  void		addOutput(Synapse *output);

  /*
  ** Compute the output value of a neuron depending on its inputs and weights
  */
  void		fire();

  /*
  ** Get the output value of the neuron - only used in case of an output neuron
  **
  ** @return: output value of the neuron
  */
  float		getOutputValue()			const;

  /*
  ** Set the input of the neuron - only used in case of an input neuron
  **
  ** @param inputValue: new input value of the neuron
  */
  void		setInputValue(float inputValue);

  /*
  ** Save the change in the neuron during learning
  **
  ** @param delta: the change in the neuron weight
  */
  void		setDelta(float delta);

  /*
  ** Get the change in the neuron
  **
  ** @return: the change in the neuron
  */
  float		getDelta()				const;

  /*
  ** Get the number of output in the neuron
  **
  ** @return: The number of output in the neuron
  */
  unsigned int	getOutputNb()				const;

  /*
  ** Get the number of input in the neuron
  **
  ** @return: The number of input in the neuron
  */
  unsigned int	getInputNb()				const;

  /*
  ** Get the input Synapse synapseId
  **
  ** @param synapseId: id of the input synapse to get back from the neuron
  ** @return: the input Synapse synapseId
  */
  Synapse	*getInput(unsigned int synapseId);

  /*
  ** Get the output Synapse synapseId
  **
  ** @param synapseId: id of the output synapse to get back from the neuron
  ** @return: the output Synapse synapseId
  */
  Synapse	*getOutput(unsigned int synapseId);

private:
  // vector of inputs Synapse
  std::vector<Synapse *>	_inputs;
  // vector of output Synapse
  std::vector<Synapse *>	_outputs;
  // change in the neuron during learning
  float				_delta;

  /*
  ** Compute the output value of the neuron depending on its net input
  **
  ** @param netInput: the amount of current arriving as input in the neuron
  ** @return: the output value of the neuron
  */
  inline double	sigmoid(double netInput)		const;
};
