/**********************************************************************\
|*  HTTP Header Parser						      
|*						    		      
|*  author: Christopher Hartman				      	      
|*  created: 12/16/2014						      
|*  last modified: 12/22/2014		
|*
|*  summary:  This is a parsing program that takes in one argument,
|*  an input text file.  This program will then go through the text
|*  file and count the number of occurrences of recognized headers.
|*  Unrecognized headers are ignored.  Headers must contain a ':'
|*  character after it to be valid.  At the end, the program will
|*  print the number of occurrences for each header. 
|*
|*  how to compile:  gcc HTTP_Parser.c -o HTTP_Parser
|*
|*  how to run:      HTTP_Parser input_file.txt     
|*
|*  example line of input file:  "Accept: text/plain"
\**********************************************************************/


#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct header header;

// Header struct for keeping track of the counted occurrences for a given header.
struct header{
	char* name;
	int count;
};

// Use the input header to see what position in the hash table to check to see
// if this header is a valid one.  It returns the position in the hash
// table that this header should be in based on the first character of 
// the header.  The values should range from 0 to 25 representing from A to Z.

// The intention of hashing is so that there are fewer places for the program to
// check to see if a given header is valid.  For example, only look at valid letter
// 'A' headers if the given header starts with an 'A'.
int hash_header(char *header){
	char firstChar = *header;

	int hash_value = firstChar - 'a';

	// If negative, we have a first character that is capitalized.
	if(hash_value < 0){
		hash_value = firstChar - 'A';
	}
	
	return hash_value;
}



