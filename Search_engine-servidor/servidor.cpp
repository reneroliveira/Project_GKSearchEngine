#include "lib/server_http.hpp" //Chamando pacotes do Simple Web Server
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include "teste.cpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;



Trie GKSE;
void start(){
	inicializa(GKSE);
}


int main(){
	start();
    
//sabemos que it->second armazena nossa palavra do formulario e 
// stream << "{\"res\":\"" <<  it->second << img_button << "\"}"; é responsavel por mostra ela
	HttpServer server;
	server.config.port = 8080; //porta do servidor será localhost/8080
	//server.init
	//função que recebe query do tipo localhost:8080/query?text={text}
	server.resource["^/query$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request){
		//Trecho do código para obter a query (consulta)
		
		auto query_fields = request->parse_query_string(); //Recebe o conteúdo de "entrada"
		auto it = query_fields.find("text"); // Obtem o texto do conteudo
		cout << it->second << endl;
<<<<<<< HEAD
		
		
    
		
=======
>>>>>>> 7c3a0284017973e8dbc0a4f5b6eb6f33c41f2400
		//A resposta para o servidor vai ser um JSON do formato
		//{"res": "O seu projeto final vai ser incrível, [texto]!"}	
		//JSON
		// {"atributo1":"valor1",
		//	"atributo2": {"sub-atributo": "valor2"}} 
<<<<<<< HEAD
		string img_button = "</br> <input id = 'btn_img' type = 'button' onclick='print_img()' value ='Me clique!'> </br>";
		vector<std::string> resultado;
		stringstream res;
               vector<Pair> rest = pesquisa(it->second,GKSE); 
               int tamanho = rest.size();
               ifstream arquivoE;
               string linha;
			   string preffix="./../aNames/";
			  
     /////////////////////////////////////          //função find + transforma em string
                for(int k = 0;k<min(20,tamanho);k++){//só pega 20 resultados
					int number = rest[k][0] / 10000;
					 string name = "aTitles_" + to_string(number*10000) + "_" + to_string((number+1)*10000) + ".txt";
               arquivoE.open(preffix+name);
                int i = 0;
                int numero = 0;
                if(arquivoE.is_open()){
              while(getline(arquivoE,linha)){
					//aqui podemos fazer operaões linha a linha
					stringstream geek(linha);
					geek >> numero;
					
					for(int j  = 0;j<tamanho;j++){
						if(rest[j][0] == numero){
							resultado.push_back(linha);
						}
					}            
                }
  			}
				};
  //////////////////////////////////////////////////////
  //resultado =string com os titulos
               /*std::string resultado = " ";
               resultado = resultado +std::to_string(rest[0]); */
                if(it->second == "sleep"){
		res << "{\"res\":\"" << resultado[0] << "\"}";
		response->write(res);
		}
		
		else{ 
		for(int k=0;k<resultado.size();k++){
		res << "{\"res\":\"" << resultado[k] <<"</BR>"<< "\"}";
		}
		cout << res.str();
		response->write(res);
		}
=======
		string img_button = "</br> <input id = 'btn_img' type = 'button' onclick='print_img()' value ='Me clique!'> </br>";	        vector<string> resultado;
		stringstream res;
               vector<int> rest = pesquisa(it->second);
               vector<string> canvas;
               vector<int> thor;
               int tamanho = rest.size();
               for(int i =0;i<tamanho;i++){
               canvas.push_back(std::to_string(rest[i]));
}                int numero = 0;
                 int y = 0;
                 int nabos  = 0;
                string name = "aTitles_0_10000.txt";
                vector<string>titulos;
                titulos.push_back("textos.txt");
                ifstream arquivoE;
                string linha;
                arquivoE.open(titulos[0]);
                if(arquivoE.is_open()){
              while(getline(arquivoE,linha)){
                //aqui podemos fazer operaões linha a linha
                stringstream geek(linha);
                geek >> numero;
                
                for(int j  = 0;j<tamanho;j++){
                stringstream can(canvas[j]);
                can >> y;
                thor.push_back(y);
                if(y == numero){
                resultado.push_back(linha);
                
                
                
                }
                }            
               
     
    }
  };           int r = resultado.size();
               if(r == 0){
               res << "{\"res\":\"" << "nenhum resultado encontrado" <<"\"}";
               
               }
               else{
 
               res << "{\"res\":\"" << thor[0] << "</br>" << thor[2] << "</br>" <<thor[1] <<  "</br>" <<  thor[3]<<"\"}";
	       response->write(res);}
	       
	       
		
>>>>>>> 7c3a0284017973e8dbc0a4f5b6eb6f33c41f2400
	};
	
	
	
	//O método default do server é abrir um arquivo na pasta web/
	//vai receber querys do tipo localhost:8080/{text}
  	server.default_resource["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
		auto path = "./web/"+request->path; //caminho até os arquivos do tipo HTML
		SimpleWeb::CaseInsensitiveMultimap header;
		std::ifstream ifs(path, ifstream::in | ios::binary | ios::ate); //abrindo o arquivo dentro da pasta /web
		auto length = ifs.tellg();
       	ifs.seekg(0, ios::beg);
       	stringstream stream;
       	stream << ifs.rdbuf(); //salvando o conteúdo em uma stringstream

        header.emplace("Content-Length", to_string(length));
        response->write(header);
        response->write(stream.str().c_str(), length); //e inserindo na resposta do servidor
    };

	//função para lidar com erros (não necessário)
    server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
		//code
	};


    thread server_thread([&server]() {
        // Start server
        server.start();
    });

    // Wait for server to start so that the client can connect
    this_thread::sleep_for(chrono::seconds(1));

	server_thread.join();
}
