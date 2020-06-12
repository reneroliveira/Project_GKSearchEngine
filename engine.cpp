#include "trie_builder.cpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <algorithm>


using namespace std;
int main(){
    int num_docs=10;//Número entre 0 e 63
    Trie GKSE=build(num_docs);
    Node *p;
    /*p=GKSE.insert("rener");
    Pair p1(15,7);
    Pair p2(16,3);
    p->put_doc(p1);
    p->put_doc(p2);*/
    while(1)
    {
        cout<<"-> Type your query: ";
        string query;
        vector<Pair>res;
        getline(cin,query);
        if(query=="0")
        {
            return 0;
        }
        
            auto time1 = chrono::high_resolution_clock::now();
            stringstream split_query;
            split_query<<query;
            string word;
            vector<vector<Pair>> all_words;
            while(split_query>>word){
                all_words.push_back(GKSE.find(word));
            }
            if(all_words.size()==1){
                auto time2 = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> t_search = time2 - time1;
                res = all_words[0];
                cout << "-> " << res.size() << " results found in " << t_search.count()/1000 << " seconds "<<"("<<t_search.count()<<" ms)." << endl;
            }else{
            res = intercept(all_words);
            auto time2 = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> t_search = time2 - time1;

            cout << "-> " << res.size() << " results found in " << t_search.count()/1000 << " seconds "<<"("<<t_search.count()<<" ms)." << endl;
            }
            if(all_words.size()==0){
                cout<<"All 0\n";
                continue;
            }
        

        if(res.empty())
        {
            if(all_words.size()==1){//só iremos sugerir no caso de busca de palavra única
            GKSE.suggest(query);
            }
            else{
                cout<<"Query Not Found !! Try typing a single word to get suggestions ;)"<<endl;
            }
            
        }
        
        else
        {
            
            cout << "-> Results:" << endl;
            sort(res.rbegin(),res.rend());//Faz a ordenação por frequência;
            int counting = 0;
            vector<Pair> res20;

            while (1) // Hehe, de novo eim.
            {
                if (res.size() > counting + 20)
                {
                    res20=vector<Pair>(res.begin()+counting,res.begin()+counting+20);
                } else {
                    res20=vector<Pair>(res.begin()+counting,res.end());
                }
                print_vector(res20,counting);
                cout << endl << "-> Do you want to open any result [n or result number]? ";
                string answer;
                int aIndex;
                cin>>answer;
                if (answer != "n"){
                
                    try // Depois colocarei as outras exeptions
                    {
                        aIndex = std::stoi(answer);
                    }
                    catch (const std::invalid_argument &aWrong)
                    {
                        std::cerr << " > Ooops. It's an invalid argument.\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        break;
                    }
                    cout<< aDocs(res[aIndex-1][0]);
                        
                }
                if (res.size() > counting + 20) // Esse if ocorre quando mais artigos
                {                               // estão disponíveis.
                    string answer2;
                    cout << "-> More results [y/n]? ";
                    cin >> answer2;
                    if (answer2 == "y") counting += 20;
                    else break;
                } else break;
               
            }
                
        }
            
            
            
        cout<< endl << "-> (To exit, enter the number 0)" << endl << endl;
    }
}