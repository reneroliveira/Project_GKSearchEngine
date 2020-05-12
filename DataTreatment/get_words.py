#!/usr/local/bin/python
# coding: latin-1
import os
import re
import unicodedata

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
accent_dict={
    'à':'a','á':'a',
    'â':'a',
    'ã':'a',
    'ä':'a',
    'å':'a'
    }

def remove_accents(string):
    #if not(type(string)=="str"):
       #string.encode('utf-8')
    
    string = re.sub(u"[àáâãäå]", 'a', string)#ª
    string = re.sub(u"[ÁÀÂÃÄÅ]","A",string)
    string = re.sub(u"[ẽèéêë]", 'e', string)
    string = re.sub(u"[ÈÉÊËẼ]","E", string)
    string = re.sub(u"[ĩîìíîï]", 'i', string)
    string = re.sub(u"[ÍÌÏĨÎ]","I",string)
    string = re.sub(u"[õòóôõö]", 'o', string)
    string = re.sub(u"[ÒÓÔÖÕ]","O",string)
    string = re.sub(u"[ũùúûü]", 'u', string)
    string = re.sub(u"[ŨÙÚÛÜ]","U",string)
    string = re.sub(u"[ỳŷỹýÿ]", 'y', string)
    string = re.sub(u"[ÝỲỸŸŶ]","Y",string)
    string = re.sub(u"[ñ]", 'n', string)
    string = re.sub(u"[Ñ]", 'N', string)
    string = re.sub(u"[¢çĉćĉ]", 'c', string)
    string = re.sub(u"[CĈĆĈÇ]","C",string)
    string = re.sub(u"[Ž]", 'z', string)
    return string #.encode('ascii','ignore')

def get_titles(titles_file,file):
    with open(file, 'r',encoding="ISO-8859-1") as sample: 
        titles = open(titles_file,'w')
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
    """
    cur=os.getcwd()
    raw_dir=cur+"/raw"
    f=[]
    for (dirpath, dirnames, filenames) in os.walk(raw_dir):
        f.extend(filenames)
        break
    f=sorted(f)
    i=0
    for file in f:
        print(i/len(f))
        i+=1
        get_titles('titles.txt',raw_dir+"/"+file)"""
    print(remove_accents2("ráner"))
if __name__=="__main__":
    main()