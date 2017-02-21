#!/usr/bin/python3
import sys

######################
#  print array
######################
forarray = ["ham","spam","eggs","nuts"]
print("----------")
for i in forarray:
    print(i)

print("----------")

for i in range(0, 10, 3) :
    print(i)
print("----------")

for i in range(len(forarray)):
    print(forarray[i])

'''
ranges=range(len(forarray))
print("aaaaa",ranges,"bbbbb",sep='')
cccc="aaaaa"+"bbbbb"
print("----------")
print(cccc)
print("----------")
'''


######################
#  print sep
######################
sep=123
inputstr=input("test input:")
print("nospace>>>>"+inputstr,"<<<<space-here!!")
print("no sep>>>>"+inputstr,"<<<<sep-here")
print("no sep>>>>"+inputstr,"<<<<sep-here>>>>","sep", sep="||||")

print("\n\n\n\n\n\n\\\\\\\\")
print(r"\\\\\\")
print(u"unicode")

print("----------")

######################
#  for file
######################
filename=input("input filename:")

for line in open(filename, 'r', encoding='UTF-8'):
    print(line, end='')

print("----------")

######################
#  if 
######################
a="aaa"
b="aaa"
strHello = "the length of (%s) is %d" %("test",len('Hello World'))
if True:
    print(strHello)
elif a is b:
    print("test")
else:
    print(333)
print("----------")

######################
#   while
######################
cnt=1
while cnt < 20:
    #print(bin(cnt))
    print("cnt=%d" % cnt)
    cnt+=1

print("----------")
