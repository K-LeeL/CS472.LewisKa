# Assignment 05: Greedy Dynamic Programming
# Due : Wed Mar 6 , 2024 11 : 59pm
#
# Problem 1
# Arbitrage is the use of discrepancies in currency-exchange rates to make a profit.
# For example, there may be a small window where 1 U.S.dollar buys 0.75 British pounds,
# 1 British pound buys 2 Australian dollars, and 1 Australian dollar buys 0.70 U.S.dollars.
# At such a time, a smart trader can trade one U.S.dollar and end up with 0.75 ∗ 2 ∗ 0.7
# = 1.05 U.S.dollars — a profit of 5%.
# Suppose that there are n currencies c1 , . . . , cn and an n ∗ n table R of exchange rates,
# such that one unit of currency ci buys R [ i , j ] units of currency cj.
# Devise and analyze an algorithm to determine the maximum value of
# R [ c1 , ci1 ]R [ ci1 , ci2 ]R [ cik−1 , cik ]R [ cik , c1 ]
#
# HINT: Think about how to express this as a graph problem then see if you can use the
# all - pairs shortest path algorithm to find a solution.
# And feel free to use either Boost : Graph or NetworkX to solve this problem,
# remember “You Ain’t Going to Need It, And If You Do, Somebody Has Already Done It.”.

# https://networkx.org/documentation/stable/reference/algorithms/generated/networkx.algorithms.shortest_paths.dense.floyd_warshall.html
# https://www.geeksforgeeks.org/bellman-ford-algorithm-simple-implementation/
# https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/
# https://www.geeksforgeeks.org/arbitrage-opportunity-in-currency-exchange/

# networkx for the creation of complex networks
import networkx as nx
import numpy as np

# function to find the maximum product of exchange rates
def max_exchange_rate(currencies, exchange_rates):
    # create a directed graph
    G = nx.DiGraph()

    # add nodes to the graph
    G.add_nodes_from(currencies)

    # add edges to the graph
    for i in range(len(currencies)):
        # add edges from each currency to every other currency
        for j in range(len(currencies)):
            # add edge only if different
            if i != j:
                # add edge with weight 
                G.add_edge(currencies[i], currencies[j], weight=-np.log(exchange_rates[i][j]))

    try:
        # find the shortest path 
        shortest_paths = dict(nx.all_pairs_bellman_ford_path_length(G))
        
        # find the maximum product
        max_product = float('-inf')

        for ci in currencies:
            # find the product of the shortest paths
            product = shortest_paths['c1'][ci] + shortest_paths[ci]['c1']
            
            # take the exponential of the negative product
            product = np.exp(-product)
            
            # update the maximum product
            if product > max_product:
                max_product = product

        return max_product
    
    # if negative cycle detected
    except nx.NetworkXUnbounded:
        return "Negative cycle detected. Arbitrage opportunity exists."

# test the function
currencies = ['c1', 'c2', 'c3']

exchange_rates = [
    [1.0, 0.75, 0.7],
    [1.33, 1.0, 0.95],
    [1.43, 1.05, 1.0]
]

max_product = max_exchange_rate(currencies, exchange_rates)
print("Maximum product of exchange rates:", max_product)
