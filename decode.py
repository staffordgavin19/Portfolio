def decode(message_file):
    with open(message_file, 'r') as file:
        lines = file.readlines()

    wordList = []

    for i, line in enumerate(lines):
        num, word = line.strip().split(' ')
        num = int(num)

        if num == ((i + 1) * (i + 2)) // 2:
            wordList.append(word)

    decodeMessage = ' '.join(wordList)
    return decodeMessage

decodeMessage = decode("encoded_message.txt")
print(decodeMessage)