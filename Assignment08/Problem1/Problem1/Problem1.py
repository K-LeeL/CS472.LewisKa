
# Assignment 08: Another Way To Soduku and Some Computational Complexity Thought Questions
# Due: Fri Apr 19 , 2024 11 : 59pm
#
# One can use graph coloring to solve a Soduku puzzle. 
# You then color this graph with nine colors numbered 1 to 9, starting by assigning the matching color
# for each given in the puzzle. Then , use the k - coloring functions in your favorite graph library to
# 9 - color the graph.
# Write a program that (1) Converts a Soduku puzzle stored in a 9x9 array into a graph, per the
# construction above, (2) uses your favorite graph library to 9 - color the resulting graph, (3) and then
# use the coloring to complete the puzzle

# https://www.geeksforgeeks.org/project-idea-genetic-algorithms-for-graph-colouring/?ref=header_search
# https://www.geeksforgeeks.org/graph-coloring-applications/?ref=header_search
# https://www.geeksforgeeks.org/graph-coloring-set-2-greedy-algorithm/?ref=header_search
# https://www.geeksforgeeks.org/check-if-given-sudoku-board-configuration-is-valid-or-not/?ref=header_search
# https://www.geeksforgeeks.org/program-sudoku-generator/?ref=header_search

# networkx is the library used to create the graph and color it
import networkx as nx

# matplotlib is used to plot the graph
import matplotlib.pyplot as plt

# Function to create the sudoku graph
def createSudokuGraph(initialBoard):
    
    # Create a graph with 81 nodes, one for each cell in the Sudoku board
    sudokuGraph = nx.Graph()
    
    # Add nodes to the graph with the values from the initial board
    for row in range(9):
        for col in range(9):
            sudokuGraph.add_node((row, col), value=initialBoard[row][col])

    # Add edges between nodes that share the same value or are empty
    for i in range(9):
        for j in range(9):
            for k in range(j + 1, 9):
                if initialBoard[i][j] == initialBoard[i][k] or initialBoard[i][j] == 0 or initialBoard[i][k] == 0:
                    sudokuGraph.add_edge((i, j), (i, k))

                if initialBoard[j][i] == initialBoard[k][i] or initialBoard[j][i] == 0 or initialBoard[k][i] == 0:
                    sudokuGraph.add_edge((j, i), (k, i))

    # Add edges for subgrids
    for rowStart in range(0, 9, 3):
        for colStart in range(0, 9, 3):
            
            subgridNodes = [(rowStart + i, colStart + j) for i in range(3) for j in range(3)]
            
            for i, u in enumerate(subgridNodes):
                for v in subgridNodes[i + 1:]:
                    if initialBoard[u[0]][u[1]] == initialBoard[v[0]][v[1]] or initialBoard[u[0]][u[1]] == 0 or initialBoard[v[0]][v[1]] == 0:
                        sudokuGraph.add_edge(u, v)
    return sudokuGraph

# Function to color the sudoku graph
def colorSudokuGraph(graph):
    
    # Get the colors of the nodes that have been assigned a value
    colors = {node: color for node, color in nx.get_node_attributes(graph, 'value').items() if color != 0}
    
    # If all nodes have been assigned a value, return True
    for node in graph.nodes():
        
        # If the node has not been assigned a value, assign a value to it or return False if no value can be assigned
        if graph.nodes[node]['value'] == 0:
            
            # Get the available colors for the node
            available_colors = set(range(1, 10)) - {colors[neighbor] for neighbor in graph.neighbors(node) if neighbor in colors}
            
            # Assign a color to the node and recursively call the function for the next node
            for color in available_colors:
                
                # Assign the color to the node
                graph.nodes[node]['value'] = color
                
                # Add the color to the colors dictionary
                colors[node] = color
                
                # Recursively call the function for the next node
                if colorSudokuGraph(graph):
                    return True          
                
                # If no value can be assigned to the node, remove the color and value assigned to it
                del colors[node]
                
            # If no value can be assigned to the node, set the value to 0 and return False
            graph.nodes[node]['value'] = 0
            
            return False
    return True

# Function to solve the Sudoku puzzle
def solveSudoku(initialBoard):
    
    sudokuGraph = createSudokuGraph(initialBoard)
    
    if colorSudokuGraph(sudokuGraph):
        solution = [[sudokuGraph.nodes[(i, j)]['value'] for j in range(9)] for i in range(9)]
        
        return solution
    else:
        return None

# Puzzle
initialBoard = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9]
]

solution = solveSudoku(initialBoard)
if solution:
    for row in solution:
        print(row)
else:
    print("No solution exists.")
