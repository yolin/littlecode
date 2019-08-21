import sys
import string

alphanum = string.ascii_uppercase + string.digits

combs = [sys.argv[1]+val1+val2 for val1 in alphanum for val2 in alphanum]

print("\n".join(combs))
