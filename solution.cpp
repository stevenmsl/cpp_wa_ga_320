#include "solution.h"
#include "util.h"
#include <unordered_map>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <functional>
#include <math.h>
using namespace sol320;
using namespace std;

/*takeaways
  - refer to cpp_ga_320 for the backtracking approach
  - for this approach we are basing on the following
    observations
    - 0000 -> "word"
      - nothing is abbreviated
    - 0001 -> the first char is abbreviated to a number
      - w[0] = 1
      - "word" -> "1ord"
    - 0100
      - w[2] = 1
      - "word" -> "wo1d"
  - each position in the word "word" has two choices
    - get abbreviated or stay the same
    - so 2x2x2x2=16 combinations
*/

vector<string> Solution::generate(string word)
{
  const int size = word.size();
  auto abbrs = vector<string>();

  /*generate all possible combinations
    - for example
      0000,0001...1111
  */
  for (auto i = 0; i < pow(2, size); i++)
  {
    /* for each combination */
    auto abbr = string("");
    auto c = i;
    auto cnt = 0;

    for (auto j = 0; j < size; j++)
    {
      /*only look at the least significant bit */
      if (c & 1)
      {
        /*keep accumulating the count if we have consecutive 1's
          - 0110 will produce a count of 2
         */
        cnt++;
        if (j == size - 1)
          abbr += to_string(cnt);
      }
      else
      {
        /* reset the counter and pick up the number */
        if (cnt)
        {
          abbr += to_string(cnt);
          cnt = 0;
        }
        abbr += word[j];
      }
      /* examine the next bit
         - 0111 -> 0011-> 0001 -> 0000
      */
      c >>= 1;
    }
    abbrs.push_back(abbr);
  }

  return abbrs;
}