# Universidade Federal do Rio de Janeiro
# Departamento de Engenharia Eletrônica e de Computação
# Linguagens de Programação 2017.2
# Professor Miguel Campista
# Autor: Felipe Ferreira da Silva
# Trabalho do Período - Parte 2 (Perl)
# Recomendador de Filmes e Maratonas

use 5.022001;
use strict;
use warnings;
use smr ':all';
use LWP::Simple qw(get);

use constant OK=>0;
use constant INFO_TYPE=>qw(
  Title
  Year
  Length
  Genres
  Score
  Synopsis
  Director(s)
  Stars
);
#Renova acervo de arquivos html em dir=./Dados/
sub getHtmlFiles {
  foreach my $genre (GENRES) {
    say "Fetching ",URL.$genre;
    my $html = get(URL.$genre);

    open (my $fileHandler, '>:encoding(UTF-8)', './Dados/'.$genre.'.html')
    or die ("Could not create file.\n", $!);

    say $fileHandler $html;

    close $fileHandler;

    say "File $genre.html created";
  }
}
# Exibe o arquivo na tela
sub showFile {
  my $file = $_[0];
  print ((validateFile($file))[1]);
  my @info = getInfo($file);
  my $sizeInfo = @info;
  my $numMovies = @{$info[0]};
  for (my $movie = 0; $movie < $numMovies; $movie++){
    print "\n", 1 + $movie, "\n";
    for (my $data = 0; $data < $sizeInfo; $data++) {
      print ((INFO_TYPE)[$data], ": ", ${$info[$data]}[$movie], "\n");
    }
  }
}
# Realiza a busca por filmes que atendam
# aos parâmetros passados pelo usuário
sub moviesSelection {
  my $file = shift;
  my @params = @_;
  my @selectedMovies;
  my $flag=TRUE;

  print ((validateFile($file))[1]);
  my @info = getInfo($file);
  my @movies = createMovieStrings (@info);

  foreach my $movie (@movies){
    foreach(@params){
      if ($movie !~ /$_/){
        $flag=FALSE;
      }
    }
    if ($flag){
      push @selectedMovies, $movie;
    }
    $flag=TRUE;
  }
  my $numberOfMovies = @selectedMovies;
  push @selectedMovies, $numberOfMovies;
  return @selectedMovies;
}
