#pragma once

#include <iostream>
#include <iomanip>

#include "Network.hh"
#include "MNISTReader.hh"

enum Phase {
  TRAINING,
  TESTING
};

class Simulation {
public:
  /*
  ** Simulation constructor - load the data in memory and build the network
  */
  Simulation();

  /*
  ** Run the simulation by first launching the training and then the testing
  */
  void	run();
private:
  // variable able to read and load in memory MNIST files
  MNISTReader	_reader;
  // vector of training imaages
  img_vector	_trainingImgs;
  // vector of testing images
  img_vector	_testImgs;
  // vector of training labels
  lbl_vector	_trainingLbls;
  // vector of testing labels
  lbl_vector	_testLbls;
  // the artificial neural network
  Network	_network;

  /*
  ** Load the data in memory
  **
  ** @return: whether the data has correctly been load in memory
  */
  bool			loadData();

  /*
  ** Simply compute the percentage of correctly found values
  **
  ** @param found: number of correct values
  ** @param total: total number of values in a dataset
  ** @return: the percentage of correct values
  */
  inline double		toPercentage(double found, double total)	const;

  /*
  ** Create a vector that contains the expected output depending on a value
  **
  ** @param value: the normal expected output
  ** @return: a vector of inputs computed thanks to the given value
  */
  std::vector<double>	expectedOutput(double value)			const;

  /*
  ** Search the highest output of the artificial neural network - This value will be used as the predicted output
  **
  ** @param output: output of the artificial neural network
  ** @return: the highest output
  */
  double		getBest(const std::vector<double> &output)	const;

  /*
  ** Give data to the network, for training or testing
  **
  ** @param imgsV: image vector
  ** @param lblsV: label vector
  ** @param phase: step of the network, may be learning or training
  */
  unsigned int		feed(const img_vector &imgsV,
			     const lbl_vector &lblsV, Phase phase);
};
