from collections import defaultdict

adj = defaultdict(list)  # creation of our adjacency list so it can be accessed anywhere
arr = []


def dfs(u, v):  # Referenced chapter 22 DFS
    for dest, src in v:  # the prerequisites will have the course: requisite thus we make a tuple out of it
        adj[src].append(dest)  # our tuple with (destination, source) or (prerequisite, course) is appended to our adjacency list
    color = {k: "white" for k in u}  # then what we do is we have a dictionary of colors to keep track, starting with all of our nodes as white

    for v_ in u: 
        if color[v_] == "white":  # if the node is white, then we call dfs-visit
            dfs_visit(v_, color)
			
    return arr[::-1]


def dfs_visit(G, u):  # Referenced chapter 22 DFS
    u[G] = "gray"  # change to gray
    for v in adj[G]: 
        if u[v] == "white":  # if the node is white, then we visit it and color it gray
            dfs_visit(v, u)
    u[G] = "black"  #blacken; we are finished
    arr.append(G)  # we are adding it the the array

file = open("input.txt", 'r')
output = open("output.txt", "w+")

course = []
prereqs = []
for fifo in file:
    fifo = fifo.split(":")
    fifo[1] = fifo[1].split()
    course.append(int(fifo[0]))
    for idx in fifo[1]:
        prereqs.append([int(fifo[0]), int(idx)])  # our nodes have tuple format (string, int)


for idx in dfs(course, prereqs):
    output.write(str(idx) + " ")

output.close()