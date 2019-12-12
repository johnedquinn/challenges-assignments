#!/usr/bin/env python3

# @file   : program.py
# @author : John Ed Quinn
# @desc   : N/A

import collections
import sys

# @name : read_graph
# @desc : read the graph
def read_graph():
    graph = collections.defaultdict(set)
    for line in sys.stdin:
        if line[0] == '%':
            break
        s, t = map(int, line.split())
        graph[s].add(t)
        graph[t].add(s)
    return graph

# @func : find_circuit
# @desc : Recursive DFS traversal
def find_circuit(graph, start, vertex, visited, path):
    # If we have returned to start, return path
    if len(path) == len(graph.keys()):
        if start in graph[vertex]:
            return path
        else:
            return None

    # Visit each unvisited neighbor
    for neighbor in sorted(graph[vertex]):
        if neighbor in visited:
            continue

        # Mark visited
        visited.add(neighbor)

        # Add to path
        path.append(neighbor)

        # Recurse
        if find_circuit(graph, start, neighbor, visited, path):
            return path

        # Remove from path
        path.pop(-1)

        # Unmark visited
        visited.remove(neighbor)

    # No circuit found, so return nothing (should never happen!)
    return []

# @name : Find Eulerian Circuit
# @desc : Iteratively compute subcircuit until all edges have been travsrsed or no circuit is possible
def find_hamiltonian_circuit(graph):
    smallest = sorted(graph.keys())[0]
    start    = smallest
    visited  = set()                 # Visited edges (set of edge ordinals)
    visited.add(start)
    circuit  = []                    # Eulerian circuit (list of edges)
    index    = 0                     # Where in circuit to insert subcircuit

    while start:
        # Find Circuit
        circuit    = find_circuit(graph, start, start, visited, [start])

        # Check if any nodes in current circuit have an unvisited neighbor
        start = None
        for neighbor in sorted(graph[start]):
            if neighbor not in visited:
                start = vertex
                break
            
    # Make sure the circuit is not None
    if circuit:
        circuit.append(smallest)
        return circuit
    else:
        return None

# @func : main
# @desc : main driver
if __name__ == '__main__':
    while sys.stdin.readline():
        # Get graph info
        graph   = read_graph()
        circuit = find_hamiltonian_circuit(graph)
        
        # Formatted print
        if circuit:
            print(" ".join(str(n) for n in circuit))
        else:
            print("None")