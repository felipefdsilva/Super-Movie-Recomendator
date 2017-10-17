# Universidade Federal do Rio de Janeiro
# Departamento de Engenharia Eletrônica e de Computação
# Linguagens de Programação 2017.2
# Professor Miguel Campista
# Autor: Felipe Ferreira da Silva
# Trabalho do Período - Parte 2 (Perl)
# Recomendador de Filmes e Maratonas

use 5.022001;
use warnings;
use strict;
use LWP::Simple qw(get);

use constant OK=>0;
use constant {FALSE=>0, TRUE=>1};

use constant DOMAIN=>'http://www.imdb.com/search/title?view=advanced&sort=num_votes,desc&genres=';
use constant GENRES=>qw(Action Adventure Animation
                        Biography Comedy Crime
                        Documentary Drama Family
                        Fantasy Film-Noir History
                        Horror Music Musical
                        Mystery Romance Sci-Fi
                        Sport Thriller War Western);

sub getData {
  foreach my $genre (GENRES) {
  	say "Start DOMAIN$genre";
    my $html = get(DOMAIN.$genre);

    open (my $fileHandler, '>>', './Dados/'.$genre.'.html')
    or die ("Could not create file.\n", $!);

    say $fileHandler $html;

    close $fileHandler;

    say "File $genre.html created";
  }
}
sub validateFile {
	my $file = $_[0];
  my $genre;
  my $match = FALSE;
  my $doctype = FALSE;
  my $htmlMatch = FALSE;
  my $imdbMatch = FALSE;
  my $genreMatch = FALSE;
  my $movieMatch = FALSE;

  #Checking file name
  foreach (GENRES){
    if ($file =~/^$_.html$/i){$match=TRUE;}
    $genre = $_;
  }
	return (FALSE, "Not valid filename (imdb html files only)\n")
	if ($match == FALSE);
  #end of file name check

  open (my $fileHandler, "<", './Dados/'.$genre.'.html')
  or die ("Could not open file.\n", $!);

  if (<$fileHandler>!~/1/g) {return (FALSE, "Not a valid html file 1\n");}

  while (<$fileHandler>){
    if ($_=~/<!DOCTYPE html>/) {$doctype=TRUE;}
    if ($_=~/(H|h)(T|t)(M|m)(L|l)/g){$htmlMatch=TRUE;}
    if ($_=~/imdb/ig){$imdbMatch=TRUE;}
    if ($_=~/$genre/ig) {$genreMatch=TRUE;}
    if ($_=~/movie/g) {$movieMatch=TRUE;}
  }
  close $fileHandler
  or die ("Could not close file.\n", $!);

  if ($doctype && $htmlMatch && $imdbMatch && $genreMatch && $movieMatch){
    return (TRUE, "This is a nice and valid file\n");
  }
  return (FALSE, "Not a valid html file (keyword not found)\n");
}

sub formatHtmlFile {
  my $filename = $_[0];
  my @movieList;
  open (my $fileHandler, "<", './Dados/'.$filename)
  or die ("Could not open file.\n", $!);
  my $i=1;
  foreach (<$fileHandler>){
    if($_=~/^>[\s\S]+<\/a>$/){
      if ($i==4){
        push @movieList, $_;
        print $_;
        $i=1;
      }
      $i++;
    }
  }
  close $fileHandler
  or die ("Could not close file.\n", $!);
}

{
  #getData;
  #print ((validateFile('drama.html'))[1]);
  formatHtmlFile ('Action.html');
  exit(OK);
}
