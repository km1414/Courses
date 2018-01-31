import cs50


def main():

    # infinite loop
    while True:

        # gets input from user
        dollars = cs50.get_float("O hai! How much change is owed? \n")

        # if input incorrect - starts loop again
        if dollars < 0:
            continue

        # converts dollars to cents
        cents = round(dollars * 100)

        coins = 0

        # checking all nominals from the biggest
        for value in [25, 10, 5, 1]:

            # adds coins already given
            coins += cents // value

            # counts cents left
            cents = cents % value

        print(coins)

        exit(0)

# executes function
if __name__ == "__main__":
     main()