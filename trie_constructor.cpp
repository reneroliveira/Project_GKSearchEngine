#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <chrono>
#include "trie.cpp"
using namespace std;


void insert_file(Trie T,const char* file){
    ifstream arquivoE;
    string linha;
    string r;
    arquivoE.open(file);
    Node *p;
    if(arquivoE.is_open()){
    while(getline(arquivoE,linha)){
        //aqui podemos fazer operaões linha a linha
       if(linha[0]=='$'){
        p = T.insert(linha.substr(1));
       }else{
           stringstream ids;
           ids<<linha;
           string cur_id;
           while(ids>>cur_id){
               p->put_doc(stoi(cur_id));
           }

       }
        

    }
  }else{
  cout << "Não foi possível abrir o arquivo "<< file << endl;

  }
    arquivoE.close();

}
int main(){
    Trie GKSE;
    auto start = chrono::high_resolution_clock::now();
    for(int i=0;i<=63;i++){
        cout<<"Inserting File "<<i<<endl;
        string prefix = "./sorted_words/sorted_words_";
        string number = to_string(i*50000);
        string sufix = ".txt";
        string a = prefix + number + sufix;
        const char *arq =a.c_str();
        insert_file(GKSE,arq);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> t_build = end - start;
    cout << "Construção concluída em "<<t_build.count()/1000<<" segundos!"<<endl;

    
    
while(1){
    cout<<"-> Digite sua palavra: "<<endl;
    cout<<"-> ";
    string query;
    cin >>query;
    if(query=="0"){
        return 0;
    }
    auto t1 = chrono::high_resolution_clock::now();
    vector<int> res = GKSE.find(query);
    auto t2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> t_search = t2 - t1;

    cout<<"-> "<<res.size()<< " resultados encontrados em "<< t_search.count()/1000<< " segundos!"; 
    
    if(res.empty()){
        cout<<"-> Palavra Não Encontrada :(";
    }else{
    cout<<endl<<"-> Resultados: ";
    if(res.size()<=20){
        print_vector(res);
    }else{
        vector<int> res20=vector<int>(res.begin(),res.begin()+20);
        print_vector(res20);
    }
    cout<<endl;
    }
    cout<<endl<<"PARA SAIR DIGITE O NÚMERO 0"<<endl;
}
}