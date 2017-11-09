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
use HTML::FormatText;
use LWP::Simple qw(get);
use Pod::Usage qw(pod2usage);
use Getopt::Long qw(GetOptions);

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
  return \@movie, \@year, \@length, \@genres, \@IMDBscore,
         \@Metascore, \@synopsis, \@directors, \@stars;
}
sub createMovieStrings {
  my @info = @_;
  my @movies;

  for (my $index=0; $index < (@{$info[0]}); $index++){
    foreach my $list (@info){
      $movies[$index] .= ${$list}[$index]."\n";
    }
  }
  return @movies;
}
sub showFile {
  my @movies = @_;
  my $index = 1;
  foreach (@movies){print $index++,"\n", $_,"\n\n";}
}
sub moviesSelection {
  my @movies = @{$_[0]};
  my @params = @{$_[1]};
  my @selectedMovies;
  my $flag=TRUE;

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
  return @selectedMovies;
}
{
  my $help; my $renew; my $file; my $show; my @params; my@info; my @movies;

  GetOptions ("help|?"=>\$help, "renew|?"=>\$renew, "file=s"=>\$file,
              "show|?"=>\$show, "search=s{1,9}"=>\@params) or pod2usage(2);

  pod2usage(-verbose=>2) if $help; #exibe ajuda no terminal
  if ($renew){getHtmlFiles; exit(OK);}

  #pod2usage("$0: No parameters given.")  if (@ARGV == 0);
  die ("Options are: --help, --renew, --file (requires --show or --search)\n")
  unless ($file && $show || $file && @params);

  if ($file){
    my @error = (validateFile($file));
    if (!$error[0]){
      print $error[1];
      exit(OK);
    }
    @info = getHtmlInfo ($file);
    @movies = createMovieStrings (@info);
  }
  if ($show){
    showFile (@movies);
  }
  if (@params){
    #my @params = split(',',$params);
    showFile(moviesSelection(\@movies, \@params));
  }
  exit(OK);
}
__END__

=head1 NAME

Super Movie Recomendador - get movie recomendations for your binge watching

=head1 SYNOPSIS

perl smr [--help][--renew][--file][--show]|[--search]

=head1 OPTIONS

=over 4

=item B<--help>

show this page

=item B<--show >

print list of most popular movies from imdb, given by the movie genre file

=item B<--renew>

renew movie genre html files stored

=item B<--search>

searchs on file from movies atending to the list of parameters given

=back

=head1 DESCRIPTION

B<This program> will ask for a html file fetched from imdb and return
movies based on parameters given by the user

=cut
