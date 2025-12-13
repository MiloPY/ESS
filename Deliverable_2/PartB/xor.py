def hex_xor_transform(hex_string: str) -> str:
    """
    Takes a space-separated string of hex values (e.g., "00 ff 74 a2"),
    performs a bitwise XOR operation with 0x42 on each byte, and returns
    the result in the same space-separated hex format.

    Args:
        hex_string: The input string of hex bytes separated by spaces.

    Returns:
        The output string of XORed hex bytes separated by spaces.
    """
    # 1. Split the string into individual hex byte strings
    hex_bytes = hex_string.split()

    # Define the XOR key (0x42 in decimal is 66)
    key = 0x42

    output_bytes = []
    for hex_byte in hex_bytes:
        try:
            # 2. Convert the hex string to an integer
            # '74' -> 116
            byte_value = int(hex_byte, 16)

            # 3. Perform the XOR operation
            # 116 ^ 66
            xor_result = byte_value ^ key

            # 4. Convert the resulting integer back to a 2-character hex string
            # and pad with a leading zero if necessary (e.g., 5 -> '05')
            # The '02x' format string handles this: 0-padding, 2 characters wide, hex format.
            output_hex = f'{xor_result:02x}'

            output_bytes.append(output_hex)

        except ValueError:
            # Handle cases where a token is not a valid hex string (e.g., empty space)
            print(f"Warning: Skipped invalid hex token: '{hex_byte}'")
            continue

    # 5. Join the processed hex strings back into a single space-separated string
    return ' '.join(output_bytes)

# --- Example Usage ---

# The input provided by the user
input_hex = "4b 03 00 08"

print(f"Input Hex:  {input_hex}")

# Perform the transformation
output_hex = hex_xor_transform(input_hex)

print(f"XOR Key:    0x42")
print(f"Output Hex: {output_hex}")







