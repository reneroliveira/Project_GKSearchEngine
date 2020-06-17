# Projeto Great Knights' Search Engine
  
Este repositório contém o projeto do curso de Estruturas de Dados e Algoritmos, dada na FGV.  
Observação: quando a pasta "raw.en" ou diretório "raw.en/" for citada, ela se refere à pasta que contém todos os dados originais para o banco da dados. Pode ser obtida extraindo-a deste [arquivo](https://www.cs.upc.edu/~nlp/wikicorpus/raw.en.tgz).
  
1. A pasta "DataTreatment" contém instruções para a preparação dos dados para a montagem da árvore.  

> Dentro de **DataTreatment**, existe uma pasta mágica chamada **aTales**. Por lá têm tentativas honradas de retornar textos.

## Construção da árvore (via dados tratados)

1. Baixe [deste link](https://bit.ly/36sinp3) os arquivos **"sorted_words2.zip"**, "aNames.zip" e "aTexts.zip" e o descompacte na mesma pasta deste arquivo readme. 
> Este novo zip, sorted_words2 considera guarda também a frequência das palavras.
2. Compile e execute o arquivo "engine.cpp". Pode usar o terminal, ou alguma IDE de sua preferência.
> Na linha 9 do engine.cpp você pode altera o valor de  int num_docs para algum número menor que 63.
> Pra contruir a árvore completa são necessários no mínimo 4,7 GB de RAM. Caso não tenha, mude a variável acima para algum menor.
3. Aguarde a construção da árvore e digite sua busca (digite apenas uma palavra, e sem acentos ou caracteres não-alfanuméricos)

## Construção da árvore (via desserialização)

... Carregando ...

