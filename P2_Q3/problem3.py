import math

def insert(A, key):
    #removed line 1 from book because we are decreasing key count
    A.append(math.inf)
    decrease_key(A, len(A) - 1, key)

def min_heapify(A, i):  # references textbook max heapify changed for min
    l = 2 * i
    r = 2 * i + 1
    length = len(A)
    if l < length and A[l] < A[i]:  # checks if left child is less than root
        smallest = l
    else:
        smallest = i
    if r < length and A[r] < A[smallest]:   # checks if right child is less than current smallest
        smallest = r
    if smallest != i:
        temp = A[i]
        A[i] = A[smallest]
        A[smallest] = temp
        min_heapify(A, smallest)


def decrease_key(A, i, key):  # referenced heap increase key chapter 6 pg 164
    if key[0] > A[i]:
        print("ERROR: new key cannot be larger than current key")
        return

    A[i] = key
    while i and A[math.floor(i / 2)] > A[i]:
        temp = A[i]
        A[i] = A[math.floor(i / 2)]
        A[math.floor(i / 2)] = temp
        i = math.floor(i / 2)
		
def extract_min(A):  # all of this follows the pseudo code from CLRS
    length = len(A)
    if length < 1:
        return
    min = A[0] # set the min to a default first index of the array
    A[0] = A[length - 1] 
    A.pop(length - 1)  # using pop() to decrease the size of the array 
    min_heapify(A, 0)
    return min

def dijkstra(G, w, s):  # referenced Dijkstra's from textbook pg: 658 - 662
    q = []  # initialize set of Vertices
    d = {k: math.inf for k in G}  # initialize single source, we set all the vertexes to edge distance infinity.
    S_ = []  # initialize an array to store each of the vertexes we traverse to get to our end point

    d[w] = 0  # set the starting vertex to s.d = 0
    q.append((0, w))  # adding G.V to Q

    while q: # A continuous loop 
        u, v = extract_min(q)  # setting vertexes to the min
        for n, w_ in G[v]:  # starting Relax, relaxation based on sections 24.2-24.3
            if d[n] > u + w_:
                d[n] = u + w_
                S_.append(v)  # add the vertex we just travelled to to our path list
                insert(q, (u + w_, n))
    S_.append(s) 

    result_path = list(dict.fromkeys(S_))  # formatting our path
    result = " "
    for i in result_path: # putting into string
        result = result + i + " "
    return str(d[s]) + ":" + result  # the resulted path taken


file = open("input.txt", 'r')
output = open("output.txt", "w+")
w, s = file.readline().split()
result_matrix = {}
i = 0

for fifo in file: 
    temp = []
    fifo = fifo.split()
    for j in range(len(fifo)):
        if i != j:
            temp.append((str(j), int(fifo[j])))  # taking in the vertex as a string and its weight as an int
            result_matrix[str(i)] = temp # add it to our matrix of nodes
    i += 1


output.write(dijkstra(result_matrix, str(w), str(s)))

output.close()