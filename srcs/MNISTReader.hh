#pragma once

#include <string>
#include <cstdint>
#include <fstream>
#include <vector>
#include <istream>

using img_vector = std::vector<std::vector<unsigned char>>;
using lbl_vector = std::vector<unsigned char>;

class MNISTReader {
public:

  MNISTReader();

  img_vector getTrainingImgs()	const;
  lbl_vector getTrainingLbls()	const;
  img_vector getTestImgs()	const;
  lbl_vector getTestLbls()	const;

private:
    
    enum Endian {
    _BIG_ENDIAN,
    _LITTLE_ENDIAN
  };
    
  static const std::string	trainingImgFile;
  static const std::string	trainingLblFile;
  static const std::string	testImgFile;
  static const std::string	testLblFile;
  Endian			_endian;

  // credit: http://stackoverflow.com/questions/105252/how-do-i-convert-between-big-endian-and-little-endian-values-in-c
  template<typename T>
  T reverse_bytes(const T& value) const {
    T swapped = 0;
    int bytes = sizeof(value);
    for (int i = 0; i < bytes; i++)
      swapped |= (value >> (8 * (bytes - i - 1)) & 0xFF) << (8 * i);
    return swapped;
  }

  MNISTReader::Endian	checkEndian()				const;
  lbl_vector	readLbls(const std::string &filename)		const;
  img_vector	readImgs(const std::string &filename)		const;
  bool		openFile(std::ifstream &file, 
                const std::string &filename)                    const;
};
