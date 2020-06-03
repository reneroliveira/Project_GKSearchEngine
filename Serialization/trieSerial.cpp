#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <chrono>
#include "trie.cpp"

using namespace std;

void insert_file(Trie Drevo, const char* file){
    ifstream arquivoE;
    string linha;
    string r;
    arquivoE.open(file);
    Node *p;
    if(arquivoE.is_open())
    {
        while(getline(arquivoE,linha))
        {
            if(linha[0]=='$')
            {
                p = Drevo.insert(linha.substr(1));
            }
            else
            {
                stringstream ids;
                ids<<linha;
                string cur_id;
                while(ids>>cur_id)
                {
                    p->put_doc(stoi(cur_id));
                }

            }
        }
    }
    else
    {
        cout << "Error in file "<< file << endl;
    }
    arquivoE.close();
}

int main()
{
    Trie GKSE;
    auto Start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 1; i++)
    {
        cout << "\r-> Inserting File " << i+1 << " of 64.";
        string prefix = "./sorted_words/sorted_words_";
        string number = to_string(i*50000);
        string sufix = ".txt";
        string a = prefix + number + sufix;
        const char *arq = a.c_str();
        insert_file(GKSE,arq);
    }
    auto End = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> Tempo = End - Start;
    cout << endl << "-> Build finished in " << Tempo.count()/1000 << " seconds!\n" << endl;
    
    GKSE.Serialize();
}

