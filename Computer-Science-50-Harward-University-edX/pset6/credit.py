import cs50


def main():

    # infinite loop
    while True:

        # gets input from user
        number = cs50.get_int("Number: ")

        # if input incorrect - starts loop again
        if not number >= 0:
            continue

        number_str = str(number)
        length = len(number_str)

        # value for test
        test_sum = 0

        # secont-to-last digit
        digit_num = length - 2

        # executes algorithm for every second digit from secont-to-last
        while digit_num >= 0:
            # doubles every number in sequence
            product = str(int(number_str[digit_num]) * 2)
            # adds every digit of product to test_sum
            for i in product:
                test_sum += int(i)
            digit_num -= 2

        # last digit
        digit_num = length - 1

        # executes algorithm for every second digit form last
        while digit_num >= 0:
            # adds every digit to test_sum
            test_sum += int(number_str[digit_num])
            digit_num -= 2

        # True if test was successful
        test = test_sum % 10 == 0
        # two first digits of card number
        begin = int(number_str[0:2])

        # checking all conditions
        if test and (begin == 34 or begin == 37) and length == 15:
            print("AMEX")

        elif test and begin >= 51 and begin <= 5 and length == 16:
            print("MASTERCARD")

        elif test and str(begin)[0] == '4' and (length == 13 or length == 16):
            print("VISA")

        else:
            print("INVALID")

        exit(0)


# executes function
if __name__ == "__main__":
     main()