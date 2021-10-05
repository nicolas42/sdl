# This script can't be called wget.py otherwise you get a circular dependency error
#
# usage: 
# python wget2.py url
#

import wget
import sys
import ssl

ssl._create_default_https_context = ssl._create_unverified_context
# ^ gets rid of certificate errors

url = sys.argv[1]
wget.download(url)
