#include <vector>
#include <iostream>
/*#include <algorithm>
#include <boost/sort/spreadsort/spreadsort.hpp>*/

class Pair //Criei com letra maiúscula pois já existe std::pair no C++
{
public:
    int core[2];

    Pair(){//construtor vazio
        core[0]=0;
        core[1]=1;
    }
    Pair(int id,int freq){
        /*construtor com dois dados:
        ID vem primeiro, depois a frequencia
        Uso: Pair P(id,freq)
        */
        core[0]=id;
        core[1]=freq;    
    }
    Pair make_pair(int id,int freq){
        Pair P(id,freq);
        return P;
    }
    Pair(int data,bool index){
        core[index]=data;
        /*contrutor com apenas um dado:
        este dado é colocado no index passado pelo boleano
        se foi false, coloca em primeira, e verdadeiro em segundo;
        
        Talvez seja útil caso queira insertar 
        uma coisa de cada vez na deserialização*/
       
    }
    bool operator<(const Pair &p2){
        if(core[1]<p2.core[1]) return true;
        else return false;
    }
    int operator[](int i){
        return core[i];
    }
    void set(int data, bool index){
        this->core[index]=data;
    }

};

void printvp(std::vector<Pair> v){
    std::cout<<"\n";
    for(int i=0;i<v.size();i++){
        std::cout<<v[i][0]<<","<<v[i][1]<<" ";
    }
    std::cout<<"\n";
}

/*int main()
{   
    std::cout<<"Hello World!\n";
    pair P1(15,1);
    pair P2(16,5);
    pair P3(17,6);
    std::vector<pair> vec={P1,P2,P3};
    printvp(vec);
    std::sort(vec.rbegin(),vec.rend());
    printvp(vec);
    return 0;
}*/