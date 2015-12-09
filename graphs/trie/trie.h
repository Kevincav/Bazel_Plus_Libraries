// Copyright 2015 Kevin Melkowski

#ifndef GRAPHS_TRIE_TRIE_H_
#define GRAPHS_TRIE_TRIE_H_

#include <memory>
#include <string>
#include <vector>

#include "googleapis/util/status.h"

struct Node {
  Node() : is_valid_string(false) {}
  bool is_valid_string;
  std::vector<std::unique_ptr<struct Node>> children;
};

class Trie {
 public:
  // Add Objects here.
  googleapis::util::Status Insert(const std::string& input_string);

  // Add remove here.
  googleapis::util::Status Remove(const std::string& input_string);

  // Change me with StatusOrDie and add objects
  googleapis::util::Status Find(const std::string& input_string);

 private:
  std::unique_ptr<struct Node> trie_;

  googleapis::util::Status Find(const std::string& input_string, Node** ptr);
};

#endif  // GRAPHS_TRIE_TRIE_H_
