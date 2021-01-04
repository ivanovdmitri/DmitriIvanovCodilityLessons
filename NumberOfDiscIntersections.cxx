#include <vector>

int solution(std::vector<int> &A) {
    // since speed is the most important thing here,
    // we allocate arrays that count where and how
    // many circles start and end
    std::vector<int> nstarts(A.size()), nends(A.size());
    
    // using long long int type will make the 
    // solution expandible to larger
    // integers and will prevent arithmetic overflows
    long long int N = (long long int)A.size();

    for (long long int i = 0; i < N; i++)
    {
        // count where the circles start; no point
        // in counting beyond the beginning of the array
        long long int j = i - A[i];
        if (j < 0)
            j = 0;
        nstarts[j] ++;

        // count where the circles end; no point in counting
        // beyond the end of the array
        j = i + A[i];
        if (j > N - 1)
            j = N - 1;
        nends[j]++;
    }
    long long int answer = 0; // initialize the answer
    // variable nstarted is needed in the local scope
    // to count how many circles are started at any given
    // step of the array
    for (long long int i = 0, nstarted = 0; i < N; i++)
    {

        // count the started circles
        nstarted += nstarts[i];


        // counting unique circles that overlap. If there are nstarted circles
        // that started so far and nends[i] ricles that are ending at i, then
        // the number of addinitional overlaps is (each ended circle overlaps 
        // with the remaining started circles):
        // (nstarted - 1) + (nstarted - 2) + ... (nstarted - nends[i]) = 
        // = nstarted * nends[i] - (1 + 2 + ... + nends[i]) =
        // = nstarted * nends[i] - nends[i] * (nends[i] + 1) / 2, using the
        // 1 + 2 + ... n = n(n+1)/2 summation formula. 
        // also, we are not factoring out nends[i] so that the integer
        // division (nends[i]+1)) / 2 works out correctly because we are
        // not using a data type with floating point.

        answer += nends[i] * nstarted - (nends[i] * (nends[i]+1)) / 2;
        
        // subtract the circles that ended from the number
        // of the circles that started
        nstarted -= nends[i];
    }

    // that's what the problem wants ... but this can be generalized
    // to larger integers if necessary
    if (answer > 10000000 )
        answer = -1;
    
    return answer;
}
