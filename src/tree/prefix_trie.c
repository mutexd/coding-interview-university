typedef struct trie_s{
    bool val;
    struct trie_s* children[26];
} Trie;

/** Initialize your data structure here. */
Trie* trieCreate(void) {
    Trie* t = malloc(sizeof(Trie));    
    memset(t, 0, sizeof(Trie));
    return t;
}

/** Inserts a word into the trie. */
void trieInsert(Trie* obj, char* word) {
    if (word == NULL) return;
    if (word[0] == '\0') {
        obj->val = true;
        return;
    }
    char c = word[0] - 'a';
    if (obj->children[c] == NULL) {
        obj->children[c] = trieCreate();
    }
    trieInsert(obj->children[c], word + 1);
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* obj, char* word) {
    if (word == NULL) return true;
    if (obj == NULL) return false;
    if (word[0] == '\0') {
        return obj->val;
    }
    char c = word[0] - 'a';
    return trieSearch(obj->children[c], word + 1);
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* obj, char* prefix) {
    if (prefix == NULL) return true;
    if (obj == NULL) return false;
    char c = prefix[0] - 'a';
    if (prefix[0] == '\0') {
         // if there is any child, return true
        for (int i = 0; i < 26; i ++) {
            if (obj->children[i] != NULL) {
                return true;
            }
        }
        return obj->val;
    } else {
        return trieStartsWith(obj->children[c], prefix + 1);
    }
}

void trieFree(Trie* obj) {
    free(obj);
}
