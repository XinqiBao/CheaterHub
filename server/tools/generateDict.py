#! /usr/bin/python3
import os
import subprocess

workPath = "../wordscapes/"
dictPath = workPath + "dict/"

if __name__ == "__main__":

    file_names = subprocess.Popen("ls " + dictPath, shell=True, stdout=subprocess.PIPE).communicate()[0].decode().split()

    m_dict = set()
    file_out = open(workPath + "myDictionary", "w")

    for file_name in file_names:
        file = open(dictPath + file_name, "r")

        for word in file.readlines():
            word = word.strip().lower()
            if word.isalpha():
                m_dict.add(word)

    file_out.write('\n'.join(m_dict))
