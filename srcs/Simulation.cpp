#include "Simulation.hh"

Simulation::Simulation() :
  _network({784, 15, 10}) {
  loadData();
  cout << "training images: " << _trainingImgs.size() << endl
       << "training labels: " << _trainingLbls.size() << endl
       << "test images: " << _testImgs.size() << endl
       << "test labels: " << _testLbls.size() << endl;
}

void Simulation::run() {
  unsigned int trainingCorrect = feed(_trainingImgs, _trainingLbls, TRAINING);
  cout << trainingCorrect << "/" << _trainingImgs.size()
       << " | classification rate: "
       << toPercentage(trainingCorrect, _trainingImgs.size())
       << "% | random: "
       << toPercentage(_trainingImgs.size() / 10, _trainingImgs.size())
       << "% " << endl;

  unsigned int testingCorrect = feed(_testImgs, _testLbls, TESTING);
  cout << testingCorrect << "/" << _testImgs.size()
       << " | classification rate: "
       << toPercentage(testingCorrect, _testImgs.size())
       << "% | random: "
       << toPercentage(_testImgs.size() / 10, _testImgs.size())
       << "%" << endl;
}

void Simulation::loadData() {
  #pragma omp parallel sections
  {
    #pragma omp section
    {
      _trainingImgs = _reader.getTrainingImgs(); // 45 M
    }
    #pragma omp section
    {
      _trainingLbls = _reader.getTrainingLbls(); // 59K
      _testImgs = _reader.getTestImgs(); // 8M
      _testLbls = _reader.getTestLbls(); // 10K
      _network.fullyConnect(0, 1);
      _network.fullyConnect(1, 2);
    }
  }
}

double Simulation::toPercentage(double found, double total) const {
  return found / total * 100;
}

vector<double> Simulation::expectedOutput(double value) const {
  vector<double> expectedOutput = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  expectedOutput[(int)value] = 1;
  return expectedOutput;
}

double Simulation::getBest(vector<double> output) const {
  int bestNb = -1;
  double bestValue = -1;

  for (unsigned int i = 0; i < output.size(); i++) {
    if (bestValue < output[i]) {
      bestValue = output[i];
      bestNb = i;
      //cout << setprecision(3) << output[j] << " ";
    }
  }
  return bestNb;
}

unsigned int Simulation::feed(const img_vector &imgsV, const lbl_vector &lblsV, Phase phase) {
  unsigned int i, totalCorrect = 0;
  int bestNb;
  vector<double> output;

  for (i = 0; i < imgsV.size(); i++) {
    vector<double> img(imgsV[i].begin(), imgsV[i].end());
    output = _network.feed(img);
    bestNb = getBest(output);
    if (phase == TRAINING)
      _network.backpropagation(expectedOutput(lblsV[i]));
    if (bestNb == (int)lblsV[i]) {
      ++totalCorrect;
      //  cout << "GOOD";
    }
    //else
    // cout << "BAD";
    //cout << "(" << i << "): " << "found " << bestNb
    // << " should be " << (int)trainingLbls[i] << endl;
  }
  return totalCorrect;
}
