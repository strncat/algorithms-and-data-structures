DIJKSTRA

This is my own implementation based on CLRS (https://mitpress.mit.edu/books/introduction-algorithms).

####Description####
"Dijkstra’s algorithm solves the single-source shortest-paths problem on a weighted, directed graph G = (V, E) for the case in which all edge weights are nonnegative"

"The algorithm maintains a set S of vertices whose final shortest-path weights from the source s have already been determined. The algorithm repeatedly selects the vertex u in V - S with the minimum shortest-path estimate, adds u to S, and relaxes all edges leaving u"

####Algorithm####
* We initialize:
 * A visited array where each element is unvisited
 * A distance array where each element's distance is inifinity
 * A minimum heap

* We insert the start element in the minimum heap with ```distance = 0```

* We explore all the elements in the minimum heap until it's empty
 * We pop a node, ```v```, and mark it as visited (it is the element with the minimum distance by definition)
 * We look at all the **unvisited** neigbors of ```v```. For each neigbor ```y```:
   + we check if ```distance[v] + edgeWeight[v->y] < distance[y]```. Meaning, can I get to ```y``` faster if I go through the node ```v```? If yes then we update the distance to that value.
    + We add ```y``` to the minimum heap but If ```y``` already exists, then we need to decrease its value in the minimum heap. (look at the implementation details for more details) 

####Example####
to be added

####Implementation Details####

I implement my own minimum heap with a decrese key operation which runs in O(log(V)) since I call bubble up after I decrease the key of a node. In CRLS however, it is noted that "We can in fact achieve a running time of O(Vlg(V) + E) by implementing the min-priority queue with a **Fibonacci heap** (see Chapter 19). The amortized cost of each of the |V| EXTRACT-MIN operations is O(lgV) , **and each DECREASE KEY call, of which there are at most |E|, takes only O(1)** [huh!] amortized time. Historically, the development of Fibonacci heaps was motivated by the observation that Dijkstra’s algorithm typically makes many more DECREASE-KEY calls than EXTRACT-MIN calls,". I should do that next!


####Practice Problem####
https://www.hackerrank.com/challenges/dijkstrashortreach
