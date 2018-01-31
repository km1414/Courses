import cs50


def main():

    # infinite loop
    while True:

        # gets input from user
        height = cs50.get_int("Height: ")

        # if input correct:
        if height >= 0 and height <= 23:

            # prints all lines of pyramid and quits
            for i in range(height + 1):
                print((height - i) * " " + i * "#" + "  " + i * "#")
            exit(0)

        # else - starts loop from beginning
        else:
            continue

# executes function
if __name__ == "__main__":
     main()