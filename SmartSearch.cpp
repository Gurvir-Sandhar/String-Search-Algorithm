/*
Gurvir Sandhar
CS350
HW6

After compiled, this program can by ran by: ./a.out < test.txt
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


/**
 * Sets all array indexes to length of pattern
 * Then sets the correct shift number for all letters in pattern 
 *
 * @param my_array is an array for which each index represents the corresponding ascii char
 * @param pattern is the string we will be searching for
 * @param num is the length of pattern
 */
void set_ascii_array(int (&my_array)[256], string pattern, int num) 
{
	for(int i = 0; i < 256; i++)
	{
		my_array[i] = num;
	}
	
	int n = num - 1;
	for(int j = 0; j < num-1; j++)
	{
		my_array[pattern[j]] = n;
		n = n -1;
	}
}

/**
 * Searches text to find the pattern
 *
 * @param text is the string to search in
 * @param pattern is the string to find
 * @param my_array is the ascii table that will have shift numbers for each char 
 *
 * @return int of either the index at which the pattern begins, or -1 if it does not exist
 */
int search_text(string text, string pattern, const int my_array[256])
{
	int current_position = pattern.length() - 1;
	
	while (current_position < text.length())
	//do while current position is less than total length of text
	{
		int shift_space = my_array[text[current_position]]; //amount to shift pattern
		int temp = current_position; //index that will move right when indexes match

	 	if(text[current_position] == pattern[pattern.length()-1])
		//do if pattern index and text index match
		{
			for(int j = pattern.length() - 1; j >= 0; j--)
			//after initial match, check rest of chars of pattern
			{
				if(text[temp] != pattern[j])
				{
					current_position += shift_space;
					break;
				}
				else if (j == 0 && text[temp] == pattern[j])
				{
					return temp;
				}
				else
				{
					shift_space = my_array[text[temp]];
					temp -= 1;
				}
			}	
		}
		else
		//if text index and pattern index don't initially match
		{	
			current_position += shift_space;	
		}
	}
	return -1; //if pattern not found
}

int main() 
{
	string pattern;		
	string text;
	int num_line;
	
	cin >> num_line;
	cin >> pattern; 

	int ascii_array[256];
	set_ascii_array(ascii_array, pattern, pattern.length());

	if(num_line <= 0)
	{
		return -1; 
	}
	else
	{	
		cin.ignore();
		for(int i = 0; i < num_line; i++)
		{
	  		getline(cin, text);
			cout << search_text(text, pattern, ascii_array) << endl;		
		}
	}

	return 0;
}
