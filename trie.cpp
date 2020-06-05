#include <string.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

struct Node
{

    //int aKey; Deixei sem a chave para tentar reduzir memória ocupada.
    Node *aChild[36];
    vector<int> docs;
    /*
    Para checar se um nó é final de palavra,
    basta ver se existe algo nesse vetor usando docs.empty();
    por isso removi o booleano end;
    */

    Node(){//
        this->docs ={};
        for(int i=0;i<36;i++){
            this->aChild[i]=nullptr;
        }
    }

    void put_doc(int doc_id)
    {
        /*Função recebe um inteiro e coloca no final da vetor,
         de documentos do Nó cujo ponteiro p representa;*/
        this->docs.push_back(doc_id);
    }

};
vector<int> convert(string aWord)
    {
        vector<int> indexes;

        // A ideia inicia é transformar a palavra numa sequência de caracteres, para depois transformá-los em índices
        // para serem identificados nos nós.
        //o vetor acima conterá os índices

        int aKey;
        //cout << "-> Converting word: " << aWord <<endl;


        // Esta parte mosta as chaves dos caracteres. Isso serve para anexá-los nos nós-filhos.
        // (nada mais que testes maneiros)
        for (char& aLetter:aWord)
        {//Função só converte corretamente, letras maiúsculas, minúsculas e números, vamos ver como tratar espaço e acentos
            if((int)aLetter < 123 && (int)aLetter>96)
            {//Letras minúsculas
                aKey = (int)aLetter - 87;
                indexes.push_back(aKey);
                //push_back é similar ao list.append do Python
            }
            else if ((int)aLetter < 58 && (int)aLetter>47)
            {//números de 0 a 9
                aKey = (int)aLetter - 48;
                indexes.push_back(aKey);
            }

            else if((int)aLetter < 91 && (int)aLetter>64)
            {//Letras maiúsculas
                aKey = (int)aLetter - 55;
                indexes.push_back(aKey);
            }
        }
    return indexes;
    }
class Trie
{
protected:
    Node *aRoot;
public:
    Trie()
    {
        aRoot = new Node();//  Usa-se o contrutor Node() para criar a raiz;
        cout << endl << "-> Starting trie build..." << endl;
    }

    Node* insert(string aWord)//retorna um ponteiro ao nó final
    {
        Node**p = &(aRoot);
        insert(convert(aWord),p);
        return *p;
    }

    vector<int> find(string aWord){
        cout << endl << "-> Finding: " << aWord << "..." << endl;
        return find(convert(aWord));
    }
    void suggest(string query){
        cout<<"-> Sorry. Word not found.  ;-;";
    }
 /*OBS: essas funções publicas de insert e find, pegam uma string, convertem em vetor,
 e chamam as funções privadas abaixo pra fazer o trabalho a partir desse vetor gerado*/
private:
    void insert(vector<int> indexes,Node**&p){
        for(int i:indexes){
            if((*p)->aChild[i]==nullptr)
            {//Caso o filho i não exista, cria-se um novo Nó;
                (*p)->aChild[i]=new Node();
            }

            p=&((*p)->aChild[i]);
        }
    }
    vector<int> find(vector<int> word)
    {
        Node **p = &aRoot;
        for (int i:word)
        {
            if (!((*p)->aChild[i])) {return {};
            } else {
            p = &((*p)->aChild[i]);
            }
        }
        return (*p)->docs;
    }
};

string print_title(int x)
{
    string title = "";
    int number = x / 10000;
    string name = "aNames/aTitles_" + to_string(number*10000) + "_" + to_string((number+1)*10000) + ".txt";
    string line;
    ifstream file (name);
    number = number*10000;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (x == number)
            {
                stringstream split;
                split<<line;
                string words;
                split>>words;//este passo tira o ID da sstream
                while(split>>words){
                    //este loop salva o título
                    title= title+words+" ";
                }
                /*char str[line.length()+1];
                strcpy(str, line.c_str());
                char *token = strtok(str, ",");
                while (token != NULL)
                {
                    token = strtok(NULL, ",");
                    if (token == NULL) break;
                    else title = title + token + ",";
                }
                title.pop_back();*/
            }
            number += 1;
        }
    }
    file.close();
    return title;
}
void print_vector(vector<int> v,int couting)
{   
    int i = couting+1;
    for(int x:v)
    {
        cout << " > ["<< i <<"] " << print_title(x) << endl;
        i+=1;
    }
}
std::string aDocs (int aIndex) // Função para procurar o texto referente ao dbindex aIndex.
{
    int aNumber = aIndex/10000; aNumber *= 10000;
    std::ifstream aFile ("aTexts/aDocs_" + std::to_string(aNumber) + "_" + std::to_string(aNumber+10000));
    std::string aLine;
    std::string aText ("");
    if (aFile.is_open())
    {
        bool aIsText (false); // Este aIsText indica se é o texto que procuramos.
        while(getline(aFile, aLine)) // E sim. Ainda não achei um jeito menos doloroso de procurar pelo texto.
        {
            std::string aNotherLine (aLine);
            aLine.erase(aLine.begin()+21, aLine.end()); // Isso deixa aLine com os primeiros caracteres. E se for igual a
            if (aLine == "Marked: low fidelity ")       // "Marked: low fidelity ", o programa reconhece um novo artigo.
            {
                if (aIsText) break;
                aNotherLine.erase(aNotherLine.begin(), aNotherLine.begin()+21);
                int aDataBaseIndex = std::stoi(aNotherLine);
                if (aDataBaseIndex == aIndex)
                {
                    aIsText = true;
                    continue;
                }
                else continue;
                break;
            }
            else if (aIsText) aText += aNotherLine + "\n";
        }
        aFile.close();
    }
    else return " > The text couldn't be openned.";
    return aText;
}