int main(int argc, char *argv[]){

	if(argc != 2){
		printf("Please use the input text file as the only argument.");
	}

	else{

		FILE *input_file = fopen( argv[1], "r" );

		char any_key_input;
	
		int hash_value;
	
		printf("To begin the HTTP Header Parser, press any key to continue");
	
		 any_key_input = getchar();

		// An array of pointers, with each pointer starting at the first index of the
		// related character header array.  For example, the a_headers start at index
		// 0 in the hash table, c_headers at index 2, and so on.
		header *hash_table[26];

		// Initialize all of the hash table to NULL pointers;
		int p = 0;
		while(p < 26){
			hash_table[p] = NULL;
			p++;
		}


		/**		HEADER DEFINITIONS		**/
		// Define the arrays of header structs for each character that is used for a header.
		header a_headers[8];
		a_headers[0].name = "Accept";
		a_headers[0].count = 0;
		a_headers[1].name = "Accept_Charset";
		a_headers[1].count = 0;
		a_headers[2].name = "Accept_Encoding";
		a_headers[2].count = 0;
		a_headers[3].name = "Accept_Language";
		a_headers[3].count = 0;
		a_headers[4].name = "Accept_Ranges";
		a_headers[4].count = 0;
		a_headers[5].name = "Age";
		a_headers[5].count = 0;
		a_headers[6].name = "Allow";
		a_headers[6].count = 0;
		a_headers[7].name = "Authorization";
		a_headers[7].count = 0;
		hash_table[0] = a_headers;

		header c_headers[9];
		c_headers[0].name = "Cache_Control";
		c_headers[0].count = 0;
		c_headers[1].name = "Connection";
		c_headers[1].count = 0;
		c_headers[2].name = "Content_Encoding";
		c_headers[2].count = 0;
		c_headers[3].name = "Content_Language";
		c_headers[3].count = 0;
		c_headers[4].name = "Content_Length";
		c_headers[4].count = 0;
		c_headers[5].name = "Content_Location";
		c_headers[5].count = 0;
		c_headers[6].name = "Content_MD5";
		c_headers[6].count = 0;
		c_headers[7].name = "Content_Range";
		c_headers[7].count = 0;
		c_headers[8].name = "Content_Type";
		c_headers[8].count = 0;
		hash_table[2] = c_headers;

		header d_headers[1];
		d_headers[0].name = "Date";
		d_headers[0].count = 0;
		hash_table[3] = d_headers;

		header e_headers[3];
		e_headers[0].name = "ETAG";
		e_headers[0].count = 0;
		e_headers[1].name = "Expect";
		e_headers[1].count = 0;
		e_headers[2].name = "Expires";
		e_headers[2].count = 0;
		hash_table[4] = e_headers;
	
		header f_headers[1];
		f_headers[0].name = "From";
		f_headers[0].count = 0;
		hash_table[5] = f_headers;

		header h_headers[1];
		h_headers[0].name = "Host";
		h_headers[0].count = 0;
		hash_table[7] = h_headers;

		header i_headers[5];
		i_headers[0].name = "If_Match";
		i_headers[0].count = 0;
		i_headers[1].name = "If_Modified_Since";
		i_headers[1].count = 0;
		i_headers[2].name = "If_None_Match";
		i_headers[2].count = 0;
		i_headers[3].name = "If_Range";
		i_headers[3].count = 0;
		i_headers[4].name = "If_Unmodified_Since";
		i_headers[4].count = 0;
		hash_table[8] = i_headers;

		header l_headers[2];
		l_headers[0].name = "Last_Modified";
		l_headers[0].count = 0;
		l_headers[1].name = "Location";
		l_headers[1].count = 0;
		hash_table[11] = l_headers;

		header m_headers[1];
		m_headers[0].name = "Max_Forwards";
		m_headers[0].count = 0;
		hash_table[12] = m_headers;

		header p_headers[3];
		p_headers[0].name = "Pragma";
		p_headers[0].count = 0;
		p_headers[1].name = "Proxy_Authenticate";
		p_headers[1].count = 0;
		p_headers[2].name = "Proxy_Authorization";
		p_headers[2].count = 0;
		hash_table[15] = p_headers;

		header r_headers[3];
		r_headers[0].name = "Range";
		r_headers[0].count = 0;
		r_headers[1].name = "Referer";
		r_headers[1].count = 0;
		r_headers[2].name = "Retry_After";
		r_headers[2].count = 0;
		hash_table[17] = r_headers;

		header s_headers[1];
		s_headers[0].name = "Server";
		s_headers[0].count = 0;
		hash_table[18] = s_headers;

		header t_headers[3];
		t_headers[0].name = "TE";
		t_headers[0].count = 0;
		t_headers[1].name = "Trailer";
		t_headers[1].count = 0;
		t_headers[2].name = "Transfer_Encoding";
		t_headers[2].count = 0;
		hash_table[19] = t_headers;

		header u_headers[2];
		u_headers[0].name = "Upgrade";
		u_headers[0].count = 0;
		u_headers[1].name = "User_Agent";
		u_headers[1].count = 0;
		hash_table[20] = u_headers;

		header v_headers[2];
		v_headers[0].name = "Vary";
		v_headers[0].count = 0;
		v_headers[1].name = "Via";
		v_headers[1].count = 0;
		hash_table[21] = v_headers;

		header w_headers[2];
		w_headers[0].name = "Warning";
		w_headers[0].count = 0;
		w_headers[1].name = "WWW_Authenticate";
		w_headers[1].count = 0;
		hash_table[22] = w_headers;

		// Begin reading the input file.
		if(input_file == 0){
			printf("Error: Could not open file.\n");
		}

		else{
			int hash_value = 0;
			char *current_line = NULL;
			char *current_header = NULL;
			size_t length = 0;
			ssize_t read;

			header *current_hashed_header = NULL;
			
			// Read in the input file line by line for headers.  Ignore non-recognized headers.
			while ((read = getline(&current_line, &length, input_file)) != -1) {
				// Split the current line at the ":" to extract the header.
				current_header = strtok(current_line, ":");
				
				if(current_header != NULL){ 
					hash_value = hash_header(current_header);
					
					// If we have an alphabetic first character for the hash value, continue.
					if(hash_value >= 0 && hash_value < 26){
						int i = 0;
						int found_real_header = 0;
						current_hashed_header = hash_table[hash_value];

						// Loop through the array of hashed headers until a matching header has been
						// found.  Keep going until the hash value is not the same as the current
						// hashed header (ie if we're looking through letter 'A' headers, keep going
						// until we're not looking at letter 'A' headers in the hash table.
						while(found_real_header == 0 && (hash_value == hash_header(current_hashed_header[i].name))){
							if(strcmp(current_header, current_hashed_header[i].name) == 0){
								found_real_header = 1;
							}
							else{
								i++;
							}
						}

						// If the current header is one that we're looking for, then increment its count.
						if(found_real_header == 1){
						   current_hashed_header[i].count = current_hashed_header[i].count + 1;	
						}
					
						i = 0;
					}
				}
           	}

			header *header_array = NULL;

			// Now print the counted occurrences of each header.
			int j = 0;
			while(j < 26){
				header_array = hash_table[j];
				if(header_array != NULL){
					int k = 0;
					while(hash_header(header_array[k].name) == j){
						printf("%s was seen %d\n", header_array[k].name, header_array[k].count);
						k++;
					}			
				}
				j++;	
			}
		
		}

	}

	return 0;
}