#ifndef TRIE_H_
#define TRIE_H_

#include <memory>
#include <string>
#include <vector>

#include "base/util/status.h"
#include "googleapi/base/macros.h"

extern struct Node;

class Trie {
 public:
  // Add Objects here.
  util::Status Insert(const std::string& input_string);

  // Add remove here.
  util::Status Remove(const std::string& input_string);

  // Change me with StatusOrDie and add objects
  util::Status Find(const std::string& input_string);

 private:
  std::unique_ptr<struct Node> trie_;

  DISALLOW_COPY_AND_ASSIGN(Trie);
};

#endif  // TRIE_H_
