#include "functor.h"
template <class Comparator>

void DoStringCompare(const std::string& s1, const std::string& s2, Comparator comp)
{
  std::cout << comp(s1, s2) << std::endl;  // calls comp.operator()(s1,s2);
}

int main() {
    std::string s1 = "abc";
    std::string s2 = "cba";

    NumStrComp comp;

    DoStringCompare(s1, s2, comp);
}