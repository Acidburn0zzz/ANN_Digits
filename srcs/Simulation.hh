#pragma once

#include <iostream>
#include <iomanip>

#include "Network.hh"
#include "MNISTReader.hh"

using namespace std;

enum Phase {
  TRAINING,
  TESTING
};

class Simulation {
public:
  Simulation();
  void	run();
private:
  MNISTReader	_reader;
  img_vector	_trainingImgs;
  img_vector	_testImgs;
  lbl_vector	_trainingLbls;
  lbl_vector	_testLbls;
  Network	_network;

  void			loadData();
  inline double		toPercentage(double found, double total)	const;
  vector<double>	expectedOutput(double value)			const;
  double		getBest(vector<double> output)			const;
  unsigned int		feed(const img_vector &imgsV,
			     const lbl_vector &lblsV, Phase phase);
};
