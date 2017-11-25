# Universidade Federal do Rio de Janeiro
# Departamento de Engenharia Eletrônica e de Computação
# Linguagens de Programação 2017.2
# Professor Miguel Campista
# Autor: Felipe Ferreira da Silva
# Trabalho do Período - Parte 2 (Perl)
# Recomendador de Filmes e Maratonas

package smr;

use 5.022001;
use strict;
use warnings;
use Carp;
use HTML::FormatText;

require Exporter;

our @ISA = qw(Exporter);

# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.

# This allows declaration	use smr ':all';
# If you do not need this, moving things directly into @EXPORT or @EXPORT_OK
# will save memory.
our %EXPORT_TAGS = ( 'all' => [ qw(
FALSE
TRUE
URL
GENRES
validateFile
getInfo
createMovieStrings
) ] );

our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );

our @EXPORT = qw(

);

our $VERSION = '0.01';

use constant {FALSE=>0,
              TRUE=>1};
use constant URL=>'http://www.imdb.com/search/title?view=advanced&sort=num_votes,desc&genres=';
use constant GENRES=>qw(
  Action
  Adventure
  Animation
  Biography
  Comedy
  Crime
  Drama
  Family
  Fantasy
  Film-Noir
  History
  Horror
  Music
  Musical
  Mystery
  Romance
  Sci-Fi
  Sport
  Thriller
  War
  Western
);


# Valida o arquivo passado pelo usuario
# segundo um teste básico de credibilidade
# e checando a extensão e o nome do arquivo
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
# Usa regex para identificar e salvar
# informações dos filmes
sub getInfo {
  my $filename = $_[0];
  my @movie;
  my @year;
  my @length;
  my @genres;
  my @IMDBscore;
  my @synopsis;
  my @directors;
  my @stars;
  my $getNextLines = FALSE;

	# Formatação prévia do arquivo html (sem tags)
  my $niceHtml = HTML::FormatText->format_file
  ($filename, leftmargin => 0, rightmargin => 300);
	# Fim da formatação
  my @niceHtml = split(/\n/, $niceHtml);

	# Busca por informações
  foreach (@niceHtml){
		# Busca por filmes e ano de laçamento
    if (/^(?:\d{1,2}\.) ([\S\s]*) (?:\()(\d{4})(?:\))$/){
      push @movie, $1; push @year, $2;
      $getNextLines = TRUE;
    }
    if ($getNextLines){
			# Busca a duração e os gêneros
      if (/(?:(?:\d{1,2}|\w+)\s\|\s)?(\d{1,3}) (?:min\s\|) ((\w+-?,?\s?)+)$/){
        push @length, $1; push @genres, $2;
			# Busca as notas dos usuários
      } elsif (/^(\d{1,2}\.?\d) (?:(?:\w+\s){12}\S*\sX)/){
        push @IMDBscore, $1;
			# Busca pelo atores principais e diretores
      } elsif (/(?:Stars:) ([\S\s]+)$/i){
        push @stars, $1;
        if (/^(?:Directors?:) ([\S\s]+)(?:\|\s)/i){
          push @directors, $1;
        } else {
          push @directors, "XX";
        }
        $getNextLines=FALSE;
			# Busca pela sinopse
      } elsif (/^[A-Za-z.\-'"0-9:,.();!?#]/ && /(\.|\?|"|\!)$/){
        push @synopsis, $_;
      }
    }
  }
  return \@movie, \@year, \@length, \@genres,
         \@IMDBscore, \@synopsis, \@directors, \@stars;
}
# Concatena as informaçoess de um mesmo filme
# antes separadas em listas diferentes
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
1;
__END__
=head1 NAME

smr - Perl extension for Super-Movie-Recomendator project

=head1 SYNOPSIS

  use smr;

=head1 DESCRIPTION

Functions: getHtmlFiles, validateFile, getInfo, createMovieStrings, showFile, moviesSelection

=head2 EXPORT

All Functions

=head1 SEE ALSO

https://github.com/felipefdsilva/Super-Movie-Recomendator

=head1 AUTHOR

Felipe, E<lt>felipeferreira@poli.ufrj.brE<gt>

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2017 by Felipe

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.22.1 or,
at your option, any later version of Perl 5 you may have available.
=cut
