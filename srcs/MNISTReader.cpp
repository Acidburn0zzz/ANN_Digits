#include "MNISTReader.hh"

const std::string MNISTReader::trainingImgFile	= "data/train-images-idx3-ubyte";
const std::string MNISTReader::trainingLblFile	= "data/train-labels-idx1-ubyte";
const std::string MNISTReader::testImgFile	= "data/t10k-images-idx3-ubyte";
const std::string MNISTReader::testLblFile	= "data/t10k-labels-idx1-ubyte";

MNISTReader::MNISTReader() :
  _endian(checkEndian())
{}

MNISTReader::Endian MNISTReader::checkEndian() const {
  union {
    uint16_t ui;
    unsigned char c[2];
  } endianUnion {1};

  if (endianUnion.c[0] == 1) // assume processor is big or little endian
    return _LITTLE_ENDIAN;
  return _BIG_ENDIAN;
}

bool MNISTReader::openFile(std::ifstream &file, const std::string &filename) const {
  file.open(filename.c_str(), std::ofstream::binary);
  if (file.is_open() == false) // later, better error managment
    return false;
  file.seekg(sizeof(int32_t)); // move after magic number
  return true;
}

lbl_vector MNISTReader::readLbls(const std::string &filename) const {
  std::ifstream file;
  char c;
  int32_t itemNumber;
  lbl_vector lbls;
  openFile(file, filename);
  file.read(reinterpret_cast<char *>(&itemNumber), sizeof(itemNumber));
  if (_endian == _LITTLE_ENDIAN)
    itemNumber = reverse_bytes<int32_t>(itemNumber);
  for (int i = 0; i < itemNumber; i++) { // can be faster with less read
    file.read(&c, sizeof(c));
    lbls.push_back(c);
  }
  file.close();
  return lbls;
}

img_vector MNISTReader::readImgs(const std::string &filename) const {
  std::ifstream file;
  int32_t itemNumber, rows, columns;
  img_vector imgs;
  int j;
  openFile(file, filename);
  file.read(reinterpret_cast<char *>(&itemNumber), sizeof(itemNumber));
  file.read(reinterpret_cast<char *>(&rows), sizeof(rows));
  file.read(reinterpret_cast<char *>(&columns), sizeof(columns));
  if (_endian == _LITTLE_ENDIAN) {
    itemNumber = reverse_bytes<int32_t>(itemNumber);
    rows = reverse_bytes<int32_t>(rows);
    columns = reverse_bytes<int32_t>(columns);
  }
  char *pixels = new char[rows * columns];
  for (int i = 0; i < itemNumber; i++) { // can be faster with less read
    std::vector<unsigned char> img;
    file.read(pixels, rows * columns * sizeof(*pixels));
    for (j = 0; j < rows * columns; j++)
      img.push_back(pixels[j]);
    imgs.push_back(img);
  }
  file.close();
  return imgs;
}

img_vector MNISTReader::getTrainingImgs() const {
  return readImgs(trainingImgFile);
}

lbl_vector MNISTReader::getTrainingLbls() const {
  return readLbls(trainingLblFile);
}

img_vector MNISTReader::getTestImgs() const {
  return readImgs(testImgFile);
}

lbl_vector MNISTReader::getTestLbls() const {
  return readLbls(testLblFile);
}
