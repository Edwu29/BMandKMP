/*  Program: Lab7, Pattern Matching algorithms. BF, BM, KMP.
	Author: Edward Wu
	Class: CSCI 230
	Date: 04.23.2020
	Description:

	I certify that the code below is my own work.

	Exception(s): N/A

*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int BMmatch(const string& text, const string& pattern, int& compares);
std::vector<int> buildLastFunction(const string& pattern);
int KMPmatch(const string& text, const string& pattern, int& compares);
std::vector<int> computeFailFunction(const string& pattern);
int BFmatch(const string& text, const string& pattern, int& compares);
int main()
{
	int compares = 0;
	string text = "a pattern matching algorithm";
	string pattern1 = "rithm";
	string pattern2 = "rithn";
	string T = "GTTTATGTAGCTTACCTCCTCAAAGCAATACACTGAAAA";
	string P = "CTGA";
	string P2 = "CTGG";

	int option;
	cout << "Choose a pattern matching algorithm: " << endl;
	cout << "1. Brute Force" << endl;
	cout << "2. Boyer-Moore" << endl;
	cout << "3. Knuth-Morris-Pratt" << endl;
	cin >>option;

	switch (option)
	{
		int match, match2, match3, match4;
	case 1:
		match = BFmatch(text, pattern1, compares);
		if (match == -1)
		{
			cout << "The pattern does not match," << " number of comparisons is " << compares << endl;
		}else cout << "There is a match at index " << match << " with " << compares << " comparisons" << endl;
		
		match2 = BFmatch(text, pattern2, compares);
		if (match2 == -1)
		{
			cout << "The pattern does not match," << " number of comparisons is " << compares << endl;
		}

		match3 = BFmatch(T, P, compares);
		if (match3 == -1)
		{
			cout << "The pattern does not match," << " number of comparisons is " << compares << endl;
		}
		else cout << "There is a match at index " << match3 << " with " << compares << " comparisons" << endl;
		match4 = BFmatch(T, P2, compares);
		if (match4 == -1)
		{
			cout << "The pattern does not match," << " number of comparisons is " << compares << endl;
		}
		else cout << match4 << endl;
		break;
	case 2:
		match = BMmatch(text, pattern1, compares);
		cout <<"There is a match at index "<< match <<" with "<<compares<<" comparisons"<< endl;
		match2 = BMmatch(text, pattern2, compares);
		if (match2 == -1)
		{
			cout << "The pattern does not match,"<<" number of comparisons is "<<compares << endl;
		}

		match3 = BMmatch(T, P, compares);
		if (match3 == -1)
		{
			cout << "The pattern does not match," << " number of comparisons is " << compares << endl;
		}
		else cout << "There is a match at index " << match3 << " with " << compares << " comparisons" << endl;
		match4 = BMmatch(T, P2, compares);
		if (match4 == -1)
		{
			cout << "The pattern does not match," << " number of comparisons is " << compares << endl;
		}
		else cout << match4 << endl;
		break;
	case 3:
		match = KMPmatch(text, pattern1, compares);
		cout << "There is a match at index " << match << " with " << compares << " comparisons" << endl;
		match2 = KMPmatch(text, pattern2, compares);
		if (match2 == -1)
		{
			cout << "The pattern does not match," << " number of comparisons is " << compares << endl;
		}
		match3 = KMPmatch(T, P, compares);
		if (match3 == -1)
		{
			cout << "The pattern does not match," << " number of comparisons is " << compares << endl;
		}
		else cout << "There is a match at index " << match3 << " with " << compares << " comparisons" << endl;
		match4 = KMPmatch(T, P2, compares);
		if (match4 == -1)
		{
			cout << "The pattern does not match," << " number of comparisons is " << compares << endl;
		}
		else cout << match4 << endl;
		break;
	default:
		break;
	}
	
	system("pause");
	return 0;
}

int BMmatch(const string& text, const string& pattern, int& compares) {
	compares = 0;
	std::vector<int> last = buildLastFunction(pattern);
	int n = text.size();
	int m = pattern.size();
	int i = m - 1;
	if (i > n - 1) // pattern longer than text?
		return -1; // . . .then no match
	int j = m - 1;
	do {
		compares++;
		if (pattern[j] == text[i])
		{
			if (j == 0) { return i; } // found a match
			else { // looking-glass heuristic
				i--; j--; // proceed right-to-left
			}
		}
		else { // character-jump heuristic
			i = i + m - std::min(j, 1 + last[text[i]]);
			j = m - 1;
		}
	} while (i <= n - 1);
	return -1; // no match
} // construct function last
std::vector<int> buildLastFunction(const string& pattern) {
	const int N_ASCII = 128; // number of ASCII characters
	int i;
	std::vector<int> last(N_ASCII); // assume ASCII character set
	for (i = 0; i < N_ASCII; i++) // initialize array
		last[i] = -1;
	for (i = 0; i < pattern.size(); i++) {
		last[pattern[i]] = i; // (implicit cast to ASCII code)
	}
	return last;
}
int KMPmatch(const string& text, const string& pattern, int& compares) {
	compares=0;
	int n = text.size();
	int m = pattern.size();
	std::vector<int> fail = computeFailFunction(pattern);
	int i = 0; // text index
	int j = 0; // pattern index
	while (i < n) {
		compares++;
		if (pattern[j] == text[i]) {
			if (j == m - 1)
				return i - m + 1; // found a match
			i++; j++;
		}
		else if (j > 0) j = fail[j - 1];
		else i++;
	}return -1; // no match
}
std::vector<int> computeFailFunction(const string& pattern) {
	std::vector<int> fail(pattern.size());
	fail[0] = 0;
	int m = pattern.size();
	int j = 0;
	int i = 1;
	while (i < m) {
		if (pattern[j] == pattern[i]) { // j + 1 characters match
			fail[i] = j + 1;
			i++; j++;
		}
		else if (j > 0) // j follows a matching prefix
			j = fail[j - 1];
		else { // no match
			fail[i] = 0;
			i++;
		}
	}return fail;
}
int BFmatch(const string& text, const string& pattern, int& compares)
{
	compares = 0;
	int n = text.size();
	int m = pattern.size();
	for (int i = 0;i <= n - m;i++)
	{
		int j = 0;
		compares++;
		while (j < m && text[i + j] == pattern[j])
		{
			j++;
		}
		if (j == m)
		{
			return i;
		}
	}
	
	return-1;
}