# TODO


def main():
    input = get_user_input()
    print(grade_level(input))


def get_user_input():
    s = input("Text: ")
    return s


def grade_level(input):
    level = round(coleman_liau_index(input))
    if level >= 16:
        return "Grade 16+"
    elif level < 1:
        return "Before Grade 1"
    else:
        return f"Grade {level}"


def coleman_liau_index(input):
    # Step 1: Count total number of letters
    letters = sum(1 for char in input if char.isalpha())

    # Step 2: Count total number of sentences
    modified_input = input.replace("...", "###")
    periods = modified_input.count(".")
    exclamations = modified_input.count("!")
    question = modified_input.count("?")
    ellipses = modified_input.count("###")
    sentences = periods + exclamations + question + ellipses

    # Step 3: Count total number of words
    words = len(input.split())

    # Step 4: Calculate average number of letters per word
    letters_per_word = letters / words

    # Step 5: Calculate average number of sentences per word
    sentences_per_word = sentences / words

    # Step 6: Calculate average number of letters per 100 words
    L = letters_per_word * 100

    # Step 7: Calculate average number of sentences per 100 words
    S = sentences_per_word * 100

    # Step 8: Calculate the Coleman-Liau index
    return 0.0588 * L - 0.296 * S - 15.8


main()
