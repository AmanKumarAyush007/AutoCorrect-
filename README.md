AUTOCORRECT SYSTEM

---

1. INTRODUCTION
This project implements a basic autocorrect system in C++. It uses a Trie (prefix tree) to store a dictionary of words and a dynamic programming algorithm to calculate the Edit Distance (Damerau-Levenshtein distance) between words. When a word isn't found in the dictionary, the system suggests potential corrections based on their edit distance.

---

2. SYSTEM COMPONENTS

The system is built from three main parts:

2.1. Trie Data Structure
   - Purpose: Efficiently stores dictionary words for fast lookup and prefix matching.
   - Implementation: Uses a `node` struct for each character in a word path and a `Trie` class to manage the overall dictionary.
   - Key Features:
     - `node`: Contains an array of 26 pointers (`links`) for child nodes (a-z) and a `wordEnds` flag to mark the end of a valid word.
     - `Trie`: Provides methods to `insert` words into the dictionary and `search` for their existence. It also exposes the `root` node for traversal by other functions.

   - IMPORTANT NOTE ON MEMORY MANAGEMENT:
     The current `node` struct lacks a constructor to initialize its `links` array to `nullptr`. This can lead to uninitialized pointers and undefined behavior.
     The `Trie` class also lacks a destructor (`~Trie()`). Without it, all dynamically allocated `node` objects will cause memory leaks when a `Trie` object is destroyed.
     These should be addressed for robust production-level code.

2.2. Edit Distance Algorithm (`editDistance` function)
   - Purpose: Calculates the Damerau-Levenshtein distance between two strings. This metric quantifies the minimum number of single-character operations required to change one word into another.
   - Operations Considered:
     - Insertion
     - Deletion
     - Substitution
     - Transposition (swapping adjacent characters)
   - Time Complexity: O(M * N), where M and N are the lengths of the two strings.

2.3. Suggestion Generation (`findSuggestions` and `getSuggestions` functions)
   - Purpose: Finds words in the dictionary that are "close" to a given misspelled word based on their edit distance.
   - `findSuggestions` (Recursive DFS):
     - Traverses the Trie recursively, building `currentWord`s.
     - When a valid word (`wordEnds` is true) is found in the Trie, it calculates its `editDistance` to the `target` (misspelled) word.
     - If the distance is within a `maxEditDist` threshold, the word is added to a list of suggestions.
     - Includes basic pruning to avoid exploring overly long paths.
   - `getSuggestions`:
     - Initiates the `findSuggestions` process from the Trie's root.
     - Converts the input word to lowercase before processing.
     - Sorts the collected suggestions:
       1. Primary sort: By increasing edit distance.
       2. Secondary sort: Alphabetically for words with the same edit distance.
     - Returns a `vector` of recommended strings.

---

3. HOW TO USE

3.1. Prerequisites:
   - C++ compiler (e.g., g++).
   - A `words.txt` file in the same directory as your executable, containing one dictionary word per line.

3.2. Compilation:
   Navigate to your source code directory in a terminal and compile using g++ (assuming your code is in `main.cpp`):

g++ main.cpp -o autocorrect -std=c++17 -Wall


3.3. Running the System:
After successful compilation, run the executable from your terminal:

./autocorrect

The program will first load words from `words.txt`. Then, it will prompt you to enter an integer `n`, followed by `n` words one by one.

- If an entered word is found in the dictionary, it prints "Found".
- If not found, it prints "Here are some relevant Suggestions:" followed by up to 5 suggestions, ranked by edit distance and then alphabetically.

---

