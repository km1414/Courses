import sys
import crypt


def main():

    # checking whether number of arguments is correct
    if len(sys.argv) != 2:
        print("Wrong number of arguments!")
        exit(1)

    # extracts integer from input
    hashed = sys.argv[1]

    # getting "salt"
    salt = hashed[:2]

    # string of possible characters (with space in the beginning)
    chars = " AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"

    # iterates over every character in password
    for a in chars:
        for b in chars:
            for c in chars:
                for d in chars:

                    # joins all 4 characters and removes spaces
                    password = (a + b + c + d).strip()

                    # hashes the password
                    hashed_new = crypt.crypt(password, salt)

                    # if hash fits - password decrypted
                    if hashed == hashed_new:
                        print(password)
                        exit(0)

    # if not successful
    print("Couldn't decrypt password")
    exit(2)


# executes function
if __name__ == "__main__":
     main()

