#include "graphs/trie.h"

#include <ctype.h>

#include "googleapis/util/status.h"

struct Node {
  Node() : is_valid_string(false) {}
  bool is_valid_string;
  std::vector<std::unique_ptr<struct Node>> children;
};

util::Status Trie::Insert(const std::string& input_string) {
  char* input = input_string.c_str();
  Node* ptr = trie_.get();

  while (input) {
    if (ptr == nullptr) {
      ptr = new Node;
      if (ptr == nullptr) {
        return util::Status(googleapis::util::error::Code::UNKNOWN,
                            "Unable to insert string.");
      }
    }
    char current_character = tolower(*input++);
    if (!isalpha(current_character)) {
      return util::Status(googleapis::util::error::Code::INVALID_ARGUMENT,
                          "Invalid characters found in the string.");
    }
    if (current_character == '\n') {
      if (ptr->is_valid_string) {
        return util::Status(googleapis::util::error::Code::ALREADY_EXISTS,
                            "String already exists.");
      }
      break;
    }
    ptr = ptr->children[current_character - 'a'].get();
  }
  return util::Status(googleapis::util::error::Code::OK);
}

util::Status Trie::Find(const std::string& input_string, Node* ptr = nullptr) {
  bool is_string_found = false;
  char* input = input_string.c_str();
  ptr = trie_.get();
  std::string error_message("Unable to find the string.");

  while (ptr != nullptr) {
    char current_character = tolower(*input++);
    if (!isalpha(current_character)) {
      return util::Status(googleapis::util::error::Code::INVALID_ARGUMENT,
                          "Invalid characters found in the string.");
    }
    if (current_character == '\0') {
      is_string_found = ptr->is_valid_string;
      break;
    }
    ptr = ptr->children[current_character - 'a'].get();
  }

  if (is_string_found) {
    return util::Status(googleapis::util::error::Code::OK);
  }
  return util::Status(googleapis::util::error::Code::NOT_FOUND,
                      "Unable to find that string.");
}

util::Status Trie::Remove(const std::string& input_string) {
  Node* ptr;
  util::Status status = Find(input_string, ptr);
  if (status.ok()) {
    ptr->is_valid_string = false;
  }
  return status;
}

util::Status Trie::Find(const std::string& input_string) {
  return Find(input_string);
}
