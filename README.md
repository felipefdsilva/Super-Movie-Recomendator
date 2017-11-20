# Super-Movie-Recomendator
Recomends movies based on user's informations

## Parte III - Final Boss
Parâmetros de entrada:
  
    Tempo Disponível
    Gênero(s) [!]
    Ator(es)
    Ano (Faixa de Anos)
    Diretor(es)
    Nota de corte
    Humor [?]
  
### Função selectFilesAndKeyWords
  Dados os parâmetros, os arquivos html serão selecionados e algumas palavras chave para busca, e o módulo perl será chamado. 
### Função marathonTime
  Calcula o tempo total de maratona, somando a duração de cada filme
### Função removeRepetitions
  Recebe a lista tirada de cada arquivo e cria apenas uma, sem repetições. Provavelmente com o auxilio da STL map.
### Função SelectMovies
  Desta lista, seleciona 3 para indicar ao usuário. (Como fazer esta ultima filtragem?)
### Função sortMovies
  Ordena os filmes na ordem em que devem ser assistidos
### Função avaliateSearch
  Avalia a lista entregue pelo módulo perl, e, caso seja muito grande, refaz a busca com parâmetros mais restritivos.
