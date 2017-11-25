# Super-Movie-Recomendator
It recomends movies marathons!

## Part III - Final Boss
Parâmetros de entrada:

    Tempo Máximo
    Gênero [!]
    Ator
    Ano (Faixa de Anos)
    Diretor
    Nota de corte

  ### Classes

  ```c++
    class PerlWrapper {
      public:
        PerlWrapper (int *, char ***, char ***);
        ~PerlWrapper ();
        void runInterpreterWithPerlFile (char *file);
        void renewFiles ();
        void showMovieByGenre (const char *);
        void retrieveMovieCandidates (const char *,
                                      const char **,
                                      unsigned,
                                      vector<string> &);

      private:
        PerlInterpreter *my_perl;
        char *my_argv[2];
    };
    class Production {
      public:
        void setName (string);
        string getName () const;

        void setAuthor (string);
        string getAuthor () const;

        void setYear (string);
        unsigned getYear() const;
      private:
        string mName, mAuthor;
        unsigned mYear;
    };
    class Movie: public Production {
      friend ostream &operator<< (ostream &, const Movie &);

      public:
        Movie (string, const unsigned = 4, const unsigned = 5);

        void splitString (string, string, vector<string> &);

        void setSinopsys (string);
        string getSinopsys () const;

        void setActors (string);
        void getActors (vector<string> &) const;

        void setGenres (string);
        void getGenres (vector<string> &) const;

        void setLength (string);
        unsigned getLength () const;

        void setRating (string, string);
        float getRating () const;

      private:
        string mSinopsys;
        unsigned mLength;
        float mRating;
        vector<string> mActors;
        vector<string> mGenres;
      };
      class Marathon: public map<string, Movie *> {
        friend ostream &operator<< (ostream &, const Marathon &);

        public:
          Marathon (unsigned = 0);
          void calculateDuration ();
          unsigned getDuration ();

        private:
          unsigned mDuration;
      };
  ```
  ### Funções que faltam

  #### 1. selectFilesAndKeyWords
    * Dados os parâmetros, serão selecionados os arquivos e algumas palavras-chave para busca e então, o módulo perl será chamado.
  #### 2. SelectMovies
    * Desta lista, seleciona 3 para indicar ao usuário. (Como fazer esta ultima filtragem?)
      * Pesos?
  #### 3. sortMovies
    * Ordena os filmes na ordem em que devem ser assistidos
  #### 4. sortMoviesByRating
    * Ordena filmes pela sua nota no IMDb.
