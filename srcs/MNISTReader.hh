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

  /*
  ** MNISTReader constructor - initialize endianess
  */
  MNISTReader();

  /*
  ** Get the training images
  **
  ** @return a vector of images
  */
  img_vector getTrainingImgs()	const;

  /*
  ** Get the training labels
  **
  ** @return a vector of labels
  */
  lbl_vector getTrainingLbls()	const;

  /*
  ** Get the test images
  **
  ** @return a vector of images
  */
  img_vector getTestImgs()	const;

  /*
  ** Get the test labels
  **
  ** @return a vector of labels
  */
  lbl_vector getTestLbls()	const;

private:

  // list of possible endians
    enum Endian {
    _BIG_ENDIAN,
    _LITTLE_ENDIAN
  };

  // list of filenames
  static const std::string	trainingImgFile;
  static const std::string	trainingLblFile;
  static const std::string	testImgFile;
  static const std::string	testLblFile;

  // OS endian
  Endian			_endian;

  /*
  ** Change variable endianess
  ** credit: http://stackoverflow.com/questions/105252/how-do-i-convert-between-big-endian-and-little-endian-values-in-c
  **
  ** @param value: variable on which to change endianess
  ** @return the reversed variable
  */
  template<typename T>
  T reverse_bytes(const T& value) const {
    T swapped = 0;
    int bytes = sizeof(value);
    for (int i = 0; i < bytes; i++)
      swapped |= (value >> (8 * (bytes - i - 1)) & 0xFF) << (8 * i);
    return swapped;
  }

  /*
  ** Check endianess of OS
  **
  ** @return the current endian
  */
  MNISTReader::Endian	checkEndian()				const;

  /*
  ** Get all labeles saved in filename
  **
  ** @param filename: file in which labels are saved
  ** @return a vector of labels
  */
  lbl_vector	readLbls(const std::string &filename)		const;

  /*
  ** Get all images saved in filename
  **
  ** @param filename: file in which images are saved
  ** @return a vector of images
  */
  img_vector	readImgs(const std::string &filename)		const;

  /*
  ** Open the file filename and save it in file
  **
  ** @param file: stream in which the file is saved
  ** @param filename: filename to open
  ** @return: whether the file has correctly been open
  */
  bool		openFile(std::ifstream &file,
                const std::string &filename)                    const;
};
