===============================================================================
                    Smart Autocorrect System
===============================================================================

OVERVIEW
--------
A C++ implementation of an intelligent spell checker that uses a Trie data 
structure for efficient word storage and retrieval, combined with the 
Damerau-Levenshtein edit distance algorithm to provide smart word suggestions 
for misspelled words.

FEATURES
--------
- Fast Word Lookup: Uses a Trie  data structure for O(m) word 
  search complexity, where m is the length of the word
- Intelligent Suggestions: Implements Damerau-Levenshtein edit distance 
  algorithm to find similar words
- Case Insensitive: Automatically converts input to lowercase for consistent 
  matching
- Configurable Edit Distance: Adjustable maximum edit distance for suggestion 
  sensitivity (default: 2)
- Sorted Results: Suggestions are sorted by edit distance first, then 
  alphabetically
- Batch Processing: Process multiple words in a single run

ALGORITHM DETAILS
-----------------

Trie Data Structure:
- Time Complexity: O(m) for insertion and search operations
- Space Complexity: O(ALPHABET_SIZE × N × M) where N is number of words and M 
  is average word length
- Efficient prefix-based storage reduces memory usage for common prefixes

Damerau-Levenshtein Edit Distance:
The spell checker uses an enhanced version of edit distance that supports four 
operations:
- Insertion: Adding a character
- Deletion: Removing a character  
- Substitution: Replacing a character
- Transposition: Swapping two adjacent characters

Time Complexity: O(n × m) where n and m are the lengths of the two strings 
being compared
Space Complexity: O(n × m)

REQUIREMENTS
------------
- C++17 or later
- A dictionary file named 'words.txt' containing one word per line
- Standard C++ libraries (iostream, fstream, vector, algorithm, etc.)


INSTALLATION & SETUP
--------------------

1. Clone or download the project files

2. Compile the program:
   g++ Trie.cpp -o Trie.exe -std=c++17

USAGE
-----

1. Run the program:
   ./Trie

2. Input format:
   - First, enter the number of words you want to check
   - Then enter each word on a separate line

3. Example interaction:
   3
   apple
   Found
   ---------------------------------------------------------------------------
   programing
   Not found.
   Here are some relevant Suggestions: programming program programs programme 
   ---------------------------------------------------------------------------
   compter
   Not found.
   Here are some relevant Suggestions: computer compter compete complete 
   ---------------------------------------------------------------------------

CODE STRUCTURE
--------------

Classes and Structures:

node Structure:
- Represents a single node in the Trie
- Contains an array of 26 pointers (for a-z)
- Boolean flag to mark word endings
- Helper methods for key operations

Trie Class:
- insert(string word): Adds a word to the dictionary
- search(string word): Checks if a word exists in the dictionary
- getRoot(): Returns the root node for traversal

Key Functions:

editDistance(string s1, string s2):
Calculates the Damerau-Levenshtein distance between two strings, supporting:
- Character insertion, deletion, substitution
- Adjacent character transposition
- Dynamic programming optimization

findSuggestions(node* curr, string& target, ...):
Performs DFS traversal of the Trie to find all words within the specified 
edit distance:
- Includes pruning optimization to avoid unnecessary branches
- Collects words with their corresponding edit distances

getSuggestions(Trie& dictionary, string word, int maxEditDist):
Main suggestion engine that:
- Finds all candidate words within edit distance threshold
- Sorts results by edit distance, then alphabetically
- Returns top suggestions for user

PERFORMANCE CHARACTERISTICS
---------------------------

Time Complexity:
- Dictionary Loading: O(N × M) where N = number of words, M = average word 
  length
- Word Search: O(M) where M = word length
- Suggestion Generation: O(W × M × T) where W = dictionary size, M = word 
  length, T = target word length

Space Complexity:
- Trie Storage: O(ALPHABET_SIZE × N × M)
- Edit Distance DP: O(M × T) for each comparison

Optimizations Implemented:
- Early Pruning: Skips Trie branches when current word exceeds reasonable 
  length
- Efficient Sorting: Custom comparator for optimal suggestion ordering
- Memory Management: Proper node allocation and linking

CUSTOMIZATION
-------------

Adjusting Edit Distance Threshold:
Change the default maximum edit distance (currently 2):
vector<string> suggestions = getSuggestions(dictionary, s, 3); // Allow up to 3 edits

Limiting Number of Suggestions:
Modify the output loop to show more/fewer suggestions:
for(int i = 0; i < min(5, (int)suggestions.size()); i++) { // Show up to 10 suggestions

Adding More Character Support:
To support additional characters beyond a-z, modify:
- Array size in node structure
- Character mapping in containsKey, put, and get methods


CONTRIBUTING
------------
Feel free to submit issues and enhancement requests. Some areas for improvement:
- Memory optimization for large dictionaries
- Parallel processing for suggestion generation
- GUI implementation


===============================================================================
