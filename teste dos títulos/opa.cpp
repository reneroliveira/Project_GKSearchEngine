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
    if(arquivoE.is_open())
    {
        while(getline(arquivoE,linha))
        {
            //Aaqui podemos fazer opera�es linha a linha.
            if(linha[0]=='$')
            {
                p = T.insert(linha.substr(1));
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
        cout << "N�o foi poss�vel abrir o arquivo "<< file << endl;
    }
    arquivoE.close();
}

int main(){
    Trie GKSE;
    auto start = chrono::high_resolution_clock::now();
    for(int i=0;i<=5;i++)
    {
        cout << "\r-> Inserting File " << i+1 << " of 64."; // Esse "\r" � um s�mbolo
        string prefix = "./sorted_words/sorted_words_";     // parecido com o "\n". Mas
        string number = to_string(i*50000);                 // ao inv�s dele criar uma
        string sufix = ".txt";                              // linha, ele reseta a
        string a = prefix + number + sufix;                 // linha, meio que
        const char *arq = a.c_str();                        // reescrevendo ela.
        insert_file(GKSE,arq);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> t_build = end - start;
    cout << "\n-> Build finished in " << t_build.count()/1000 << " seconds!\n" << endl;



    while(1)
    {
        cout<<"-> Type your query: ";
        string query;
        cin >> query;
        if(query=="0")
        {
            return 0;
        }
        auto time1 = chrono::high_resolution_clock::now();
        vector<int> res = GKSE.find(query);
        auto time2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> t_search = time2 - time1;

        cout << "-> " << res.size() << " results found in " << t_search.count()/1000 << " seconds." << endl;

        if(res.empty())
        {
            cout<<"-> Sorry. Word not found.  ;-;";
        }
        else
        {
            cout << "-> Results:" << endl;
            long unsigned int counting = 0;
            vector<int> res20;

            while (1) // Hehe, de novo eim.
            {
                if (res.size() > counting + 20)
                {
                    res20=vector<int>(res.begin()+counting,res.begin()+counting+20);
                } else {
                    res20=vector<int>(res.begin()+counting,res.end());
                }
                print_vector(res20);
                cout << endl << "-> Do you want to open any result [n or result number]? ";
                string answer;
                cin >> answer;
                if (answer != "n")
                {
                    cout << " > Ooops, we can't do this yet. Maybe later." << endl;
                    // � por aqui que fazemos alguma coisa para abrir o arquivo.
                }
                if (res.size() > counting + 20) // Esse if ocorre quando mais artigos
                {                               // est�o dispon�veis.
                    cout << "-> More results [y/n]? ";
                    cin >> answer;
                    if (answer == "y") counting += 20;
                    else break;
                } else break;
            }
        }
        cout<< endl << "-> (To exit, enter the number 0)" << endl << endl;
    }
}
