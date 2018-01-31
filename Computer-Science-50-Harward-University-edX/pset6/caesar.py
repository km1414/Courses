import sys
import cs50


def main():

    # checking whether number of arguments is correct
    if len(sys.argv) != 2:
        print("Wrong number of arguments!")
        exit(1)

    # extracts integer from input
    number = int(sys.argv[1])

    # text input from user
    text = cs50.get_string("plaintext:  ")

    print("ciphertext: ", end = "")

    # iterating over all characters in string
    for letter in text:

        # if character is alphabetical:
        if letter.isalpha():

            # if character is uppercase:
            if letter.isupper():
                print(chr((ord(letter) - ord('A') +  number) % 26 + ord('A')), end = "")

            # if character is lowercase:
            else:
                print(chr((ord(letter) - ord('a') +  number) % 26 + ord('a')), end = "")

        # if character is non-alphabetical:
        else:
            print(letter, end = "")
    # new line
    print()

    # great success
    exit(0)


# executes function
if __name__ == "__main__":
     main()

