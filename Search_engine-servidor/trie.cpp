#include <string.h>
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace std;

struct Node
{

    int aKey;// troquei a chave de char para int, pois faremos a conversão em índices primeiro;
    Node *aChild[36];
    vector<int> docs;
    /*
    Para checar se um nó é final de palavra, 
    basta ver se existe algo nesse vetor usando docs.empty();
    por isso removi o booleano end;
    */

    Node(){//
        for(int i=0;i<36;i++){
            this->aChild[i]=nullptr;
        }
    }
    Node(int aIndex)
    {
        this->aKey = aIndex;
        this->docs = {};
        // Esta parte separa os caracteres. Os de 0 a 9 são os números, e os de 10 a 35 são as letras.
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

    ~Trie()
    {
        //cout  << "-> Build finished." << endl;
    }
    Node* insert(string aWord)//retorna um ponteiro ao nó final
    {   
        Node**p = &(aRoot);
        //cout<<endl<<"-> Inserting: "<<aWord<<endl;
        insert(convert(aWord),p);
        return *p;
    }
    
    
    vector<int> find(string aWord){
        cout<<endl<<"-> Finding: "<<aWord<<endl;
        return find(convert(aWord));
    }
 /*OBS: essas funções publicas de insert e find, pegam uma string, convertem em vetor,
 e chamam as funções privadas abaixo pra fazer o trabalho a partir desse vetor gerado*/
private:
    void insert(vector<int> indexes,Node**&p){
        for(int i:indexes){
            if((*p)->aChild[i]==nullptr)
            {//Caso o filho i não exista, cria-se um novo Nó;
                (*p)->aChild[i]=new Node(i);
            }
            
            p=&((*p)->aChild[i]);
        }
    }
    vector<int> find(vector<int> word) {
        Node **p = &aRoot;
        for(int i:word) {
            if (!((*p)->aChild[i])) {return {};
            }
            else{
            p = &((*p)->aChild[i]);
            }
        }
        return (*p)->docs;
        }

};
void print_vector(vector<int> v){
    cout<<"-> ";
    for(int x:v){
    cout<<x<<" ";}
    cout<<"\n\n";
}

// comentado temporariamente pois importaremos em outro arquivo.
/*int main()
{
    cout << "-----> Wellcome to the GK'SE, the Search Engine of the Great Knights! (build mode) <-----" << endl;

    cout<<"-> Trie Tests\n";
    Trie arvore;
    Node *p=arvore.insert("Jorge");
    p->put_doc(7);
    p->put_doc(47);
    p->put_doc(78);
    
    

    vector <int> d=arvore.find("Jorge");
    if(d.empty()){
        cout<<"Palavra Não Encontrada"<<endl;
    }else{
        cout<<"Resultados: ";
        print_vector(d);
    }

    vector <int> d2=arvore.find("Kenner");
    if(d2.empty()){
        cout<<"Palavra Não Encontrada"<<endl;
    }else{
        cout<<"Resultados: ";
        print_vector(d2);
    }

    return 0;
    
    
    
    
    
    
}*/
