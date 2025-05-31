#include<bits/stdc++.h>
using namespace std;

struct node{
    node* links[26];
    bool wordEnds = false;

    bool containsKey(char c){
        return (links[c - 'a'] != nullptr);
    }

    void put(char c, node* Node){
        links[c - 'a'] = Node;
    }

    node* get(char c){
        return links[c - 'a'];
    }

    void end(){
        wordEnds = true;
    }
};

class Trie{
    private: 
    node* root;

    public:
    Trie(){
        root = new node();
    }

    void insert(string word) {
        for(int i = 0; i < word.length(); i++){
            word[i] = tolower(word[i]);
        }

        node* curr = root;
        for(int i = 0; i < word.length(); i++){
            if(!(curr -> containsKey(word[i]))){
                curr -> put(word[i], new node());
            }
            curr = curr -> get(word[i]);
        }
        curr -> end();
    }

    bool search(string word) {
        for(int i = 0; i < word.length(); i++){
            word[i] = tolower(word[i]);
        }

        node* curr = root;
        for(int i = 0; i < word.length(); i++){
            if(!(curr -> containsKey(word[i]))) return false;
            curr = curr -> get(word[i]);
        }
        return (curr -> wordEnds);    
    }
    
    node* getRoot() { return root; }
};


// Time Complexity -> O(n*m) | Space Complexity -> O((n+1)*(m+1)); 
int editDistance(string s1, string s2) {
    int m = s1.length(), n = s2.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    

    for(int i = 0; i <= m; i++) dp[i][0] = i;  
    for(int j = 0; j <= n; j++) dp[0][j] = j; 
    
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            int cost = (s1[i-1] == s2[j-1]) ? 0 : 1;
            
            dp[i][j] = min({
                dp[i-1][j] + 1,      // deletion
                dp[i][j-1] + 1,      // insertion
                dp[i-1][j-1] + cost  // substitution
            });
            
            // Check for transposition (swap of adjacent characters)
            if(i > 1 && j > 1 && 
               s1[i-1] == s2[j-2] && s1[i-2] == s2[j-1]) {
                dp[i][j] = min(dp[i][j], dp[i-2][j-2] + cost);
            }
        }
    }
    
    return dp[m][n];
}


// DFS to find all words in trie with their edit distances
void findSuggestions(node* curr, string& target, string currentWord, 
                    vector<pair<int, string>>& suggestions, int maxEditDist) {
    if(curr->wordEnds) {
        int dist = editDistance(target, currentWord);
        if(dist <= maxEditDist) {
            suggestions.push_back({dist, currentWord});
        }
    }
    
    // Pruning: if current word is already too long compared to target
    if(currentWord.length() > target.length() + maxEditDist) {
        return;
    }

    
    for(int i = 0; i < 26; i++) {
        if(curr->links[i] != nullptr) {
            currentWord.push_back('a' + i);
            findSuggestions(curr->links[i], target, currentWord, suggestions, maxEditDist);
            currentWord.pop_back();
        }
    }
}

vector<string> getSuggestions(Trie& dictionary, string word, int maxEditDist = 2) {
    // Convert to lowercase
    for(int i = 0; i < word.length(); i++){
        word[i] = tolower(word[i]);
    }
    
    vector<pair<int, string>> suggestions;
    string currentWord = "";
    
    findSuggestions(dictionary.getRoot(), word, currentWord, suggestions, maxEditDist);
    
    // Sort by edit distance first, then alphabetically
    sort(suggestions.begin(), suggestions.end(), [](const pair<int,string>& a, const pair<int,string>& b) {
        if(a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });
    
    vector<string> result;
    for(auto& p : suggestions) {
        // cout << p.second << " found with Edit Distance : " << p.first << endl;
        result.push_back(p.second);
    }
    
    return result;
}

int main(){
    Trie dictionary;
    ifstream words("words.txt");    
    
    string s;
    // Insert all words into trie
    while(getline(words, s)){
        if(s.size()) dictionary.insert(s);
    }

    int n;
    cin >> n;

    while(n--){
        string s;
        cin >> s;
        
        if(dictionary.search(s)) {
            cout << "Found\n";
        } else {
            vector<string> suggestions = getSuggestions(dictionary, s, 2);
            
            cout << "Here are some relevant Suggestions: \n";
            for(int i = 0; i < min(5, (int)suggestions.size()); i++) {
                cout << i+1 << "-> " << suggestions[i] << "\n";
            }
            cout << endl;
        }
        cout << "---------------------------------------------------------------------------------------------------------\n";
    }
   
    return 0;
}