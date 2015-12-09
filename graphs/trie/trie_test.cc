#include "graphs/trie/trie.h"

#include <memory>

#include "googleapis/util/status.h"
#include "glog/logging.h"
#include "gtest/gtest.h"

class TrieTest : public ::testing::Test {
 protected:
  void SetUp() { trie_.reset(new Trie); }

  std::unique_ptr<Trie> trie_;
};

TEST_F(TrieTest, TestInsertWorksWithErrorCodes) {
    googleapis::util::Status status = trie_->Insert("Hello");
    EXPECT_TRUE(status.ok());
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  return RUN_ALL_TESTS();
}
