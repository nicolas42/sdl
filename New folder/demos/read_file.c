#include <stdio.h>
// #include <ctype.h>
#include <stdlib.h>




void read_file (char *filename, char **ret_char_array, int *ret_char_length)
{
	// allocate a character array
    char *char_array = (char*)malloc(4000);
	int chars_allocated = 4000;
	int char_length = 0;
	
    // open file to read
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		char err[200];
		snprintf(err, 200, "Error in opening file %s", filename);
		perror(err);
		return;
	}

	while (1) {
		// read a character
		int character = fgetc(file);
		// at the end add a null byte and exit
		if (feof(file)) { 
			char_array[char_length] = '\0'; 
            // cstrings don't count the null byte in the length
			break; 
		}
		char_array[char_length] = (char)character;
		char_length += 1;

        // double the allocation size if the char array has reached capacity
        if (char_length == chars_allocated){
            chars_allocated *= 2;
            char_array = (char*)realloc(char_array, chars_allocated);
            // printf("chars_allocated %d\n", chars_allocated);
        }

	}
	fclose(file);
	
    *ret_char_array = char_array;
    *ret_char_length = char_length;
}



// // Print file out slowly
// // https://www.reddit.com/r/Cprog/comments/kaapdr/prints_itself/
// #include <stdio.h>
// #include <unistd.h>
// #include <stdint.h>


// int prints_itself(void)
// {
//     FILE *file = fopen("./"__FILE__, "r");
//     uint16_t tick = UINT16_MAX;

//     for (;;) {
//         while (!feof(file)) {
//             usleep(tick -= ftell(file));
//             fputc(fgetc(file), stderr);
//         }
//         rewind(file);
//     }
// }


static void print_char(unsigned char theChar) {

    switch (theChar) {

        case '\n':
            printf("\\n");
            break;
        case '\r':
            printf("\\r");
            break;
        case '\t':
            printf("\\t");
            break;
        default:
            if ((theChar < 0x20) || (theChar > 0x7f)) {
                printf("\\%03o", (unsigned char)theChar);
            } else {
                printf("%c", theChar);
            }
        break;
   }
}

double min(double a, double b )
{
    if ( a < b ) return a;
    return b;
}

int read_file_demo1() 
{
	// __FILE__ appears to be the filename of this file
	// putting two string immediately next to each other concatenates them in c
	// "./"__FILE__
	// or "alskjdf""alksjdflka" => "alskjdfalksjdflka"

    char *file_data = NULL; 
	int length = -1;
	char *filename = __FILE__; 

	printf("reading %s\n", filename);
    read_file( filename, &file_data, &length );

	printf("\n{");
	for (int i=0; i<min(length, 10000); ++i) print_char(file_data[i]); // printf("%c",file_data[i]); 
	printf("}...\n");

	free(file_data);
    return 0;
}

void read_file_demo()
{
    char *file_data; 
	int length = -1;
    read_file( __FILE__, &file_data, &length );

    char str[1000];
    snprintf(str, 1000, "%s", file_data);
    printf("%s\n", str);
}


int main()
{
    read_file_demo();
    // read_file_demo1();
    // prints_itself();
}