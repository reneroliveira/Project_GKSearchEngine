#!/usr/local/bin/python
# coding: utf-8
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

def strip_accents(text):

    try:
        text = unicode(text, 'utf-8')
    except NameError: 
        pass

    text = unicodedata.normalize('NFKD', text).encode('ascii', 'ignore').decode()

    return str(text)
def remove_accents(string):
    if not(type(string)=="str"):
       string.encode('utf-8')
    
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
    with open(file, 'r',encoding="ISO-8859-1",errors='ignore') as sample: 
        titles = open(titles_file,'w')
        for line in sample:
            line=strip_accents(line)
            line = (" ").join(re.findall('\w+',line))
            if re.match("doc",line) and len(line)>3 and re.search("title\s?(\w+\s+)+nonfiltered",line):#linha que contem as informações
                title=re.search("title\s?(\w+\s+)+nonfiltered",line).group()[6:-11].upper()
                index=re.search("dbindex\s?\d+\s?",line).group()[8:]
                titles.write(index+","+title+"\n")
        titles.close()
def get_words(file):
    with open(file, 'r',encoding="ISO-8859-1") as sample: 
        result = open('result_tests.txt', 'w+')
        titles = open('titles.txt','w')
        aux=set([])
        frequence={}
        frequences=[]
        for line in sample:
            line=strip_accents(line)
            line = (" ").join(re.findall('\w+',line))
            if re.match("doc",line) and len(line)>3:#linha que contem as informações
                title=re.search("title\s?(\w+\s+)+nonfiltered",line).group()[6:-12]
                index=re.search("dbindex\s?\d+\s?",line).group()[8:]
                titles.write(index+","+title+"\n")
                for word in title.lower().split():
                    if word not in aux:
                        aux.update([word])
                        frequence[word]=1
                    else:
                        if word in frequence: 
                            frequence[word]=frequence[word]+1
                        else:
                            frequence[word]=1
            elif (re.match("doc",line) and len(line)<=3) or re.match("ENDOFARTICLE",line):##fim do artigo
                frequences.append([index,frequence])
                frequence={}
            else:
                for word in line.lower().split():
                    if word not in aux:
                        aux.update([word])
                        frequence[word]=1
                    else: 
                        if word in frequence: 
                            frequence[word]=frequence[word]+1
                        else:
                            frequence[word]=1
        j=0
        tot=len(aux)
        print(str(tot)+" words")
        #print(frequences[0])
        for word in aux:
            j+=1
            if j%1000==0 or j==tot:
                print("Palavra "+str(j)+"/"+str(tot))
            result.write("$"+word+"\n")
            i=1
            for freq in frequences:
                if word in freq[1]:
                    i+=1
                    result.write(str(freq[0])+","+str(freq[1][word])+" ")
                if i%500==0:
                    print(str(word)+ "ultrapassou 500")
                    result.write("\n")
            result.write("\n")
        result.close()
        titles.close()
def main():
    #get_articles("raw_0_10000",100)
    #get_words('sample.txt')
    if not os.path.exists('titles'):
        os.mkdir('titles')
    cur=os.getcwd()
    raw_dir=cur+"/raw.en"
    f=[]
    for (dirpath, dirnames, filenames) in os.walk(raw_dir):
        f.extend(filenames)
        break
    f=sorted(f)
    i=0
    for file in f:
        print(i/len(f))
        get_titles(cur+"/titles/titles_"+str(i*10000)+"_"+str((i+1)*10000)+".txt",raw_dir+"/"+file)
        i+=1
if __name__=="__main__":
    main()