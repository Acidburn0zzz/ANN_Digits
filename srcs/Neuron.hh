#pragma once

#include <vector>
#include <cmath>

#include "Synapse.hh"

class Neuron {
public:
  void		addInput(Synapse *input);
  void		addOutput(Synapse *output);
  void		fire();
  float		getOutputValue()			const;
  void		setInputValue(float inputValue);
  void		setDelta(float delta);
  float		getDelta()				const;
  unsigned int	getOutputNb()				const;
  unsigned int	getInputNb()				const;
  Synapse	*getInput(unsigned int synapseId);
  Synapse	*getOutput(unsigned int synapseId);

private:
  std::vector<Synapse *>	_inputs;
  std::vector<Synapse *>	_outputs;
  float				_delta;

  inline double	sigmoid(double netInput)	const;
};
