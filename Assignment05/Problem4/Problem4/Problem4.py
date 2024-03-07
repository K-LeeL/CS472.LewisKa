# Assignment 05: Greedy Dynamic Programming
# Due : Wed Mar 6 , 2024 11 : 59pm

# Problem 4:
# Prove by counterexample that the greedy approach to problem solving does not always 
# yield an optimal solution for the Making Change problem when the coins are U.S. coins 
# and we do not have at least one of each type of coin

# The greedy approach to making change is to always use the largest coin possible.
# For example, if the amount of change to make is 30 cents, the greedy approach would
# use a quarter, a nickel, and a nickel. However, if there are no nickels available,
# the greedy approach would use a quarter and 5 pennies, which is not optimal.

# https://www.geeksforgeeks.org/greedy-algorithm-to-find-minimum-number-of-coins/


def make_change_greedy(amount, coins):
    # amount: the amount of change to make
    num_coins = 0
    # change: the coins used to make the change
    change = []

    # Sort the coins in descending order
    for coin in sorted(coins, reverse=True):
        # While the amount is greater than or equal to the coin
        while amount >= coin:
            # Subtract the coin from the amount
            amount -= coin
            # Add the coin to the change
            change.append(coin)
            # Increment the number of coins
            num_coins += 1

    # Return the number of coins and the change
    return num_coins, change

def main():
    # U.S. coins
    coins = [25, 10, 1] 
    # Amount of change to make
    amount = 30
    
    # Greedy approach
    num_coins_greedy, change_greedy = make_change_greedy(amount, coins)

    print("Greedy approach:")
    print("Number of coins:", num_coins_greedy)
    print("Coins used:", change_greedy)
    
    # Counter example: No nickels available
    if 5 not in coins:
        print("\nCounterexample:")
        print("No nickels available.")
        print("Using only quarters, dimes, and pennies.")
        
        # Amount of change to make
        num_coins_counter, change_counter = make_change_greedy(amount, coins)
        print("Number of coins:", num_coins_counter)
        print("Coins used:", change_counter)

# Run the main function
if __name__ == "__main__":
    main()
