// Copyright 2015 Kevin Melkowski

#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

#include "gflags/gflags.h"
#include "glog/logging.h"
#include "sort/radix_sort/radix_sort.h"

DEFINE_int32(number_of_elements, 100000000, "How many elements should I sort?");
DEFINE_bool(time_std_sort, false, "Should I compare against std::sort?");

typedef float kDataType;

std::vector<kDataType> GenerateRandomVector() {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_real_distribution<kDataType> uniform_dist(
      std::numeric_limits<kDataType>::min(),
      std::numeric_limits<kDataType>::max());
  std::vector<kDataType> output(FLAGS_number_of_elements);
  for (int i = 0; i < FLAGS_number_of_elements; ++i) {
    output[i] = uniform_dist(engine);
  }
  return output;
}

int main(int argc, char* argv[]) {
  ::google::InitGoogleLogging(argv[0]);
  ::google::ParseCommandLineFlags(&argc, &argv, true);

  // Set up test parameters.
  RadixSort radix_sort;
  std::vector<kDataType> test_vector = GenerateRandomVector();
  std::vector<kDataType> compare_vector;
  if (FLAGS_time_std_sort) {
    compare_vector.insert(compare_vector.begin(), test_vector.begin(),
                          test_vector.end());
  }

  // Time and run tests.
  std::chrono::high_resolution_clock::time_point t1 =
      std::chrono::high_resolution_clock::now();
  radix_sort.Sort(test_vector);
  std::chrono::high_resolution_clock::time_point t2 =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  LOG(INFO) << "It took the radix_sort " << time_span.count()
            << " seconds to sort " << FLAGS_number_of_elements << " elements.";

  // Only runs if comparing timings to std::sort.
  if (FLAGS_time_std_sort) {
    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();
    std::sort(compare_vector.begin(), compare_vector.end());
    std::chrono::high_resolution_clock::time_point t2 =
        std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span =
        std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    LOG(INFO) << "It took the std::sort " << time_span.count()
              << " seconds to sort " << FLAGS_number_of_elements
              << " elements.";
  }
  return 0;
}
