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
                        Drama Family Fantasy
                        Film-Noir History Horror
                        Music Musical Mystery
                        Romance Sci-Fi Sport
                        Thriller War Western);

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
  my @stars; my $getNextLines = FALSE;

  my $niceHtml = HTML::FormatText->format_file
  ($filename, leftmargin => 0, rightmargin => 300);

  my @niceHtml = split(/\n/, $niceHtml);

  foreach (@niceHtml){
    if (/^(?:\d{1,2}\.) ([\S\s]*) (?:\()(\d{4})(?:\))$/){
      push @movie, $1;
      $getNextLines = TRUE;
    }
    if ($getNextLines){
      if (/(?:(?:\d{1,2}|\w+)\s\|\s)?(\d{1,3})(?:\smin\s\|\s)((\w+-?,?\s?)+)$/){
        push @length, "Length (min): ".$1;
        push @genres, "Genres: ".$2;
      } elsif (/^(\d{1,2}\.?\d)(?:\s(?:\w+\s){12}\S*\sX)/){
        push @IMDBscore, "IMDB Score: ".$1;
        if (/(\d{2,3})(?:\sMetascore)$/i){
          push @Metascore, "Metascore: ".$1;
        } else {
          push @Metascore, "Metascore: ??"
        }
      } elsif (/^[A-Za-z.\-'"0-9:,.();!?]/ && /(\.|\?|")$/ && $_ !~ /IMdb.com/i){
        push @synopsis, "Synopsis: ".$_;
      } elsif (/^(?:Directors?:\s)([\S\s]+)(?:\|\sStars:\s)([\S\s]+)/i){
        push @directors, "Director(s): ".$1;
        push @stars, "Stars: ".$2;
        $getNextLines=FALSE;
      }
    }
  }
  return \@movie, \@length, \@genres, \@IMDBscore, \@Metascore, \@synopsis, \@directors, \@stars;
}
sub showFile {
  my @info = @_;
  my $size = @{$info[0]};
  print "1\n";
  for (my $movie = 0; $movie < $size; $movie++){
    for (my $data=0; $data < 8; $data++) {
      print ${$info[$data]}[$movie],"\n";
      if ($data == 7 && $movie != $size-1){print "\n\n",$movie+2,"\n";}
    }
  }
}
#sub removeRepetitions {
#}
#sub analyseSearch {
#}
{
  #getHtmlFiles;
  #foreach (GENRES){
  #  print ((validateFile($ARGV[0]))[1]);
  #}
  my @info = getHtmlInfo ($ARGV[0]);
  showFile (@info);
  exit(OK);
}
