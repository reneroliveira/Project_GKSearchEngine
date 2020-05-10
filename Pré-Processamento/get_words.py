#!/usr/local/bin/python
# coding: utf-8
import os
import re
import unicodedata as ud

def get_articles(file,n): #pega uma amostra de n domumentos em "file"
    counts=0
    end="ENDOFARTICLE"
    out=open('sample.txt',"w+")
    with open(file,"r") as f:
        lines=f.readlines()
        while counts<=n:
            for line in lines:
                out.write(line)
                if line[0:12]==end:
                    counts +=1
    out.close()
def remove_accents(string):
    if type(string) is not unicode:
        string = unicode(string, encoding='utf-8')
    
    string = re.sub(u"[ÁÀÂÃÄÅàáâãäå]", 'a', string)#ª
    string = re.sub(u"[ÈÉÊËẼẽèéêë]", 'e', string)
    string = re.sub(u"[ÍÌÏĨÎĩîìíîï]", 'i', string)
    string = re.sub(u"[ÒÓÔÖÕõòóôõö]", 'o', string)
    string = re.sub(u"[ŨÙÚÛÜũùúûü]", 'u', string)
    string = re.sub(u"[ÝỲỸŸŶỳŷỹýÿ]", 'y', string)
    string = re.sub(u"[Ññ]", 'n', string)
    string = re.sub(u"[¢çĉćĉCĈĆĈ]", 'c', string)
    string = re.sub(u"[Ž]", 'z', string)
    return string #.encode('ascii','ignore')

def main():
    #get_articles("raw_0_10000",5)

    sample = open('sample.txt', 'r') #arquivo original
    result = open('result_tests.txt', 'w') #abrir o arquivo em modo leitura
   

    for line in sample:
        if line[0:4]=="<doc":
            #print(re.search('title={1}\"{2}',line))
        if line[0:4]!="<doc" and line[0:6]!="</doc>" and line[0:12]!="ENDOFARTICLE":
            words = re.findall('[a-zA-Z0-9]+',line)
            line = (" ").join(words)
            
    result.close()
    sample.close()
if __name__=="__main__":
    get_articles("raw_0_10000",5)
    main()