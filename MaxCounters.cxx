#include <vector>

using namespace std;

vector<int> solution(int N, vector<int> &A) {

    // stores the returned answer (this automatically
    // initializes all N counters to zero) 
    vector<int> answer(N);


    // keep track of the last counter maxout value
    // so that we don't have to loop over every counter
    // each time the counters need to be set to
    // the maximal value among them
    int M = 0;

    // current counter maximum value at any given iteration through A
    int m = 0;

    // look at each element of A and perform corresponding
    // operations on counters
    for (vector<int>::iterator it = A.begin(); it != A.end(); it++) 
    {
        // counter number that's being referenced by the array's entry
        int& cntnum = (*it);

        // increment the corresponding counter if the counter number value
        // is in 1 to N range
        if(1 <= cntnum && cntnum < N + 1) 
        {
            
            // counter that's being incremented
            int& cntval = answer[cntnum - 1];

            // setting the counter to the last maxout value 
            // if it's below that value
            if(cntval < M)
                cntval = M; 

            // increment the current counter's value
            cntval ++;

            // and keeping the current maximum value
            if(cntval > m)
                m = cntval;
        }
        // if the counter number is at N + 1 then
        // set the maxout value to the current maximum
        else if (cntnum == N + 1)
            M = m;
        // return an emtpy answer if the counter number is wrong
        else
            return vector<int>(0);
    }

    // be sure that all counters have been set to the last maxout value
    if(M > 0)
        for (vector<int>::iterator it = answer.begin(); it != answer.end(); it++)
        {
            int& cntval = (*it);
            if(cntval < M)
                cntval = M;
        }

    // return the answer
    return answer;
}
