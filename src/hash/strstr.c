/*
 * For problem on LeetCode strstr()
 *
 * The intuitive solution will be O(|s|*|t|)
 *
 * However, we're going to use the hash table we just learned and 
 * reduce the time complexity to O(|s|+|t|)
 * (1) we need to implement hash table
 * (2) we need to create rolling hash ADT
 * (3) use Karp-Robin algorithm to solve the problem
 *
 * In fact, we don't need hash table, just hash function
 * But we'll extend that later in another exercise
 */

// use divide method: h(k) = k mod m, where m is prime-number > |s|

#include <math.h> //sqrt
#include <stdio.h>
#include <string.h>

#define ALPHA_BASE 256 // ASCII code

typedef struct {
    int u;          // pre-hash value
    int u_len;      // length of stored string
    int m;          // table size
    int hash;       // hash value
    int base;       // string -> number base
    long long factor;
} rolling_hash_t;

/*
 * return prime-number larger than num
 */
static int _find_prime(int num) {
    /*for (int j = num; ; j++) {
        int i = 0;
        int limit = (int) sqrt((double)j);
        for (i = 2; i < limit; i++) {
            if (num % i == 0) {
                break;
            }
        }
        if (i == limit) {
            return j;
        }
    }*/
    //return 1000000007;
    return 103;
}

static void _init(rolling_hash_t* r, int len, long long factor) {
    r->m = _find_prime(len+1); // find prime number
    r->hash = 0;
    r->base = ALPHA_BASE;
    r->factor = factor;
}

/*
 *  append char c to end of original string [----][c]
 *  shift orignal string left (* base)
 */
static void _append(rolling_hash_t* r, char c) {
    r->hash = (int) (r->hash * r->base + c) % r->m;
    //printf("appending %c, hash = %d\n", c, r->hash);
}

/*
 *  [c][----] -> [----]
 *  remove the upmost char number, c*base^(|u|-1)
 */
static void _skip(rolling_hash_t* r, char c) {
    r->hash = (int)r->hash - ((c*r->factor)%r->m);
    if (r->hash < 0) r->hash += r->m;
    //printf("skipped %c, hash = %d\n", c, r->hash);
}

static int _value(rolling_hash_t* r) {
    return r->hash;
}

int strStr(char* haystack, char* needle) {
    rolling_hash_t rt;
    rolling_hash_t rs;
    int s = strlen(needle);
    int t = strlen(haystack);
    if (s == 0) {
        return 0;
    } else if (s > t) {
        return -1;
    }
    
    int power = 1;
    for (int i = 0; i < s-1; i++) {
        power = (power * ALPHA_BASE) % 103;
    }

    _init(&rt, s, power);
    _init(&rs, s, power);
    for (int i = 0; i < s; i++) {
        // append all in needle to rs (rolling_hash)
        _append(&rs, needle[i]);
        // append first len(s) chars in t into rt (rolling-hash)
        _append(&rt, haystack[i]);
    }

    for (int i = 0; i < t - s + 1; i++) {
        if (i-1>=0) {
            _skip(&rt, haystack[i-1]);
            _append(&rt, haystack[i+s-1]);
        }
        //printf("compare (%d) (%d) \n", _value(&rs), _value(&rt));
        if (_value(&rs) == _value(&rt)) {
            int match = 0;
            for (int j = 0; j < s; j++) {
                if (haystack[i+j] == needle[j]) {
                    if (j == s-1) {
                        match = 1;
                    }
                } else {
                    break;
                }
            }
            if (match == 1) {
                return i;
            }
        }
    }
    return -1;
}

int main(int argc, char **argv)
{
    //char target[] = "mississippi";
    //char source[] = "issip";
    //char target[] = "hello";
    //char source[] = "ll";
    char target[] = "ababcaababcaabc";
    char source[] = "ababcaabc";
    printf("answer=%d\n", strStr(target, source));
}


#if 0 // intuitive solution
int strStr(char* haystack, char* needle) {
    int t = strlen(haystack);
    int s = strlen(needle);
    if (s == 0) {
        return 0;
    }
    
    for (int i = 0; i < t - s + 1; i++) {
        int match = 0;
        for (int j = 0; j < s; j++) {
            if (haystack[i+j] == needle[j]) {
                if (j == s-1) {
                    match = 1;
                }
            } else {
                break;
            }
        }
        if (match == 1) {
            return i;
        }
    }
    return -1;
}
#endif
