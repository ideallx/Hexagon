# -*- coding: utf-8 -*- 
import os, os.path

def checkfiles(directory):
    files = os.listdir(directory)
    for f in files:
        if f[:1] == '.':
            continue
        fname = directory + os.sep + f
        if os.path.isdir(fname):
            checkfiles(fname)
        else:
            if f[-2:] == '.h' or f[-4:] == '.cpp':
                if(f[:3] != 'ui_') and (f[:4] != "qrc_"):
                    os.system("D:\lix\cpplint\cpplint.py " + '"' + fname + '"')


root = "C:\Documents and Settings\lix\My Documents\GitHub\Hexagon"
checkfiles(root)
os.system("pause")
