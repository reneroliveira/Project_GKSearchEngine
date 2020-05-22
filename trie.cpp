#include <string.h>
#include <vector>
#include <iostream>

using namespace std;

struct Node
{

    char aChar;
    bool aEnd;
    Node *aChild[36];
    vector<int> docs;

    Node(char aLetter)
    {
        this->aChar = aLetter;
        this->aEnd = false;
        this->docs = {};
        // Esta parte separa os caracteres. Os de 0 a 9 são os números, e os de 10 a 35 são as letras.
        aChild[0] = aChild[1] = aChild[2] = aChild[3] = aChild[4] = aChild[5] = aChild[6] = aChild[7] = aChild[8]
        = aChild[9] = aChild[10] = aChild[11] = aChild[12] = aChild[13] = aChild[14] = aChild[15] = aChild[16] = aChild[17]
        = aChild[18] = aChild[19] = aChild[20] = aChild[21] = aChild[22] = aChild[23] = aChild[24] = aChild[25] = aChild[26]
        = aChild[27] = aChild[28] = aChild[29] = aChild[30] = aChild[31] = aChild[32] = aChild[33] = aChild[34] = aChild[35]
        = nullptr;
    }
    
};
vector<int> convert(string aWord)
    {
        vector<int> int_word;
        
        // A ideia inicia é transformar a palavra numa sequência de caracteres, para depois transformá-los em índices
        // para serem identificados nos nós.
        //o vetor acima conterá os índices

        int aKey;
        cout << "-> Converting word: " << aWord <<endl;

        
        // Esta parte mosta as chaves dos caracteres. Isso serve para anexá-los nos nós-filhos.
        // (nada mais que testes maneiros)
        for (char& aLetter:aWord)
        {
            if ((int)aLetter < 90)
            {
                aKey = (int)aLetter - 48;
                int_word.push_back(aKey);
            }
            else
            {
                aKey = (int)aLetter - 87;
                int_word.push_back(aKey);
            }
        }
    return int_word;
    }
class Trie
{
protected:
    Node *aRoot;
public:
    Trie():aRoot(nullptr)
    {
        cout << endl << "-> Starting trie build..." << endl;
    }
    ~Trie()
    {
        cout  << "-> Build finished." << endl;
    }
    void insert(vector<int> v){///Tive problemas aqui não consegui completar
        for(int letter:v){
            cout<<letter<<" ";
        }
        cout<<endl;
    }
private:
    bool find(vector<int> word) {
        Node **p = &aRoot;
        for(int i:word) {
            if (!((*p)->aChild[i])) {return false;
            }
            else{
            p = &((*p)->aChild[i]);
            }
        }
        return true;
        }

        
    
    
};
void print_vector(vector<int> v){
    cout<<"-> ";
    for(int x:v){
    cout<<x<<" ";}
    cout<<"\n\n";
}
int main()
{
    cout << "-----> Wellcome to the GK'SE, the Search Engine of the Great Knights! (build mode) <-----" << endl;

    
    cout<<"-> Conversion Tests\n";
    print_vector(convert("aoba"));
    print_vector(convert("bacate"));
    print_vector(convert("1948"));
    print_vector(convert("autism"));
    cout<<(char)87;
    Trie arvore;
    arvore.insert(convert("rener"));
}
