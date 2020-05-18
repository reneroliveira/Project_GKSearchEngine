#!/usr/local/bin/python
# coding: utf-8
import os
import re
import unicodedata

def get_articles(file,n): #pega uma amostra de n domumentos em "file"
    
    out=open('sample.txt',"w+")
    with open(file,"r",encoding="utf-8") as f:
        counts=0
        for line in f:
            if counts>=n:
                break
            out.write(line)
            if re.match("ENDOFARTICLE",line):
                print(line)
                counts +=1
    out.close()

def strip_accents(text):

    try:
        text = unicode(text, 'utf-8')
    except NameError: 
        pass

    text = unicodedata.normalize('NFKD', text).encode('ascii', 'ignore').decode()

    return str(text)
def remove_accents(string):
    try:
        text = unicode(text, 'utf-8')
    except NameError: 
        pass
    
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
    with open(file, 'r',encoding="utf-8",errors='ignore') as sample: 
        titles = open(titles_file,'w')
        for line in sample:
            line=strip_accents(line)
            line = (" ").join(re.findall('\w+',line))
            if re.match("doc",line) and len(line)>3 and re.search("title\s?(\w+\s+)+nonfiltered",line):#linha que contem as informações
                title=re.search("title\s?(\w+\s+)+nonfiltered",line).group()[6:-11].upper()
                index=re.search("dbindex\s?\d+\s?",line).group()[8:]
                titles.write(index+","+title+"\n")
        titles.close()
def get_words(file,frequences):
    with open(file, 'r',encoding="utf-8",errors='ignore') as sample: 
        frequence={}
        for line in sample:
            line=strip_accents(line)
            line = (" ").join(re.findall('\w+',line))
            if re.match("doc",line) and len(line)>3 and re.search("title\s?(\w+\s+)+nonfiltered",line):#linha que contem as informações
                title=re.search("title\s?(\w+\s+)+nonfiltered",line).group()[6:-12]
                index=re.search("dbindex\s?\d+\s?",line).group()[8:]
                for word in title.lower().split():
                    if word not in frequences.keys():
                        frequences[word]={}#""
                        frequence[word]=1
                    else:
                        if word in frequence: 
                            frequence[word]=frequence[word]+1
                        else:
                            frequence[word]=1
            elif (re.match("doc",line) and len(line)<=3) or re.match("ENDOFARTICLE",line):##fim do artigo
                for word in frequence.keys():
                    frequences[word][index]=frequence[word]#frequences[word]=frequences[word]+str(index)+","+str(frequence[word])+" "
                del frequence
                frequence={}
            else:
                for word in line.lower().split():
                    if word not in frequences.keys():
                        frequences[word]={}#""
                        frequence[word]=1
                    else: 
                        if word in frequence: 
                            frequence[word]=frequence[word]+1
                        else:
                            frequence[word]=1
def save_words(frequences):
    max_words=400000
    cur=os.getcwd()
    if not os.path.exists('words'):
        os.mkdir('words')
    w_dir=cur+"/words"
    
    j=0
    tot=len(frequences.keys())
    print(str(tot)+" words")
    #print(frequences[0])
    if j%max_words==0: result_file = w_dir+"/words_"+str(j)
    result = open(result_file,'w+',encoding='utf-8')
    for word in frequences.keys():
            j+=1
            if j%1000==0 or j==tot:
                print("Palavra "+str(j)+"/"+str(tot))
            result.write("$"+word+"\n")
            if j%max_words==0: 
                result.close
                result_file = w_dir+"/words_"+str(j)+".txt"
                result=open(result_file,'w+',encoding='utf-8')
            for index in frequences[word].keys():
                result.write(str(index)+","+str(frequences[word][index])+" ")
            result.write("\n")
    result.close()
    del frequences


def extract_titles():
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
        os.system('clear')
        print("Progresso -- "+str(round(i*100/len(f),2))+" %" )
        get_titles(cur+"/titles/titles"+file[11:]+".txt",raw_dir+"/"+file)
        i+=1
def extract_words():
    frequences={}
    cur=os.getcwd()
    raw_dir=cur+"/raw.en/"
    f=[]
    for (dirpath, dirnames, filenames) in os.walk(raw_dir):
        f.extend(filenames)
        break
    f=sorted(f)
    i=0
    frequences={}
    for file in f:
        i+=1
        print("{:.2f} % dos documentos lidos".format(i/len(f)))
        get_words(raw_dir+file,frequences)
    save_words(frequences)
    
if __name__=="__main__":
    #get_articles(os.getcwd()+"/raw.en/englishText_0_10000",100)
    #extrai 100 documentos e salva em sample.txt
    #frequences={}
    #get_words('sample.txt',frequences)
    #extract_titles()
    extract_words()
    
