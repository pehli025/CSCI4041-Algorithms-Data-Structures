import math
from collections import defaultdict
MAX_INT = math.inf
def min_distance(dist, spt):
    global min_vert

    minimum = MAX_INT  # setting our minimum distance to infinity as a base
    for v in range(len(dist)):  # looping over vertices
        if dist[v] < minimum and spt[v] == False:  # checks to see if we have already visited this vertex yet
            minimum = dist[v]  # update minimum
            min_vert = v  # set our min_vert
            spt[v] = True  # that vertex is now visited so set it to true
    return min_vert

def bellmanford(G, edges):  # implementation of Bellman-Ford algorithm based on CLRS
    dist = [MAX_INT] * (len(G) + 1)  # initialize single source
    dist[len(G)] = 0

    for i in range(len(G)):
        for (src, des, weight) in edges:  # src - starting point, des - destination, weig - edge weight
            if dist[src] + weight < dist[des]:
                dist[des] = dist[src] + weight
				
        for (src, des, weight) in edges:  # looping over each edge
            if dist[src] + weight < dist[des]:
                return False
				
        return dist[0:len(G)]  # mod_weight


def dijkstra(G, s): 
    dist = [MAX_INT] * len(G)  # initialize single source
    dist[s] = 0

    spt = defaultdict(lambda: False)

    for count in range(len(G)): # current vertex is at min distance from source not yet included in path
        current = min_distance(dist, spt) # current min vertex 
        for v in range(len(graph)):
            if dist[v] > (dist[current] + G[current][v]):
                dist[v] = (dist[current] + G[current][v])
    return dist



def johnson_algorithm(G): #references johnson algorithm in from textbook 
    edges = []  # collection of edges for later computation
    for i in range(len(G)):  # edges for bellmanford
        for j in range(len(G[i])):
            if G[i][j] != 0:
                edges.append([i, j, G[i][j]])

    for i in range(len(G)):  #
        edges.append([len(G), i, 0])

    mod_weight = bellmanford(G, edges)  # defining our mod_weight calculated from Bellman-Ford
    mod_graph = [[0 for x in range(len(G))]
        for y in range(len(G))]  # 

    for i in range(len(G)):
        for j in range(len(G[i])):
            mod_graph[i][j] = (G[i][j] + mod_weight[i] - mod_weight[j])  # computation of new weights

    adj = []  #creation of adjacency matrix
    for v in range(len(G)):  # finding shortest path
        adj.append(dijkstra(mod_graph, v))
    return adj  # return our new adjacency matrix of updated values


output = open("output.txt", "w+")

with open('input.txt', 'r') as f:
    graph = [[int(num) for num in line.split()] for line in f]
graph = johnson_algorithm(graph)

for i in graph:
    for j in i:
        output.write(str(j) + " ")
    output.write("\n")

output.close()