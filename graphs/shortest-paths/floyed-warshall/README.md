Floyd-Warshall

Source: CLRS / Algorithm Design Manual

####Description/Notes####
* Floyd-Warshall computes all pairs shortest paths on a directed graph G
* Floyd-Warshall assumes that no negative-weight cycles exist in the graph
* "For any pair of vertices ```i```, ```j```, consider all paths from i to j whose intermediate vertices are all drawn from ```{1,2,...,k}```, and let ```p``` be a minimum-weight path from among them. (Path p is simple.)"


####Algorithm####
to be added


####Example####
to be added


####Running Time###
For a graph with ```V``` vertices, the running time is ```O(V^3)```


####Applications####
* "Consider the blackmail graph, where there is a directed edge ```(i,j)``` if person ```i``` has sensitive-enough private information on person ```j``` so that ```i``` can get ```j``` to do whatever he wants. You wish to hire one of these ```n``` people to be your personal representative. Who has the most power in terms of blackmail potential?"
* "Computing the graph’s diameter, the longest shortest-path distance over all pairs of vertices"

####Implementation Details####


####Practice Problem####
https://www.hackerrank.com/challenges/floyd-city-of-blinding-lights
