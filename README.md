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
    
### Funções

#### 1. selectFilesAndKeyWords
  * Dados os parâmetros, serão selecionados os arquivos e algumas palavras-chave para busca e então, o módulo perl será chamado.
#### 2. avaliateSearch (!!!!)
  * Avalia a lista entregue pelo módulo perl, e, caso seja muito grande, refaz a busca com parâmetros mais restritivos.
#### 3. removeRepetitions
  * Recebe a lista tirada de cada arquivo e cria apenas uma, sem repetições. 
    * STL __map__.
#### 4. SelectMovies (!!!!)
  * Desta lista, seleciona 3 para indicar ao usuário. (Como fazer esta ultima filtragem?)
    * Pesos?
#### 5. marathonTime
  * Calcula o tempo total de maratona, somando a duração de cada filme
#### 6. sortMovies
  * Ordena os filmes na ordem em que devem ser assistidos
  
  ### Classes
  
  ```c++
    Class Obra {
      private:
        string autor;
        string ano;
    };
    Class Movie: public Obra {
      ostream &operator<< (ostream &, Movie &);
      private:
        string name;
        string year;
        ...
    };
    Class Marathon {
      public:
        Marathon &operator+= (const Movie &);
      private:
        vector <Movie &> movies;
        unsigned time;
    };
  ```
