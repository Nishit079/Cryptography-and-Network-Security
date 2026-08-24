#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
char m[5][5];   /* the 5x5 Playfair matrix */
 
/* Build matrix from keyword */
void buildMatrix(char *key) {
    int used[26] = {0};
    used['J'-'A'] = 1;       /* I and J share one cell, so block J */
    int r = 0, c = 0;
 
    /* place keyword letters first (no repeats) */
    for (int i = 0; key[i]; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';
        if (!used[ch-'A']) {
            used[ch-'A'] = 1;
            m[r][c] = ch;
            if (++c == 5) { c = 0; r++; }
        }
    }
    /* fill remaining letters A-Z */
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J' || used[ch-'A']) continue;
        m[r][c] = ch;
        if (++c == 5) { c = 0; r++; }
    }
}
 
/* find row/col of a letter */
void find(char ch, int *r, int *c) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (m[i][j] == ch) { *r = i; *c = j; return; }
}
 
/* Convert plaintext into digraph pairs (insert X for double letters, pad odd length) */
int makePairs(char *text, char *pairs) {
    char clean[100];
    int n = 0;
    for (int i = 0; text[i]; i++)
        if (isalpha((unsigned char)text[i])) {
            char ch = toupper(text[i]);
            clean[n++] = (ch == 'J') ? 'I' : ch;
        }
 
    int i = 0, j = 0;
    while (i < n) {
        char a = clean[i];
        char b = (i+1 < n) ? clean[i+1] : 'X';
        if (a == b) {                 /* double letter -> insert filler X */
            pairs[j++] = a; pairs[j++] = 'X';
            i += 1;
        } else {
            pairs[j++] = a; pairs[j++] = b;
            i += 2;
        }
    }
    pairs[j] = '\0';
    return j;
}
 
/* mode = +1 for encrypt, -1 for decrypt */
void process(char *pairs, char *out, int mode) {
    int r1, c1, r2, c2;
    for (int i = 0; pairs[i]; i += 2) {
        find(pairs[i], &r1, &c1);
        find(pairs[i+1], &r2, &c2);
 
        if (r1 == r2) {                                  /* same row */
            out[i]   = m[r1][(c1 + 5 + mode) % 5];
            out[i+1] = m[r2][(c2 + 5 + mode) % 5];
        } else if (c1 == c2) {                            /* same column */
            out[i]   = m[(r1 + 5 + mode) % 5][c1];
            out[i+1] = m[(r2 + 5 + mode) % 5][c2];
        } else {                                          /* rectangle */
            out[i]   = m[r1][c2];
            out[i+1] = m[r2][c1];
        }
    }
    out[strlen(pairs)] = '\0';
}
 
int main() {
    char key[50], plain[100], pairs[100], cipher[100], back[100];
 
    printf("Enter Keyword: ");
    scanf("%s", key);
    printf("Enter Plain Text: ");
    scanf("%s", plain);
 
    buildMatrix(key);
 
    printf("\nMatrix:\n");
    for (int i = 0; i < 5; i++, printf("\n"))
        for (int j = 0; j < 5; j++) printf("%c ", m[i][j]);
 
    makePairs(plain, pairs);
    printf("\nPlaintext pairs : %s\n", pairs);
 
    process(pairs, cipher, +1);
    printf("Cipher text     : %s\n", cipher);
 
    process(cipher, back, -1);
    printf("Decrypted text  : %s\n", back);
 
    return 0;
}
 