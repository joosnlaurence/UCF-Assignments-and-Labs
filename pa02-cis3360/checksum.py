import sys 

'''
Calculates the numeric value of a string as if its characters are 
expressed in unsigned binary
'''
def convert_to_unsigned_binary(string, bit_size):
    result = 0
    exp = bit_size - 8
    for c in string:
        result += ord(c) << exp
        exp -= 8

    return result

''' 
Calculates the decimal checksum of a string with a bit/block size that can be 
expressed as an amount of bytes (i.e. is divisible by 8)
'''
def byte_wide_checksum(string, bit_size):
    byte_size = bit_size // 8
    mod = 1 << bit_size
    checksum = 0
    for i in range(0, len(string), byte_size):
        block = string[i:i+byte_size]
        block_checksum = convert_to_unsigned_binary(block, bit_size)
        checksum = (checksum + block_checksum) % mod     

    return checksum

'''
Returns the decimal value represented in hexadecimal
'''
def int_to_hex(n):
    if n == 0:
        return '0'

    hex_values = ['0','1','2','3','4','5','6',
                  '7','8','9','a','b','c','d',
                  'e','f']
    hex_val = ''
    while n > 0:
        r = n % 16
        n //= 16
        hex_val = hex_values[r] + hex_val

    return hex_val

bit_size = 16
byte_size = bit_size // 8

string = "The highest forms of understanding we can achieve are laughter and human compassion. Richard Feynman\n"
pad_size = (byte_size - (len(string) % byte_size)) % byte_size
string += 'X' * pad_size

checksum = byte_wide_checksum(string, bit_size)
print(int_to_hex(checksum))