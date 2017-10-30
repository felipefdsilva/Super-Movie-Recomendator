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
use HTML::FormatText;

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
  my $genre = FALSE;
  my $doctype = FALSE;
  my $htmlMatch = FALSE;
  my $imdbMatch = FALSE;
  my $genreMatch = FALSE;
  my $movieMatch = FALSE;

  #Checking file name
  foreach (GENRES){
    if ($file =~/^$_.html$/i){$genre = $_;}
  }
	return (FALSE, "Not valid filename (imdb html files only)\n")
	if ($genre == FALSE);
  #end of file name check

  open (my $fileHandler, "<", './Dados/'.$genre.'.html')
  or die ("Could not open file.\n", $!);

  if (<$fileHandler>!~/1/g) {return (FALSE, "Not a valid html file (did not start with 1)\n");}

  while (<$fileHandler>){
    if ($_=~/<!DOCTYPE html>/ && $doctype==FALSE) {$doctype=TRUE;}
    if ($_=~/(H|h)(T|t)(M|m)(L|l)/g && $htmlMatch==FALSE){$htmlMatch=TRUE;}
    if ($_=~/imdb/ig && $imdbMatch==FALSE){$imdbMatch=TRUE;}
    if ($_=~/$genre/ig && $genreMatch==FALSE) {$genreMatch=TRUE;}
    if ($_=~/movie/g && $movieMatch==FALSE) {$movieMatch=TRUE;}
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
  my @ageLengthGenre;
  my @score;
  my @synopsis;
  my @director;
  my $niceHtml = HTML::FormatText->format_file
  ('./Dados/'.$filename, leftmargin => 0, rightmargin => 300);

  my @niceHtml = split(/\n/, $niceHtml);

  foreach (@niceHtml){
    if (/\d*\.\W\w+/ && /(\(\d{4}\))$/){
      push @movieList, $_;
      print $_,"\n";
    }
    if (/\d*\s\|\s\d*\smin\s\|\s\w*/){
      push @ageLengthGenre, $_;
      print $_,"\n";
    }
    if (/Rate this/i && /Metascore/i){
      push @score, $_;
      print $_,"\n";
    }
    if (/^[A-Za-z.\-'0-9:,.();!?]/ && /(\.|\?)$/ && $_ !~ /IMdb.com/i){
      push @synopsis, $_;
      print $_,"\n";
    }
    if (/^Director/i){
      push @director, $_;
      print $_,"\n\n";
    }
  }
}

{
  #getData;
  #print ((validateFile('drama.html'))[1]);
  formatHtmlFile ('Action.html');
  exit(OK);
}
