# you can write to stdout for debugging purposes, e.g.
# print("this is a debug message")

def solution(A):
    # write your code in Python 3.6

    # counts how many circles start and stop at any given array index
    # circles that start (or stop) beyond the array edges are counted
    # as starting (or stopping) at the edges
    nstartstop = [[int(0)]*2 for _ in range(len(A))]
    
    for i,a in enumerate(A):
        # count how many circles start at each array index,
        # count all circles that start below zero as starting at zero 
        nstartstop[0 if i-a < 0 else i-a][0] += 1
        # count how many circles end at each array index; count circles
        # that end beyond the maximum index as ending at the maximum index
        nstartstop[len(A)-1 if i+a >= len(A) else i+a][1] += 1

    noverlap = 0 # counts the total number of overlaps 
    nstarted = 0 # counts how many circles started and not ended at any given array index
    for i,ss in enumerate(nstartstop):
        
        # count the circles that started so far
        nstarted += ss[0]

        # count the overlaps which is 
        # [(number of circles that started so far) - 1] + 
        # [(number of circles that started so far) - 2]
        # + ... [(number of started circles that started so far) - 
        # (number circles that ended here)]
        # = (nstarted  - 1) + (nstarted - 2) + ... (nstarted - ss[1]) = 
        # nstarted * ss[1] - (1+2+...ss[1]) = nstated * ss[1] - (ss[1]*(ss[1]+1))/2
        noverlap += nstarted*ss[1] - (ss[1]*(ss[1] + 1)) // 2

        # remove circles that ended from the total count of started circles
        nstarted -= ss[1]

    # the problem wants -1 if the number of overlaps is larger than 10000000
    if noverlap > 10000000:
        noverlap = -1

    #return the answer
    return noverlap
