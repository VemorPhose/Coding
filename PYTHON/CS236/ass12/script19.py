import sys
import time
import importlib
import traceback
import copy
import math
from pyswip import Prolog

prolog = Prolog()
prolog.consult("19.pl")
prolog.consult("3.pl")

query_gen = prolog.query("remove_duplicates([a, b, a, c, d, d], List)")
for result in query_gen:
    print(result)

bool_query = list(prolog.query("is_leap_year(2000)"))
print(f'{"Yes" if bool_query else "No"}')