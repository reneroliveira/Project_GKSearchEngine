# -*- coding: utf-8 -*-
import time
import os
import re
import unicodedata

def merge(a,b,key):
    result = []
    while (a and b):
        if a[0][key]>b[0][key]:
            result.append(a[0])
            a.pop(0)
        else:
            result.append(b[0])
            b.pop(0)
    for i in a:
        result.append(i)
    for j in b:
        result.append(j)
    return result

def merge_sort(a,key):
    if len(a)<=1:
        return a 
    else:
        left = a[0:int(len(a)/2)]
        right = a[int(len(a)/2):len(a)+1]
    return merge(merge_sort(left,key),merge_sort(right,key),key)
def get_articles(file,n): #pega uma amostra de n domumentos tipo raw em "file"
    
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
            if re.match("doc id",line):#linha que contem as informações
                if re.search("title\s?(\w+\s+)+nonfiltered",line):
                    title=re.search("title\s?(\w+\s+)+nonfiltered",line).group()[6:-11].upper()
                else:
                    title=" "
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
    max_words=50000
    cur=os.getcwd()
    if not os.path.exists('words'):
        os.mkdir('words')
    w_dir=cur+"/words"
    
    j=0
    tot=len(frequences.keys())
    print(str(tot)+" words")
<<<<<<< HEAD
    if j%max_words==0: result_file = w_dir+"/words_"+str(j)
=======
    #print(frequences[0])
    if j%max_words==0: result_file = w_dir+"/words_"+str(j)+".txt"
>>>>>>> ed23568e387523fca3d95ac85510c24d95cacfbf
    result = open(result_file,'w+',encoding='utf-8')
    for word in frequences.keys():
            j+=1
            if j%1000==0 or j==tot:
                print("Palavra "+str(j)+"/"+str(tot))
            result.write("$"+word+"\n")
            for index in frequences[word].keys():
                result.write(str(index)+","+str(frequences[word][index])+" ")
            if j%max_words==0: 
                result.close
                result_file = w_dir+"/words_"+str(j)+".txt"
                result=open(result_file,'w+',encoding='utf-8')
            
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
        print("{:.2f} % dos documentos lidos".format(i*100/len(f)))
        get_words(raw_dir+file,frequences)
    save_words(frequences)

def sort_docs(dir,file):
    file1=open(file,'r')
    name=re.search('words\_(\d+)',file).group()
    file2=open(dir+"sorted_"+name+".txt",'w+')
    k=0
    t0=time.time()
    for line in file1:
        k+=1
        if k%10000==0:
            print("--- Processing Lines {:.2f} %".format(k*100/100000))
        
        if re.match("\$",line):
            file2.write(line)
        else:
            docs=[]
            it=iter(line.split())
            docs=[tuple([int(i) for i in x.split(',')]) for x in it]
            docs=merge_sort(docs,1)
            sorted_line=""
            for d in docs:
                sorted_line=sorted_line+str(d[0])+" "
            file2.write(sorted_line+"\n")
        t=time.time()-t0
        
    file1.close()
    file2.close()
    print(" ----- Tempo de linha = {:.2f} minutos".format(t/60))

            
    
def sort_articles():
    cur=os.getcwd()
    words_dir=cur+"/words/"
    if not os.path.exists('sorted_words'):
        os.mkdir('sorted_words')
    sort_dir=cur+"/sorted_words/"
    
    f=[]
    for (dirpath, dirnames, filenames) in os.walk(words_dir):
        f.extend(filenames)
        break
    print(f)
    i=0
    t0=time.time()
    for file in f:
        i+=1
        print("{:.2f} % concluído".format(i*100/len(f)))
        sort_docs(sort_dir,words_dir+file)
    t=time.time()-t0
    print("Extração Concluída em {:.2f} minutos".format(t/60))
def split_words():
    cur=os.getcwd()
    words_dir=cur+"/words/"
    if not os.path.exists('words3'):
        os.mkdir('words3')
    new_dir=cur+"/words3/"
    j=0
    f=[]
    for (dirpath, dirnames, filenames) in os.walk(words_dir):
        f.extend(filenames)
        break
    res=open(new_dir+"words"+"_0.txt",'w+')
    for file in f:
        with open(words_dir+file,'r') as w:
            for line in w:
                res.write(line)
                if j%100000==99999 and j!=0:
                    res.close()
                    res=open(new_dir+"words_"+str(int((j+1)/2))+".txt",'w+')
                j=j+1
def verify(path):
    res=[]
    f=[]
    for (dirpath, dirnames, filenames) in os.walk(path):
        f.extend(filenames)
        break
    for file in f:
        j=0
        with open(path+file,"r") as w:
            for line in w:
                j+=1
                if j%2==1 and not (re.match("\$",line)):
                    res.append([file,j,line[0:10]])
    return res
if __name__=="__main__":
    
    #Linha abaixo extrai 100 documentos e salva em sample.txt
    #get_articles(os.getcwd()+"/raw.en/englishText_0_10000",100)
    

    #Descomente abaixo se quiser extrair as palavras únicas por conta própria,
    #recomendável ter 16GB de RAM, caso não tenha, temos os resultados já procesados disponíveis/*
    #extract_words()
    #sort_articles()

    #Comando que extrai os títulos:
    #extract_titles()
    
    

