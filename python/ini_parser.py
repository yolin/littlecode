#!/usr/bin/env python
import sys
import ConfigParser

config = ConfigParser.ConfigParser()

if len(sys.argv) != 1:
    try:
        config.read(sys.argv[1])
        if len(sys.argv) == 4:
            single_value = config.get(sys.argv[2], sys.argv[3])
            print single_value
        elif len(sys.argv) == 3:
            single_section = config.items(sys.argv[2])
            for item in single_section:
                print item[0]
        elif len(sys.argv) == 2:
            for section in config.sections():
                print section
        else:
            print "./ini_parser.py [ini_file] [section] [variable]"
    except:
        sys.exit(0)
else:
    print "./ini_parser.py [ini_file] [section] [variable]"
