import random
import requests
import os


def read_thru(url):

    # read url file and cache it for future usage.

    # url2filename
    filename = url.split('//')[-1].replace('/','-')

    if os.path.exists(filename):
        f = open(filename,'r')
        data = f.read()
        f.close()
        return data

    print('\nreading', url, '...\n')

    # set encoding to utf8
    response = requests.get(url)
    response.encoding = 'utf-8'
    data = response.text
    
    f = open(filename,'w')
    f.write(data)
    f.close()

    return data


# moby dick
url = 'https://www.gutenberg.org/files/2701/2701-0.txt'
data = read_thru(url)


# # write to file
# f = open('moby_dick.txt','w',encoding="utf-8")
# f.write(r.text)
# f.close()

# # read from file
# f = open('moby_dick.txt', encoding="utf-8")
# data = f.read()
# f.close()


output = []
data = data.split() # split at whitespace

position = random.randint(0, len(data)-3) # 24158 

output.append(data[position])
output.append(data[position+1])

for j in range(100):
    # print(j)
    locations_of_matches = []
    for i,_ in enumerate(data):
        if data[i].lower() == output[-2].lower() and data[i+1].lower() == output[-1].lower():
            # print(i)
            locations_of_matches.append(i)

    # print(locations_of_matches)        
    # for l in locations_of_matches:
    #     print(data[l], data[l+1], data[l+2])
    random_match_location = random.choice(locations_of_matches)
    new_word = data[random_match_location+2]
    output.append(new_word)
    print(new_word, end=' ', flush=True)


print()

# joined_result = ' '.join(output)
# print(joined_result)

