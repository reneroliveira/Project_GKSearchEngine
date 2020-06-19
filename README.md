# Projeto Great Knights' Search Engine
  
Este repositório contém o projeto do curso de Estruturas de Dados e Algoritmos, dada na FGV.  
Observação: quando a pasta "raw.en" ou diretório "raw.en/" for citada, ela se refere à pasta que contém todos os dados originais para o banco da dados. Pode ser obtida extraindo-a deste [arquivo](https://www.cs.upc.edu/~nlp/wikicorpus/raw.en.tgz).
  
1. A pasta "DataTreatment" contém instruções para a preparação dos dados para a montagem da árvore.  

2. A pasta Search-engine-servidor contém instruções para executar a interface web.

## Uso do programa

- Certifique-se que tenha as seguintes bibliotecas: string.h, vector, iostream, fstream,sstream, chrono, algorithm, exception, thread e boost*

> Obs: O boost só será necessário para interface web.

- Baixe o zip [deste link](https://drive.google.com/file/d/1C1REE2hm8JPc5KaK1YxJmO_M29VrZB8-/view?usp=sharing), e extraia-o nesta pasta raiz, o que tem que aparecer aqui são os arquivos trieSerial, e as pastas aNames e aTexts

Após isso compile o arquivo engine.cpp, em um terminal com gcc compiler instalado.

O comando é o seguinte:

g++ engine.cpp -o engine && ./engine

Depois disso, ele vai demorar de 2 a 4min para descerializar a árvore, aguarde ....

Após a desserialização, as buscas fcam liberadas pelo terminal, e o restante das instruções são dadas pelo próprio programa :)