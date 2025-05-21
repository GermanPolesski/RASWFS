#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

// Word list (NULL-terminated)
char *w[] = {"PALKA", "LYAGUSHKA", "KAPLJ", "KARTA", NULL};

// Checks if the end of 's' matches the beginning of 'r'
bool test(const char *s, const char *r) {
    int s_len = strlen(s);
    if (s_len == 0) return true; // Empty string matches any beginning
    
    // Check all possible suffix lengths
    for (int match_len = s_len; match_len > 0; match_len--) {
        if (match_len > (int)strlen(r)) continue;
        
        // Compare end of 's' with start of 'r'
        if (strncmp(s + s_len - match_len, r, match_len) == 0) {
            return true;
        }
    }
    return false;
}

bool step(const char *lw) {
    setlocale(LC_ALL, "Russian");
    
    // Find first available word
    int n;
    for (n = 0; w[n] != NULL; n++) {
        if (strlen(w[n]) > 0) break;
    }
    
    if (w[n] == NULL) {
        printf("Цепочка построена!\n");
        return true;
    }
    
    for (n = 0; w[n] != NULL; n++) {
        if (strlen(w[n]) == 0) continue;
        
        char *original = w[n];
        if (test(lw, original)) {
            // Mark word as used
            w[n] = "";
            
            if (step(original)) {
                printf("%s\n", original);
                return true;
            }
            
            // Restore word if path failed
            w[n] = original;
        }
    }
    
    return false;
}

int main(void) {
    if (!step("")) {
        printf("Не удалось построить цепочку\n");
    }
    return 0;
}