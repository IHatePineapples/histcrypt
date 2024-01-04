
#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
#include <array>

const std::string ciphertext{
    "dvozInv gl gsv zibkgltixksb nlwfov gsv nlwfov droo zlevi gsv kirmzrkovh "
    "xmw gvzsmrjfvh lu hvzfirmt zInkfgvih xmw mvgdliph rg rh hkorg mvogion "
    "rora nkorormood kyion asvir rmgl gdl kxigh dsviv gsv urihg rh zImzvimvw "
    "drgs hbnnvgirz zibkgltixksb dsvivxh gsv hvzlmw kxig rh zImzvimvw drgs "
    "xhbnnvgirz zibkgltixksb xnlmt lgsvi gsrmth gsv nlwfov vckoxrmh gsv "
    "zibkgltixksrz gsvlib rmzofwrmt nxmb zoxhhrzxo xh dvoo xh klkfoxi zrksvih "
    "gsv pmldovwtv droo svok blf rm wvhrtmrmt xmw wvevolkrmt hvzfiv "
    "xkkorzxgrlmh xmw hvzfiv zInkfgvi mvgdliph gsrh rh dsviv gsvlib nvvgh "
    "kixzgrzv"};

const std::map<char, char> solution{
    // {'a','a'},
    // {'b','a'},
    // {'c','a'},
    // {'d','a'},
    // {'e','a'},
    // {'f','a'},
    // {'g','a'},
    // {'h','a'},
    // {'i','a'},
    // {'j','a'},
    // {'k','a'},
    // {'l','a'},
    // {'m','a'},
    // {'n','a'},
    // {'o','a'},
    // {'p','a'},
    // {'q','a'},
    // {'r','a'},
    // {'s','a'},
    // {'t','a'},
    // {'u','a'},
    // {'v','a'},
    // {'w','a'},
    // {'x','a'},
    // {'y','a'},
    // {'z','a'},
};

void decrypt_freq_analysis() {
  const std::array<char, 27> frequency_order{"etaoinsrhldcumfpgwybvkxjqz"};
  std::map<char, int> character_count;

  for (const auto &c : ciphertext) {
    ++character_count[c];
  }

  std::map<char, std::string> character_count_graph;

  for (const auto &c : ciphertext) {
    character_count_graph[c] += '|';
  }

  std::vector<std::pair<char, int>> cc_v;
  for (const auto &p : character_count)
    cc_v.push_back(p);

  std::sort(cc_v.begin(), cc_v.end(),
            [](auto &l, auto &r) { return l.second > r.second; });

  cc_v.erase(cc_v.begin());

  std::map<char, char> solution;

  int i{0};

  for (const auto &p : cc_v) {
    solution[frequency_order[i]] = p.first;
    ++i;
  }

  for (const auto &c : ciphertext) {
    if (c == ' ') {
      std::cout << c;
      continue;
    }

    std::cout << solution[c];
  }
  std::cout << std::endl;

  for (const auto &[c, n] : character_count)
    std::cout << c << ": " << n << '\n';
  for (const auto &[c, n] : character_count_graph)
    std::cout << c << " " << n << '\n';
  for (const auto &[c, n] : cc_v)
    std::cout << c << " " << n << '\n';
  std::cout << std::endl;
}



int main() {}
