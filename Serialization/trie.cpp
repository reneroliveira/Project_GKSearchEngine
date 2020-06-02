#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

struct Node
{
    int aKey;
    Node *aChild[36];
    vector<int> docs;

    void put_doc(int doc_id)
    {
        this->docs.push_back(doc_id);
    }

    Node()
    {
        for(int i = 0; i < 36; i++)
        {
            this->aChild[i] = nullptr;
        }
    }
    Node(int aIndex)
    {
        this->aKey = aIndex;
        this->docs = {};
        for(int i = 0; i < 36; i++)
        {
            this->aChild[i] = nullptr;
        }
    }
};

vector<int> convert(string aWord)
{
    vector<int> indexes;
    int aKey;

    for (char& aLetter : aWord)
    {
        if((int)aLetter < 123 && (int)aLetter > 96)
        {// Letras minúsculas.
            aKey = (int)aLetter - 87;
            indexes.push_back(aKey);
        }
        else if ((int)aLetter < 58 && (int)aLetter > 47)
        {// Números de 0 a 9.
            aKey = (int)aLetter - 48;
            indexes.push_back(aKey);
        }

        else if((int)aLetter < 91 && (int)aLetter > 64)
        {// Letras maiúsculas.
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
        // Methods;
        Node* insert(string aWord)//retorna um ponteiro ao nó final
        {
            Node **p = &(aRoot);
            insert(convert(aWord), p);
            return *p;
        }
        vector<int> find(string aWord){
            cout << endl << "-> Finding: " << aWord << "..." << endl;
            return find(convert(aWord));
        }
        void Serialize()
		{
			ofstream TextSerialize ("trieSerial.txt"); // Se quiser outro nome, também mude
			if (TextSerialize.is_open())               // no Deserialization() abaixo.
			{
				string Text = Serialize(aRoot);
				TextSerialize << Text;
				TextSerialize.close();
			}
		}
		void Deserialization()
		{
			Node *Current = aRoot; int Number = 0; int *Position = &Number;
			ifstream TextDeserialize ("trieSerial.txt"); // Sim, com esse nome mesmo.
			string Rain;
			TextDeserialize >> Rain;                     // Copiamos o texto para Line.
            string *Line = &Rain;

			ShootingChars(Line, Position, Current);
			TextDeserialize.close();
		}
    private:
        void insert(vector<int> indexes,Node**&p){
            for(int i:indexes){
                if((*p)->aChild[i]==nullptr)
                {
                    (*p)->aChild[i]=new Node(i);
                }
                p = &((*p)->aChild[i]);
            }
        }
        vector<int> find(vector<int> word)
        {
            Node **p = &aRoot;
            for (int i:word)
            {
                if (!((*p)->aChild[i])) return {};
                else p = &((*p)->aChild[i]);
            }
            return (*p)->docs;
        }
        string Serialize(Node *Current)
		{
			string Text ("");
			for (int i = 0; i < 36; i++)
			{
				if (Current->aChild[i] != nullptr)
				{
					Text += "+";
					Text += Serialize(Current->aChild[i]);
				}
				else Text += "n";
			}
			if (Current->docs.empty()) Text += "{}";
            else
            {
                Text += "{";
                for (int Int : Current->docs)
                {
                    Text += to_string(Int) + ",";
                }
                Text += "}";
            }
			return Text;
		}
		void ShootingChars(string *List, int *&Position, Node *&Current) // Auxilia a
		{                                                               // Deserialization().
		    Node *NextNode;
			for (int Count = 0; Count < 26; Count++)
			{
				if (*(List[*Position]) == 'n') *Position += 1;
				else if (List[*Position] == '+')
				{
					Current->aChild[Count] = new Node(Count);
					NextNode = Current->aChild[Count];
					*Position += 1;
					ShootingChars(List, Position, NextNode);
				}
			}
			if (List[*Position] == '{')
			{
				*Position += 1;
                if (List)
                Current->IsEnd = true;
				
			}
		}
};
