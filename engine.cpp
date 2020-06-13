#include "trie_builder.cpp"
#include <chrono>
#include <iostream>
#include <algorithm>


using namespace std;
int main(){
    int num_docs=63;//Número entre 0 e 63
    Trie GKSE=build(num_docs);
    
    while(1)
    {
        cout<<"-> Type your query: ";
        string input;
        string query;
        vector<Pair>res;
        while(cin){//Passo um tando doloroso pra capturar mais de uma palavra.
            cin >> input;
            query+=input;
            query+=" ";
            if (cin.get()=='\n'){
                query.pop_back();
                break;
            }
        }
        if(query=="0")
        {
            return 0;
        }
            auto time1 = chrono::high_resolution_clock::now();
            res = GKSE.find(query);
            auto time2 = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> t_search = time2 - time1;
            cout << "-> " << res.size() << " results found in " << t_search.count()/1000 << " seconds "<<"("<<t_search.count()<<" ms)." << endl;
        
            stringstream split2;
            split2<<query;
            string wrong_word;
            split2>>wrong_word;
            if(res.empty())
            {
                if(split2>>wrong_word){//só iremos sugerir no caso de busca de palavra única
                    cout<<"Query Not Found !! Try typing a single word to get suggestions ;)"<<endl;
                }
                else{
                    GKSE.suggest(wrong_word);
                }
            
        }
        
        else
        {
            
            cout << "-> Results:" << endl;
            sort(res.begin(),res.end());//Faz a ordenação por frequência;
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
                cin >> answer;
                if (answer != "n")
                {
                    try{
                    string Text = ShowText(answer,res,counting);
                    std::cout<<Text;
                    }
                    catch(const OutOfRange &e){//Colocarei mais exceptions futuramente;
                        std::cerr<<e.what();
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        continue;
                    }
                    catch (const std::invalid_argument &aWrong)
                    {
                        std::cerr << " > Ooops. It's an invalid argument.\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        continue;
                    }
                    catch (const std::out_of_range &aWrong)
                    {
                        std::cerr << " > Ooops. This can't be converted to an integer. It's too large!\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        continue;
                    }
                }
                if (res.size() > counting + 20) 
                {                               
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
           