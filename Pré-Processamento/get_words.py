#!/usr/local/bin/python
# coding: utf-8
import os
import re
import unicodedata as ud

def get_articles(file,n): #pega uma amostra de n domumentos em "file"
    
    out=open('sample.txt',"w+")
    with open(file,"r",encoding="ISO-8859-1") as f:
        counts=0
        for line in f:
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
def get_titles(titles,file)
    with open(file, 'r',encoding="ISO-8859-1") as sample: 
        titles = open('titles.txt','w')
        for line in sample:
            line=remove_accents(line)
            line = (" ").join(re.findall('\w+',line))
            if re.match("doc",line) and len(line)>3:#linha que contem as informações
                title=re.search("title\s?(\w+\s+)+nonfiltered",line).group()[6:-11].upper()
                index=re.search("dbindex\s?\d+\s?",line).group()[8:]
                titles.write(index+","+title+"\n")
        titles.close()
def get_words(file):
    with open(file, 'r',encoding="ISO-8859-1") as sample: 
        result = open('result_tests.txt', 'r+')
        titles = open('titles.txt','w')
        aux=set([])
        frequence={}
        for line in sample:
            line=remove_accents(line)
            line = (" ").join(re.findall('\w+',line))
            if re.match("doc",line) and len(line)>3:#linha que contem as informações
                title=re.search("title\s?(\w+\s+)+nonfiltered",line).group()[6:-11].upper()
                index=re.search("dbindex\s?\d+\s?",line).group()[8:]
                titles.write(index+","+title+"\n")
                for word in title.lower().split():
                    if word not in aux:
                        aux.update([word])
                        frequence[word]=1
                    else: 
                        frequence[word]=frequence[word]+1
                
            elif (re.match("doc",line) and len(line)<=3) or re.match("ENDOFARTICLE",line):
                
                aux.clear()
                frequence={}
            else:
                for word in line.lower():
                    if word not in aux:
                        aux.update([word])
                        frequence[word]=1
                    else: 
                        frequence[word]=frequence[word]+1
        result.close()
        titles.close()
def main():
    #get_articles("raw_0_10000",100)
    #get_words('sample.txt')
    
if __name__=="__main__":
    main()