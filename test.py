# -*- coding: utf-8 -*-
"""
-------------------------------------------------
   File Name：     book_UI
   Description :
   Author :       #TUYI#
   date：          6/9/2019
-------------------------------------------------
"""
__author__ = '#TUYI#'

import re
import sys

filepath = sys.argv[1]

outpath = filepath
# print(filepath)
f = open(filepath,'r')

text = "".join(f.read())
# text = text.replace("booktitle","nnnnn")

l = re.findall(r'\btitle\b(.*?)=(.*?)[{|"]((.|\n)*?)[}|"],',text)

print("length of l: "+str(len(l)))

i=1
for ll in l:
    print(i)
    print(ll[2])
    msg = 'title = {{%s}},' %ll[2]
    print(msg)

    i= i+1

    # l1 = re.findall(r'\btitle\b(.*?)=(.*?)[{|"]'+ll[2]+r'[}|"],',text)
    # print("length of l1: "+str(len(l1)))

    text = re.sub(r'\btitle\b(.*?)=(.*?)[{|"]'+ll[2]+r'[}|"],',msg,text)

# print(text)
f.close()                
open(outpath, 'w').write(text)

