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
  my @movie; my @year; my @length;
  my @genres; my @IMDBscore;
  my @Metascore; my @synopsis;
  my @directors; my @stars;
  my $getNextLines = FALSE;

  my $niceHtml = HTML::FormatText->format_file
  ($filename, leftmargin => 0, rightmargin => 300);

  my @niceHtml = split(/\n/, $niceHtml);

  foreach (@niceHtml){
    if (/^(?:\d{1,2}\.) ([\S\s]*) (?:\()(\d{4})(?:\))$/){
      push @movie, $1;
      push @year, "Year: ".$2;
      $getNextLines = TRUE;
    }
    if ($getNextLines){
      if (/(?:(?:\d{1,2}|\w+)\s\|\s)?(\d{1,3}) (?:min\s\|) ((\w+-?,?\s?)+)$/){
        push @length, "Length (min): ".$1;
        push @genres, "Genres: ".$2;
      } elsif (/^(\d{1,2}\.?\d) (?:(?:\w+\s){12}\S*\sX)/){
        push @IMDBscore, "IMDB Score: ".$1;
        if (/(\d{2,3}) (?:Metascore)$/i){
          push @Metascore, "Metascore: ".$1;
        } else {
          push @Metascore, "Metascore: XX"
        }
      } elsif (/(?:Stars:) ([\S\s]+)$/i){
        push @stars, "Stars: ".$1;
        if (/^(?:Directors?:) ([\S\s]+)(?:\|\s)/i){
          push @directors, "Director(s): ".$1;
        } else {
          push @directors, "Director(s): XX";
        }
        $getNextLines=FALSE;
      } elsif (/^[A-Za-z.\-'"0-9:,.();!?#]/ && /(\.|\?|"|\!)$/){
        push @synopsis, "Synopsis: ".$_;
      }
    }
  }
  return "Movie", \@movie, "Year", \@year, "Length", \@length,
         "Genres", \@genres, "IMDB score", \@IMDBscore, "Metascore", \@Metascore,
         "Synopsis", \@synopsis, "Director(s)", \@directors, "Star", \@stars;
}
sub showFile {
  my %info = @_;
  my @infoType = keys %info;
  my $size = @{$info{$infoType[0]}};
  for (my $movie = 0; $movie < $size; $movie++){
    for (my $data = 0; $data < 9; $data++){
      if (!$data){
        print "\n",$movie+1,"\n";
      }
      print $infoType[$data], ": ", ${$info{$infoType[$data]}}[$movie],"\n";
    }
  }
}
sub moviesSelection {
  my %info = @{$_[0]};
  my @params = @{$_[1]};
  my @selectedMovies = [];
  my $index=0; my $flag=TRUE;
  foreach my $data (@{$info{"Movie"}}){
    foreach my $dataList (values %info){
      $selectedMovies[$index] .= ${$dataList}[$index]."\n";
    }
    $index++;
  }
  foreach my $movies (@selectedMovies){
    foreach(@params){
      if ($movies !~ /$_/){
        $flag = FALSE;
      }
    }
    if ($flag){
      print $movies,"\n";
    }
    $flag=TRUE;
  }
}

{
  #getHtmlFiles;
  #foreach (GENRES){
  #  print ((validateFile($ARGV[0]))[1]);
  #}
  my @info = getHtmlInfo ($ARGV[0]);
  push my @params, "2008";
  push @params, "Nolan";
  #showFile (@info);
  moviesSelection(\@info, \@params);
  exit(OK);
}
