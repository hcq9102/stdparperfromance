#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "argparse/argparse.hpp"
#include "commons.hpp"

// generate positive definition matrix
template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
std::vector<T> generate_pascal_matrix(const int n) {
  Matrix<T> matrix(n, std::vector<T>(n, static_cast<T>(0)));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == 0 || j == 0) {
        matrix[i][j] = static_cast<T>(1);
      } else {
        matrix[i][j] = matrix[i][j - 1] + matrix[i - 1][j];
      }
    }
  }

  std::vector<T> flattenedVector;
  for (const auto& row : matrix) {
    flattenedVector.insert(flattenedVector.end(), row.begin(), row.end());
  }
  return std::move(flattenedVector);
}

// parameters define
struct args_params_t : public argparse::Args {
  bool& results = kwarg("results", "print generated results (default: false)")
                      .set_default(false);
  std::uint64_t& nd =
      kwarg("nd", "Number of input(positive definition) matrix dimension(<=18)")
          .set_default(10);
  std::uint64_t& np = kwarg("np", "Number of partitions").set_default(4);
  bool& help = flag("h, help", "print help");
  bool& time = kwarg("t, time", "print time").set_default(true);
};

// Function to read data from a text file and store it in a vector
inline std::vector<int> readDataFromFile(const std::string& filename) {
  std::vector<int> data;

  // Open the file
  std::ifstream file(filename);

  // Check if the file is open successfully
  if (!file.is_open()) {
    std::cerr << "Failed to open the file: " << filename << std::endl;
    return data;  // Return an empty vector in case of failure
  }

  std::string line;
  while (std::getline(file, line)) {
    // Use std::istringstream to parse each line into doubles and store them in the vector
    double value;
    std::istringstream iss(line);
    while (iss >> value) {
      data.push_back(value);
    }
  }

  // Close the file
  file.close();

  return data;
}

extern std::vector<int> inputMatrix = readDataFromFile(
    "/global/homes/c/chuanqiu/performance/nvstdpar/apps/choleskey/"
    "cholesky_result400.txt");
