#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
typedef uint8_t     u8;
typedef int8_t      s8;
typedef uint16_t    u16;
typedef int16_t     s16;
typedef uint32_t    u32;
typedef int32_t     s32;
typedef uint64_t    u64;
typedef int64_t     s64;
typedef float       f32;
typedef double      f64;
#include <signal.h>



struct list {
  void** data;
  int length;
  int allocated;
};

struct list make_list()
{
    struct list l;
    l.length = 0;
    l.allocated = 10;
    l.data = (void**)malloc( l.allocated * sizeof(void*) );
    return l;
}

struct list append_list(struct list l, void* str)
{
    l.data[l.length] = str;
    l.length += 1;
    if ( l.length == l.allocated ) {
      l.allocated *= 2;
      l.data = (void**)realloc( l.data, l.allocated * sizeof(void*) );
    }
    return l;
}


void free_list(struct list l)
{
    free(l.data);
}

struct list allocate_list(int n)
{
    struct list l;
    l.length = 0;
    l.allocated = n;
    l.data = (void**)malloc( l.allocated * sizeof(void*) );
    return l;
}

struct list split_string(char *str, char delim)
{
    // convert spaces to null bytes
    size_t string_length = strlen(str);
    int i=0;
    for (i=0;i<string_length;i++) if (str[i]==delim) str[i] = '\0';

    // note down stuff after null bytes
    struct list l = make_list();
    if ( str[0] != '\0' ) l = append_list(l, str);
    for (i=1; i<string_length; i++ ) {
        if ( str[i-1] == '\0' && str[i] != '\0' ) l = append_list(l, str+i);
    }
    return l;
}

char* read_file(char *filename)
{
    char *str;
    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END); // seek to end of file
    int size = ftell(f);   // get current file pointer
    fseek(f, 0, SEEK_SET); // seek back to beginning of file
    str = (char*)malloc(size * sizeof(char));
    fread(str, size, 1, f);
    fclose(f);

    return str;
}


int file_exists(const char * filename){
    /* try to open file to read */
    FILE *file;
    file = fopen(filename, "r");
    if (file){
        fclose(file);
        return 1;
    }
    return 0;
}

double get_time_elapsed(void)
{
	return clock()/(double)CLOCKS_PER_SEC;
}

int is_optimus_prime( u64 candidate, struct list primes )
{
    for (u64 i=0; i<primes.length; i++){
        if ( candidate % (u64)primes.data[i] == 0) return 0;
    }
    return 1;
}

void signal_handler(int signal)
{
  if (signal == SIGINT){
    // fclose(file);
    printf("\nreceived SIGINT\n");
    exit(0);
  }
}


// sieve some primes and write them to the file
// read primes from file if it already exists
struct list make_prime_numbers(char *filename)
{

    if ( signal(SIGINT, signal_handler) == SIG_ERR ) { printf("\ncan't catch SIGINT\n"); }



    // char *filename = "primes.dat";
    struct list primes = make_list();
    FILE *file;

    if ( file_exists(filename)) {

        char *str = read_file(filename);
        
        struct list l = split_string(str, ' ');

        for (int i=0;i<l.length;i++) {
            u64 tmp;
            sscanf((char*)l.data[i], "%lu", &tmp);
            primes = append_list( primes, (void*)tmp );
        }

        for (int i=0;i<l.length;i++) { printf("%lu ", (u64)(primes.data[i])); }

    } else {

        // we only check odd numbers
        primes = append_list( primes, (void*)2 );
        primes = append_list( primes, (void*)3 );
        file = fopen(filename, "a");
        fprintf(file, "%lu %lu ", (u64)(2), (u64)(3));
        fclose(file);
    }



    u64 num_to_check = 1000000;
    u64 upper_limit = (u64)primes.data[primes.length-1] + num_to_check;
    double t1 = get_time_elapsed();

    file = fopen(filename, "a");

	for ( u64 o = (u64)(primes.data[primes.length-1]); o < upper_limit; o += 2 ) {
		
		if ( is_optimus_prime(o, primes) ) {
    
            primes = append_list( primes, (void*)o );
			// printf("%lu ", o);
            fprintf(file, "%lu ", o);

		}

        if ( get_time_elapsed()-t1 >= 1 ){
            
			t1 = get_time_elapsed();
		    printf("...%lu", (u64)(primes.data[primes.length-1]));
            fflush(stdout);
            
        }

	}

    
    return primes;
}


struct list simple_make_prime_numbers()
{
    struct list primes = make_list();
    primes = append_list( primes, (void*)2 );
    primes = append_list( primes, (void*)3 );

    u64 upper_limit = 1000000;
    double t1 = get_time_elapsed();
	for ( u64 p = (u64)(primes.data[primes.length-1]); p < upper_limit; p += 2 ) {
		
		if ( is_optimus_prime(p, primes) ) {
    
            primes = append_list( primes, (void*)p );
			// printf("%lu ", p);
		}

        if (get_time_elapsed()-t1 >= 1){
			t1 = get_time_elapsed();
		    printf("...%lu", (u64)(primes.data[primes.length-1]));
            fflush(stdout);
            
        }

	}
    return primes;
}


int main()
{
    simple_make_prime_numbers();
    // make_prime_numbers("primes.dat");
}