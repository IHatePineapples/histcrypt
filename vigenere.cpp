#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
constexpr std::string_view ciphertext{"bruebrsmbsf"};

namespace help {
// Why bother doing ASCII math, here's a massive O(1) jump/lookup table (I can't
// get the math right :/)
constexpr int atoi(const char &c) {
  switch (c) {
  case 'a':
    return 0;
  case 'b':
    return 1;
  case 'c':
    return 2;
  case 'd':
    return 3;
  case 'e':
    return 4;
  case 'f':
    return 5;
  case 'g':
    return 6;
  case 'h':
    return 7;
  case 'i':
    return 8;
  case 'j':
    return 9;
  case 'k':
    return 10;
  case 'l':
    return 11;
  case 'm':
    return 12;
  case 'n':
    return 13;
  case 'o':
    return 14;
  case 'p':
    return 15;
  case 'q':
    return 16;
  case 'r':
    return 17;
  case 's':
    return 18;
  case 't':
    return 19;
  case 'u':
    return 20;
  case 'v':
    return 21;
  case 'w':
    return 22;
  case 'x':
    return 23;
  case 'y':
    return 24;
  case 'z':
    return 25;
  default:
    throw std::runtime_error{
        std::string{c}}; // I wish I could use std::unreachable here
  }
}
constexpr char itoa(const int &i) {
  switch (i % 26) {
  case 0:
    return 'a';
  case 1:
    return 'b';
  case 2:
    return 'c';
  case 3:
    return 'd';
  case 4:
    return 'e';
  case 5:
    return 'f';
  case 6:
    return 'g';
  case 7:
    return 'h';
  case 8:
    return 'i';
  case 9:
    return 'j';
  case 10:
    return 'k';
  case 11:
    return 'l';
  case 12:
    return 'm';
  case 13:
    return 'n';
  case 14:
    return 'o';
  case 15:
    return 'p';
  case 16:
    return 'q';
  case 17:
    return 'r';
  case 18:
    return 's';
  case 19:
    return 't';
  case 20:
    return 'u';
  case 21:
    return 'v';
  case 22:
    return 'w';
  case 23:
    return 'x';
  case 24:
    return 'y';
  case 25:
    return 'z';
  default:
    throw std::runtime_error{
        std::to_string(i)}; // I wish I could use std::unreachable here
  }
}
} // namespace help

namespace crypt {

using namespace help;

std::string encrypt(const std::string &s, const std::string &k) {
  std::string lciphertext{s};
  for (int i = 0; i != s.size() - 1; ++i)
    lciphertext.at(i) = itoa(atoi(s.at(i)) + atoi(k.at(i % (k.size() - 1))));

  lciphertext.erase(lciphertext.size() - 1);

  return lciphertext;
}
} // namespace crypt

namespace preprocess {

template <int n, int k> bool has_n_times_k_same_letters(const std::string &s) {

  std::map<char, int> count_map;
  for (const auto &c : s)
    ++count_map[c];

  int count{0};
  for (const auto &p : count_map)
    if (p.second == k)
      ++count;

  return count == n;
}

template <int n> bool has_n_same_letters(const std::string &s) {

  std::map<char, int> count_map;
  for (const auto &c : s)
    ++count_map[c];

  int count{0};
  for (const auto &p : count_map)
    if (p.second == n)
      ++count;

  return count == 1;
}
void possible_plaintexts() {
  std::ifstream all_words;
  all_words.open("./words_alpha.txt");
  if (!all_words.is_open())
    throw std::runtime_error{std::to_string(__LINE__)};

  std::ofstream plaintexts;
  plaintexts.open("./possible_plaintexts.txt");
  if (!plaintexts.is_open())
    throw std::runtime_error{std::to_string(__LINE__)};

  std::string w{};
  while (std::getline(all_words, w))
    if (w.size() == 12 && w.at(2) == 'c' && w.at(0) == w.at(4) &&
        has_n_times_k_same_letters<2, 3>(w))
      plaintexts << w << '\n';
}

void keys() {
  std::ifstream all_words;
  all_words.open("./words_alpha.txt");
  if (!all_words.is_open())
    throw std::runtime_error{std::to_string(__LINE__)};

  std::ofstream keys;
  keys.open("./possible_keys.txt");
  if (!keys.is_open())
    throw std::runtime_error{std::to_string(__LINE__)};

  std::string w{};
  while (std::getline(all_words, w))
    if (w.size() == 5 && has_n_same_letters<2>(w))
      keys << w << '\n';
}

} // namespace preprocess

void brute_force() {
  std::ifstream plaintexts;
  plaintexts.open("./possible_plaintexts.txt");
  if (!plaintexts.is_open())
    throw std::runtime_error{std::to_string(__LINE__)};

  std::string plaintext;

  while (std::getline(plaintexts, plaintext)) {
    std::ifstream keys;

    keys.open("./possible_keys.txt");
    if (!keys.is_open())
      throw std::runtime_error{std::to_string(__LINE__)};

    std::string key;
    while (std::getline(keys, key))
      if (crypt::encrypt(plaintext, key) == ciphertext) {
        std::cout << "Found!\n";
        std::cout << "\tPlaintext=" << plaintext << '\n';
        std::cout << "\tKey=" << key << std::endl;
        return;
      }
  }
}

int main() {
  preprocess::possible_plaintexts();
  preprocess::keys();
  brute_force();
}
