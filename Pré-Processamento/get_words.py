#!/usr/local/bin/python
# coding: utf-8
import os
import re
import unicodedata as ud

def get_articles(file,n): #pega uma amostra de n domumentos em "file"
    
    out=open('sample.txt',"w+")
    with open(file,"r") as f:
        lines=f.readlines()
        counts=0
        
        for line in lines:
            if counts>=n:
                break
            out.write(line)
            if re.match("ENDOFARTICLE",line):
                print(line)
                counts +=1
    out.close()
def remove_accents(string):
    #if type(string) is not unicode:
        #string = unicode(string, encoding='utf-8')
    
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


def get_words(file):
    with open(file, 'r',encoding="latin-1") as sample: 
        result = open('result_tests.txt', 'w+')
        titles = open('titles.txt','w+')

        for line in sample:
            line=remove_accents(line)
            line = (" ").join(re.findall('\w+',line))
            aux=[]
            if re.match("doc",line) and len(line)>3:#linha que contem as informações
                title=re.search("title\s?(\w+\s+)+nonfiltered",line).group()[6:-11].upper()
                index=re.search("dbindex\s?\d+\s?",line).group()[8:]
                x=title.lower().split()
                for i in x:
                    if i is not in
                titles.write(index+","+title+"\n")
            elif (re.match("doc",line) and len(line)<=3) or re.match("ENDOFARTICLE",line):
                #result.write("\n")
                pass
            else:
                pass
        result.close()
        titles.close()
def main():
    #get_articles("raw_0_10000",5)
    get_words('sample.txt')
    
if __name__=="__main__":
    #get_articles("raw_0_10000",5)
    main()