import os
import glob
from collections import defaultdict

def get_words_in_line(line):
    delims = " ,.\"'\n"
    words = []
    c_input = list(line)
    while c_input:
        # Find the first character not in delims
        while c_input and c_input[0] in delims:
            c_input.pop(0)

        # Break if there are no more non-delimiter characters
        if not c_input:
            break

        # Find the end of the current token
        end_index = 0
        while end_index < len(c_input) and c_input[end_index] not in delims:
            end_index += 1

        # Extract the token
        token = "".join(c_input[:end_index])
        words.append(token)
        c_input = c_input[end_index:]
    
    return words

def count_input_words(file_path):
    word_counts = defaultdict(int)
    with open(file_path, 'r') as file:
        for line in file:
            words = get_words_in_line(line)
            for word in words:
                word_counts[word] += 1
    return word_counts

def count_output_words(file_path):
    word_counts = defaultdict(int)
    with open(file_path, 'r') as file:
        for line in file:
            word, freq = line.split(' ')
            word_counts[word] += int(freq)
    return word_counts

def compare_word_counts(map1, map2):
    return map1 == map2

input_dir = 'bin'
output_dir = 'bin/output'

input_word_counts = defaultdict(int)
output_word_counts = defaultdict(int)

input_filenames = []
with open('bin/config.ini', 'r') as file:
  for line in file:
    if line.startswith('input_files='):
      input_filenames = line.split('=')[1].strip().split(',')
      break
  
print(input_filenames)

# Count words in input files
for file_name in input_filenames:
    file_path = os.path.join(input_dir, file_name)
    if os.path.isfile(file_path):
        word_counts = count_input_words(file_path)
        for word, count in word_counts.items():
            input_word_counts[word] += count

# Count words in output files
for file_name in os.listdir(output_dir):
    file_path = os.path.join(output_dir, file_name)
    if os.path.isfile(file_path):
        word_counts = count_output_words(file_path)
        for word, count in word_counts.items():
            output_word_counts[word] += count

# Compare the word counts
are_identical = compare_word_counts(input_word_counts, output_word_counts)

# print(input_word_counts)
# print(output_word_counts)

# Print the results
print(f"Are the word counts identical? {are_identical}")

if not are_identical:
    print("Differences:")
    for word in input_word_counts:
        if input_word_counts[word] != output_word_counts[word]:
            print(f"{word} {input_word_counts[word]} {output_word_counts[word]}")
