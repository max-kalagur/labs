#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 500

// To compile: gcc lab6.c -o lab6 -lm

int main()
{
// Варіант №12
// З клавіатури послідовно уводяться речення англійською мовою. Визначити, з якою частотою у тексті зустрічається кожна з букв мови (частотний аналіз всього тексту). Кількість речень визначає користувач інтерактивно.

    char str[MAX];

    char letters[27];   // 26 letters + \0
    strcpy(letters, "");

    int letterAmounts[26];

    puts("enter sentence:\n");
    fgets(str, MAX, stdin);

    for( int i=0; str[i]; i++ ) {

        char c = tolower(str[i]);

        if( isalpha(c) ) {

            int isNew = 1;

            for(int ii=0; letters[ii]; ii++) {
                if( letters[ii] == c ) {
                    letterAmounts[ii]++;
                    isNew = 0;
                }
            }
            
            if( isNew ) {

                int len = strlen(letters);
                letters[len] = c;
                letters[len+1] = '\0';
                letterAmounts[len] = 1;
            }
        }
    }

    for(int i = 0; letters[i]; i++ ) {
        printf("%c: %d\n", letters[i], letterAmounts[i]);
    }

/* Output:
    enter sentence:

    William Shakespeare, Shakespeare also spelled Shakspere, byname Bard of Avon or Swan of Avon, (baptized April 26, 1564, Stratford-upon-Avon, Warwickshire, England—died April 23, 1616, Stratford-upon-Avon), English poet, dramatist, and actor often called the English national poet and considered by many to be the greatest dramatist of all time.
    w: 4
    i: 15
    l: 15
    a: 34
    m: 6
    s: 18
    h: 8
    k: 4
    e: 29
    p: 11
    r: 18
    o: 20
    d: 15
    b: 5
    y: 3
    n: 19
    f: 6
    v: 4
    t: 20
    z: 1
    u: 2
    c: 4
    g: 4

*/

    return 0;
}