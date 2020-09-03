# Legend
## Anything between {} is a parameter
## [o] means Optional
## // then anything is a comment

# Program level
## add graph {name} // Add a new graph
## rem graph {name} // Remove a graph
## sel graph {name} // Select a graph and move the application to Graph level

# Graph level
## add vertex {id} [o]{x} [o]{y} // Add a new vertex
## add edge {id1} {id2} // Add a new edge
## rem vertex {id} // Remove a vertex
## rem edge {id1} {id2} // Remove a edge
## bfs // Make a breadth-first search (busca em largura)
## dfs // Make a depth-first search (busca em profundidade)
