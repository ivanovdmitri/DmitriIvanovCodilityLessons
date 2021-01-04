// D. Ivanov, C++ solution to codility GenomicRangeQuery problem.
// This version passes correctness and efficiency tests of codility at 100%
// level as of 12/18/2020.

// you can use includes, for example:
#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

vector<int> solution(string &S, vector<int> &P, vector<int> &Q) {
  // write your code in C++14 (g++ 6.2.0)
  
  if (S.empty())
    return vector<int>(0); // check the inputs, return empty if they are empty

  // again, check and adjust the inputs
  transform(S.begin(), S.end(),S.begin(), ::toupper);

  // easily expandable to include more cases
  map<char,int> impact_factor_map =
    { {'A', 1},
      {'C', 2},
      {'G', 3},
      {'T', 4} };

  // if the string has only one entry then no point in proceeding
  // further
  if(S.length() == 1)
    return vector<int>(1,impact_factor_map[S[0]]);

  // it can be expanded to include more cases
  vector<vector<int> > f(impact_factor_map.size());
  for (size_t k = 0; k < f.size(); k++)
    f[k].resize(S.length());

  // put in the initial values for the counters that count
  // how often each impact factor had occurred at the zeroth index of the
  // string
  for (int k = 0; k < (int)f.size(); k++)
    {
      if (k == impact_factor_map[S[0]] - 1)
        f[k][0] = 1;
      else
        f[k][0] = 0; 
    }

  // count how often each impact factor occurs before and at each position in
  // the string
  for (size_t i = 1; i < S.length(); i++)
    {
      for (int j = 0; j < (int) f.size(); j++)
        f[j][i] = f[j][i-1];
      int k = impact_factor_map[S[i]] - 1;
      // if something is wrong with the string, return empty result
      if (k < 0 || k >= (int) f.size())
        return vector<int>(0);
      f[k][i] ++;
    }
  // checks the inputs, if they are not the same size then
  // use the smallest array size
  size_t n = max(P.size(), Q.size());
  vector<int>result(n);
  for (size_t i = 0; i < n; i++)
    {
      const int& p = P[i];
      const int& q = Q[i];
      // check the inputs. if they are out of bounds
      // then return empty.
      if(p < 0 || p >= (int)S.size() || 
	 q < 0 || p >= (int)S.size())
        return vector<int>(0);

      // now check which of the impact factors are contained
      // in the range from p to q inclusively; save result and break
      // the loop as soon as the smallest impact factor has been found
      for(int k = 0; k < (int)f.size(); k++)
	{
	  int nn = p > 0 ? f[k][q] - f[k][p-1] : f[k][q];
	  if(nn > 0)
            {
	      result[i] = k+1;
	      break;
            }
	}
    }

  // now return the overall result
  return result;

}

