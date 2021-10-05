# Find files in the current directory that have all the supplied keywords in them
# 
# For example
# python find.py something
# python find.py misc ass1 .c misc
# 
# Searches the entire file path

import os
import sys

def find(a,b):
	result = a.lower().find(b.lower())
	if result < 0:
		return False
	else:
		return True


def find_files( top_dir, query ):


    for root, dirs, files in os.walk(top_dir, topdown=False):
        # print(root,dirs,files)

        files = dirs + files  # join the two lists together

        for file in files:
            full_path = os.path.join(root, file)
            was_found = True	
            for query_word in query:
                if not find(full_path, query_word):
                    was_found = False
            if was_found:
                print(full_path)


import pathlib 

if __name__ == "__main__":

    print("usage: python find_files.py dir query")
    print("args:", sys.argv)

    query = [""]
    top_dir = os.getcwd()

    if ( len(sys.argv) >= 2 ):
        script_name = sys.argv[0]
        top_dir = sys.argv[1]
        query = sys.argv[2:]
        if ( top_dir == "." ): top_dir = os.getcwd()
        if ( top_dir == "~" ): top_dir = pathlib.Path.home()
    

    print(script_name, top_dir, query, "\n")
    find_files( top_dir, query )

