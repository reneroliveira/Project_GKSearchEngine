#include "trie_builder.cpp"
#include <chrono>
#include <iostream>


using namespace std;
int main(){
    int num_docs=63;//Número entre 0 e 63
    Trie GKSE=build(num_docs);


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
        //cout << "-> Google! Hire us immediately!!" << endl;

        if(res.empty())
        {
            GKSE.suggest(query);
            
        }
        else
        {
            cout << "-> Results:" << endl;
            int counting = 0;
            vector<int> res20;

            while (1) // Hehe, de novo eim.
            {
                if (res.size() > counting + 20)
                {
                    res20=vector<int>(res.begin()+counting,res.begin()+counting+20);
                } else {
                    res20=vector<int>(res.begin()+counting,res.end());
                }
                print_vector(res20,counting);
                cout << endl << "-> Do you want to open any result [n or result number]? ";
                string answer;
                cin >> answer;
                if (answer != "n")
                {
                    cout<< aDocs(res[(stoi(answer)-1)]);
                }
                if (res.size() > counting + 20) // Esse if ocorre quando mais artigos
                {                               // estão disponíveis.
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