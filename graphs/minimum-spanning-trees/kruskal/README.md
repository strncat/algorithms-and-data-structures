KRUSKAL

This is my own implementation based on CLRS (https://mitpress.mit.edu/books/introduction-algorithms).

####Description/Notes####
* "Kruskal uses a disjoint-set data structure to maintain several disjoint sets of elements."
* "Each set contains the vertices in one tree of the current forest. The operation FIND-SET(u) returns a representative element from the set that contains u. Thus, we can determine whether two vertices u and belong to the same tree by testing whether FIND-SET(u) equals FIND-SET(v) To combine trees, Kruskal’s algorithm calls the UNION procedure."

####Algorithm####
* We initialize V sets where the leader of each set is just the vertex itself
* We initialize a set to hold the minimum spanning tree
* We sort all edges in the graph and we go through all edges in a loop
 * if both end points ```x,y``` of the edge belong to different sets (they don't have the same leader) then
    + we can safely add this edge to our minimum spanning tree set
    + we combine both sets so that they will have the same leader


####Example####
to be added


####Running Time####
* "The running time of Kruskal’s algorithm depends on how we implement the disjoint-set data structure." We we use Union-by-Rank for this implemention"
* The time to make each in the begining is just O(V)
* the time to sort the edges is O(ElgE)
* We perform 2*E FIND-SET so that's O(Elg(V)) and at most (V-1) UNION operations = O(V). 
* The total time is then O(ElgE) = O(ElgV) which is similar to Prim


####Practice Problem####
https://www.hackerrank.com/challenges/kruskalmstrsub
