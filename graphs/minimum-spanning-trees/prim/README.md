PRIM
  
This is my own implementation based on CLRS (https://mitpress.mit.edu/books/introduction-algorithms).
  
####Notes####  
* "Prim’s algorithm operates much like Dijkstra’s algorithm for finding shortest paths in a graph". In Dijkstra we care about finding the best route ```v->...->y``` that connects us to ```y```. In Prim we only care about the edge that connects us to ```y```. So the implementation only differs in the relaxing condition. Instead of checking whether the (current distance + the edge weight) is better, we only test if the current edge is better.
* "Prim’s algorithm has the property that the edges in the set A always form a single tree"
  
####Algorithm####  
* We initialize:
 * A visited array where each element is unvisited
 * A distance array where each element's distance is inifinity
 * A minimum heap

* We insert the start element in the minimum heap with ```distance = 0```

* We explore all the elements in the minimum heap until it's empty
 * We pop a node, ```v```, and mark it as visited (it is the element with the minimum distance by definition)
 * We look at all the **unvisited** neigbors of ```v```. For each neigbor ```y```:
   + we check if ```edgeWeight[v->y] < distance[y]```. Meaning, will this new edge ```v-y``` connect me to ```y``` in a cheaper way than the avaiable edge to ```y```?
    + We add ```y``` to the minimum heap but If ```y``` already exists, then we need to decrease its value in the minimum heap. (look at the implementation details for more details) 
  
####Example####  
to be added  
  
  
####Running Time####  
* "The running time of Prim’s algorithm depends on how we implement the min priority queue Q"
* "Each EXTRACT-MIN operation takes O(lgV) time, the total time for all calls to EXTRACT-MIN is O(VlgV)"
* We look at each edge in Prim at most twice when visiting the unvisited neigbors therefore the runing time for looking at all edges is O(E)
* "The DECREASE-KEY operation on the min-heap, which a binary min-heap supports in O(lgV) time"
* The total time for Prim’s algorithm is O(VlgV + ElgV) = O(ElgV)"
* By using Fibonacci heaps, Prim’s algorithm runs in time O(E + VlgV), which improves over the binary-heap implementation if |V| is much smaller than |E|
  
####Implementation Details####  
My implementation of decrease-key on a heap is slow because I do a linear search to find the node and then call bubble up. I should at least maintain pointers to the nodes in the heap so that I call bubble up right away without search. In CRLS however, it is noted that "We can in fact achieve a running time of O(Vlg(V) + E) by implementing the min-priority queue with a **Fibonacci heap** (see Chapter 19). The amortized cost of each of the |V| EXTRACT-MIN operations is O(lgV) , **and each DECREASE KEY call, of which there are at most |E|, takes only O(1)** [huh!] amortized time. Historically, the development of Fibonacci heaps was motivated by the observation that Dijkstra’s algorithm typically makes many more DECREASE-KEY calls than EXTRACT-MIN calls,"
  
  
####Practice Problem####
https://www.hackerrank.com/challenges/primsmstsub
  