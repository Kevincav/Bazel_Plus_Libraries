// Copyright 2015 Kevin Melkowski

#include "graphs/trie/trie.h"

#include <ctype.h>

googleapis::util::Status Trie::Insert(const std::string& input_string) {
  const char* input = input_string.c_str();
  Node* ptr = trie_.get();

  while (input) {
    if (ptr == nullptr) {
      ptr = new Node;
      if (ptr == nullptr) {
        return googleapis::util::Status(googleapis::util::error::Code::UNKNOWN,
                                        "Unable to insert string.");
      }
    }
    char current_character = tolower(*input++);
    if (!isalpha(current_character)) {
      return googleapis::util::Status(
          googleapis::util::error::Code::INVALID_ARGUMENT,
          "Invalid characters found in the string.");
    }
    if (current_character == '\n') {
      if (ptr->is_valid_string) {
        return googleapis::util::Status(
            googleapis::util::error::Code::ALREADY_EXISTS,
            "String already exists.");
      }
      break;
    }
    ptr = ptr->children[current_character - 'a'].get();
  }
  return googleapis::util::Status();
}

googleapis::util::Status Trie::Find(const std::string& input_string,
                                    Node** ptr = nullptr) {
  bool is_string_found = false;
  const char* input = input_string.c_str();
  *ptr = trie_.get();
  std::string error_message("Unable to find the string.");

  while (ptr != nullptr) {
    char current_character = tolower(*input++);
    if (!isalpha(current_character)) {
      return googleapis::util::Status(
          googleapis::util::error::Code::INVALID_ARGUMENT,
          "Invalid characters found in the string.");
    }
    if (current_character == '\0') {
      is_string_found = (*ptr)->is_valid_string;
      break;
    }
    *ptr = (*ptr)->children[current_character - 'a'].get();
  }

  if (is_string_found) {
    return googleapis::util::Status();
  }
  return googleapis::util::Status(googleapis::util::error::Code::NOT_FOUND,
                                  "Unable to find that string.");
}

googleapis::util::Status Trie::Remove(const std::string& input_string) {
  Node* ptr;
  googleapis::util::Status status = Find(input_string, &ptr);
  if (status.ok()) {
    ptr->is_valid_string = false;
  }
  return status;
}

googleapis::util::Status Trie::Find(const std::string& input_string) {
  return Find(input_string, nullptr);
}
