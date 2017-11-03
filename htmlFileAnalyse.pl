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

use constant URL=>'http://www.imdb.com/search/title?view=advanced&sort=num_votes,desc&genres=';
use constant GENRES=>qw(Action Adventure Animation
                        Biography Comedy Crime
                        Documentary Drama Family
                        Fantasy Film-Noir History
                        Horror Music Musical
                        Mystery Romance Sci-Fi
                        Sport Thriller War Western);

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
sub validateFile {
	my $file = $_[0];
  my $credibility = 0;
  my $genre;

  foreach (GENRES){
    if ($file =~ /$_(.html)$/){
      $genre = $_;
      $credibility++;
      last;
    }
  }
  return (FALSE, "Not valid filename (imdb html files only)\n")
  unless ($credibility);

  open (my $fileHandler, "<", $file)
  or die ("Could not open file.\n", $!);

  while (<$fileHandler>){
    if (/(<!DOCTYPE html>)|html|img|href|body|head|
    imdb|$genre|movie|directors?|actors|rate/i){
      $credibility++;
    }
  }
  close $fileHandler
  or die ("Could not close file.\n", $!);

  return (FALSE, "Not a valid html file (low credibility)\n")
  unless($credibility > 1800 && $credibility < 2000);

  return (TRUE, "This is a nice and valid file\n");
}

sub getHtmlInfo {
  my $filename = $_[0];
  my @movie; my @length; my @genres;
  my @IMDBscore; my @Metascore;
  my @synopsis; my @directors;
  my @stars;

  my $niceHtml = HTML::FormatText->format_file
  ('./Dados/'.$filename, leftmargin => 0, rightmargin => 300);

  my @niceHtml = split(/\n/, $niceHtml);

  foreach (@niceHtml){
    if (/^(?:\d{1,2}\.) ([\S\s]*) (?:\()(\d{4})(?:\))$/){
      push @movie, $1;
    } elsif (/(?:\d{1,2}) (?:\|) (\d*) (?:min) (?:\|) ((\w+-?,?\s?)+)/){
      push @length, $1;
      push @genres, $2;
    } elsif (/^(\d{1,2}\.?\d)(?:\s(?:\w+\s){12}\S*\sX\s)(\d{2})(?:\s\w+)$/){
      push @IMDBscore, $1;
      push @Metascore, $2;
    } elsif (/^[A-Za-z.\-'0-9:,.();!?]/ && /(\.|\?)$/ && $_ !~ /IMdb.com/i){
      push @synopsis, $_;
    } elsif (/(?:Directors?:\s)((?:\w+\.?|\s|,)+)(?:\|\sStars:\s)([\W\w]+)/i){
      push @directors, $1;
      push @stars, $2;
    }
  }
}

{
  #getHtmlFiles;
  #foreach (GENRES){
  #  print ((validateFile($ARGV[0]))[1]);
  #}
  getHtmlInfo ($ARGV[0]);
  exit(OK);
}
