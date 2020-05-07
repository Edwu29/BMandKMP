# BMandKMP
Performs the Boyer Moore and Knutt Morris Pratt pattern matching algorithm.

BM compares the characters from right to left(known as the looking glass heuristic). If there is a mismatch, we do a character jump. The number of character jumps depend on computing the function : i = i + m - min(j, 1 + last[text[i]]). Note: BM computes a last occurance function that stores the index of the last occuring character in the pattern.

KMP computes a failure function in a table. Once there is a mismatch at j, the you look at the failure function at j-1 and then it determines where j is supposed to be aligned in the text. The j index is placed just after the prefix of P that must match. (A little more complicated to describe and trace than the BM algorithm)
