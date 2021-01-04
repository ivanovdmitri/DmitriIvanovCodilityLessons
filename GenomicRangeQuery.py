# D. Ivanov, Python solution to codility GenomicRangeQuery problem.
# This version passes correctness and efficiency tests of codility at 100%
# level as of 12/18/2020.


from collections import defaultdict

# codility doesn't want you to use numpy
# for this exercise, this won't work
#import numpy

def solution(S, P, Q):
    # write your code in Python 3.6

    # check the inputs
    if(len(S) < 1):
        return None

    # dictionary with default element "None"
    d=defaultdict(lambda:None)
    
    # include the known impact factors, can always add more ...
    d.update({
        "A" : 1,
        "C" : 2,
        "G" : 3,
        "T" : 4}
    )


    # impact factor that corresponds to the 1st element
    # of the string
    f0 = d[S[0].upper()]

    # stop here if the 1st string element is invalid
    if f0 == None:
        return None

    # the output is always going to be the same
    # if the length of the string is 1
    if(len(S) == 1):
        return [f0]

    # now for the sake of efficiency, let's count
    # how many times before and at the given index
    # in the string has the impact factor occurred
    nf=[[0] * len(S) for _ in range(len(d)) ]
    # increment the appropriate counter using the 1st element of
    # the string
    nf[f0-1][0] += 1

    # now go over all string elements incrementing the apropriate
    # counters at each position in the string. The counters
    # at each position are first initialized to their previous
    # values.
    for i in range(1,len(S)):
        # initializing counters with the previous values
        for k in range(len(d)):
            nf[k][i] = nf[k][i-1]
        f=d[S[i].upper()]
        # incrementing the appropriate counter at the position
        # if the impact factor was valid
        if(f != None):
            nf[f-1][i] += 1
        # return None if the string contained an invalid
        # entry
        else:
            return None
    # now go over the queries and if they are valid, store
    # their minimum impact factor. Ignore the queries that
    # are not valid

    # choose the smallest index of the input query arrays
    # in case they are not the same length
    n = min([len(P),len(Q)])
    result = [] # list that will store the answer
    for i in range(n):
        p = P[i]
        q = Q[i]
        # skip invalid queries
        if p < 0 or q < 0 or p >= len(S) or q >= len(S):
            continue
        # pick out only the smallest impact factors
        # which had a non-zero occurrence within the query
        # range and add them to the results list. 
        for k,f in enumerate(nf):
            nn = f[q] - f[p - 1] if p > 0 else f[q]
            if  nn > 0:
                result.append(k+1)
                break

    return result
