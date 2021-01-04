
# present problem doesn't allow numpy
#import numpy

def solution(N, A):
    counters=[int(0)]*N
    m = int(0) # maximum value at each iteration through A
    M = int(0) # last maximum value all counters were set to
    # iterate through the elements of A
    for cntnum in A:
        # instruction to increment a certain counter
        if 1 <= cntnum and cntnum < N + 1:
            # make sure that the last maxout value was
            # taken into account
            if counters[cntnum - 1] < M:
                counters[cntnum - 1] = M
            # increment the counter with index corresponding 
            # to the present value of A
            counters[cntnum - 1] += 1
            # update the current maximum value across counters
            if m < counters[cntnum - 1]:
                m = counters[cntnum - 1]
        # instruction to set all counters to the maximum value
        # across all counters
        elif cntnum == N + 1:
            M = m # update the last maxout value
        # wrong A value, return None when this happens
        else:
            return None
    # set all counters that are less than the last maxout
    # value to the maxout value and return the answer
    return [ M if c < M else c for c in counters]
