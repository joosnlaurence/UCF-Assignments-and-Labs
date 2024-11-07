import sys 

'''
Calculates the numeric value of a string as if its characters are 
expressed in unsigned binary
'''
def convert_to_unsigned_binary(string):
    result = 0
    shamt = 8
    for c in string:
        result = result << shamt
        result += ord(c)

    return result

def byte_wide_checksum(string, bit_size):
    ''' 
Calculates the decimal checksum of a string with a bit/block size that can be 
expressed as an amount of bytes (i.e. is divisible by 8)
'''
    byte_size = bit_size // 8
    bitmask = 1 << bit_size -1
    checksum = 0
    for i in range(0, len(string), byte_size):
        block = string[i:i+byte_size]
        block_checksum = convert_to_unsigned_binary(block)
        checksum = (checksum + block_checksum)
        checksum &= bitmask     

    return checksum

if len(sys.argv) < 3:
    print("Usage: python pa02.py <filename> <checksum: 8, 16, 32>")
    sys.exit(1)

filename = sys.argv[1]
bit_size = int(sys.argv[2])
if bit_size not in {8, 16, 32}:
    print("Error: Checksum must be 8, 16, or 32")
    sys.exit(1)

try: 
    with open(filename, 'r') as file:
        string = file.read()
        byte_size = bit_size // 8
        pad_size = (byte_size - (len(string) % byte_size)) % byte_size
        string += 'X' * pad_size

        strlen = len(string)
        print()
        for i in range(0, len(string), 80):
            print(string[i:i+80])

except FileNotFoundError:
    print(f"File '{filename}' was not found.")

checksum = byte_wide_checksum(string, bit_size)
print(f"{bit_size:2d} bit checksum is {checksum:8x} for all {len(string):4d} chars")