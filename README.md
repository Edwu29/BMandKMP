# BMandKMP
Performs the Boyer Moore and Knutt Morris Pratt pattern matching algorithm.

BM compares the characters from right to left(known as the looking glass heuristic). If there is a mismatch, we do a character jump. The number of character jumps depend on computing the function : i = i + m - min(j, 1 + last[text[i]]).
