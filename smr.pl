# Universidade Federal do Rio de Janeiro
# Departamento de Engenharia Eletrônica e de Computação
# Linguagens de Programação 2017.2
# Professor Miguel Campista
# Autor: Felipe Ferreira da Silva
# Trabalho do Período - Parte 2 (Perl)
# Recomendador de Filmes e Maratonas

use 5.022001;
use smr qw(
getHtmlFiles
validateFile
getInfo
createMovieStrings
showFile
moviesSelection
);
use strict;
use warnings;
use HTML::FormatText;
use LWP::Simple qw(get);
use Pod::Usage qw(pod2usage);
use Getopt::Long qw(GetOptions);

use constant OK=>0;

{
  my $help; my $renew; my $file; my $show; my @params; my@info; my @movies;

  GetOptions ("help|?"=>\$help, "renew|?"=>\$renew, "file=s"=>\$file,
              "show|?"=>\$show, "search=s{1,9}"=>\@params) or pod2usage(2);

  pod2usage(-verbose=>2) if $help; #exibe ajuda no terminal
  if ($renew){getHtmlFiles; exit(OK);}

  die ("Options are: --help, --renew, --file (requires --show or --search)\n")
  unless ($file && $show || $file && @params);

  if ($file){
    my @error = (validateFile($file));
    if (!$error[0]){
      print $error[1];
      exit(OK);
    }
    @info = getInfo ($file);
    @movies = createMovieStrings (@info);
  }
  if ($show){
    showFile (@movies);
  }
  if (@params){
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
