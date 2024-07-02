import sys


def state_to_string(state):
    stateBuilder = []

    for i in range(63, -1, -1):
        bit = (state >> i) & 1
        stateBuilder.append(str(bit) + " ")

        if i % 8 == 0:
            row = i // 8
            stateBuilder.append("|" + str(row + 1))
            stateBuilder.append("\n")

    stateBuilder.append("---------------\n")
    stateBuilder.append("a b c d e f g h\n")
    return ''.join(stateBuilder)


def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <state>")
        sys.exit(1)

    try:
        # The 0 base allows for base inference (e.g., 0x for hex).
        state = int(sys.argv[1], 0)
    except ValueError as e:
        print("Error: Please ensure the state is an integer.")
        sys.exit(1)

    result = state_to_string(state)
    print(result)


if __name__ == "__main__":
    main()
