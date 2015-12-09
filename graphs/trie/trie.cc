// Copyright 2015 Kevin Melkowski

#include "graphs/trie/trie.h"

#include <ctype.h>
#include <stdio.h>

googleapis::util::Status Trie::Insert(const std::string& input_string) {
  Node* ptr = trie_.get();

  for (const char& value : input_string) {
    if (ptr == nullptr) {
      printf("Allocating for a new element.");
      ptr = new Node;
      if (ptr == nullptr) {
        return googleapis::util::Status(googleapis::util::error::Code::UNKNOWN,
                                        "Unable to insert string.");
      }
    }
    char current_character = tolower(value);
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
  Node* curr_ptr = trie_.get();
  std::string error_message("Unable to find the string.");

  for (const char& value : input_string) {
    if (curr_ptr == nullptr) {
      break;
    }
    char current_character = tolower(value);
    if (!isalpha(current_character)) {
      return googleapis::util::Status(
          googleapis::util::error::Code::INVALID_ARGUMENT,
          "Invalid characters found in the string.");
    }
    if (current_character == '\0') {
      is_string_found = curr_ptr->is_valid_string;
      break;
    }
    curr_ptr = curr_ptr->children[current_character - 'a'].get();
  }

  if (is_string_found) {
    return googleapis::util::Status();
    *ptr = curr_ptr;
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
