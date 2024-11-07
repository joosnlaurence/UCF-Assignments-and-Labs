import sys
import os

"""
Your program should open the input text files, 
1. echo the processed input to the screen, 
2. make the necessary calculations, 
3. and then output the checksum to the console (terminal) screen in the format described below.

The input file specified as the first command line argument, will consist of 
the valid 8 bit ASCII characters normally associated with the average text file. 
This includes punctuation, numbers, special characters, and whitespace.

1. Collect the command line input arguments and print them to the console. 
Remember to remove or comment out this test code when running the testing scripts.
2. Read the file and print it out to the console.
3. Adjust the out put to print 80 characters per line.
4. Calculate the 8 bit checksum. Remember that the checksum is a running total with no overflow.
5. Resolve the calculations and padding for both 16 and 32 bit checksums.    

"""


# create a throw error message function
# hex(255)
def print_stderr(msg: str) -> None:
    sys.stderr.write(msg + '\n')

def read_file_to_string(_file: str):
    file_str = ''
    with open(_file) as file:
        for line in file:
            for character in line:
                if character != '\n':
                    file_str += character
    return file_str


def format_checksum(data: str, width: int = 80) -> None:
    """

    printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, checksum, characterCnt);



    """
    for i in range(0, len(data), width):
        print(data[i:i + width])
    # var1 = 5
    # string: str = f 'the variable var1 is {5}'
    # return string

def calculate_checksum(size: int, data: str):
    """
    Divide input into uniform words (e.g., 2 byte blocks) of the checksum size

    Add all the words as unsigned binary numbers, discarding any overflow bits

    Interpret the result as a two’s complement number

    Use the negation of the result as the checksum value

    Append the checksum value to the end of the input

    >>> calculate_checksum()
    1
    >>> calculate_checksum("hello")
    output

    """

    checksum = 0
    block_size = size // 8
    # print("block size", block_size)
    if len(data) % block_size != 0:
        pad_size = block_size - (len(data) % block_size)
        data += 'X' * pad_size

    for i in range(0, len(data), block_size):
        # Get the current block of characters
        block = data[i:i + block_size]
        # Calculate the sum ASCII values of the characters in the block
        block_value = sum(ord(char) for char in block)
        checksum += block_value
        # print(block)
    return checksum
    # hex_dict = {'0': '0000', '1': '0001', '2': '0010', '3': '0011', '4': '0100', '5': '0101', '6': '0110', '7': '0111', '8': '1000', '9': '1001', 'a': '1010', 'b': '1011', 'c': '1100', 'd': '1101', 'e': '1110', 'f': '1111'}

    # num: int = 0xB37F19
    # num: str = 'B37F19'
    # num = num.lower()
    # bin
    # print('hex number', num)
    # binary_str = ''

    # for digit in num:
    #     print("current hex digit", hex_dict[digit])
    #     binary_str += hex_dict[digit]
    #     # we have to check to make sure the string isn't bigger than size
    #     if (len(binary_str) > size):
    #         binary_str = binary_str[i:i + size]
    #
    # digit1 = hex_dict[num[0]]
    # digit2 = hex_dict[num[1]]
    # print("digit one and two", digit1, digit2)
    #
    # sum = bin(int(digit1, 2) + int(digit2, 2))
    # # sum = bin(int(digit1, 16) + int(digit2, 16))
    # print("Final sum", int(sum, 2))

    # # twos compliment
    # # 1110 -> 0001 + 1 = 0010

    # # 1110
    # # 0010
    # # 10000
    # # # size = 8
    # # # div: num / size
    # # print()

    # return 0

# Input the required file name and the checksum size as command line parameters
def main():
    if len(sys.argv) < 3:
        print_stderr("Usage: script.py <filename> <checksum_size>")
        return
    file_name = sys.argv[1]
    checksum_size = int(sys.argv[2])

    if checksum_size not in (8, 16, 32):
        print_stderr("Checksum size must be 8, 16, or 32")
        return

    print(f"File name: {file_name}")
    print(f"Checksum size: {checksum_size}")

    data = read_file_to_string(file_name)
    print("File Content:")
    format_checksum(data)

    checksum = calculate_checksum(checksum_size, data)
    character_count = len(data)
    print(f"{checksum_size} bit checksum is {checksum:0{checksum_size // 4}x} for all {character_count: >4d} chars")
    # call the file
    #
    # sum = ''
    # int_sum = 0
    # with open('i3.txt') as file:
    #     for line in file:
    #         for character in line:
    #             if (character != '\n'):
    #                 sum += bin(int(character, 16)) + '\n'
    #                 print("number in binary", bin(int(character, 16)))
    #                 print("number that is added", int(bin(int(character, 16)), 2))
    #                 int_sum += int(bin(int(character, 16)), 2)
    # print(sum)
    # print(int_sum)
    # binary string back into an int(our_binary_string, 2)

    # 8, 16, 32

    # calculate_checksum(32, read_file_to_string('inWC2.txt'))

    # size = 8, 16, 32
    # file = data
    # if(len(file) > size):
    #creates a slice of a string (substring)
        # file = file[1:(size + 1) ]
        # print(file)

    # print(int(hex_string, 16) + int(binary_str, 2))



    # file = open(f"{file_name}", "r") 

    # s = 'The quick brown fox jumps over the lazy dog.'.encode('utf-8')
    # print(s.hex())

    # os.system("echo Print this to the screen")
    # calculate_checksum(8)
    # if __name__ == "__main__":
    #     main()

main()