#!/bin/bash
# Universidade Federal do Rio de Janeiro
# Escola Politecnica
# Departamento de Engenharia Eletronica e de Computacao
# Linguagens de Programacao 2017.2
# 
# Professor: Miguel Elias Mitre Campista
#
# Aluno: Felipe Ferreira da Silva
# install.sh
 
currentDirectory=$(pwd)
mkdir Super-Movie-Recomendator
cd Super-Movie-Recomendator
perl Makefile.PL INSTALL_BASE=$currentDirectory
make
make install
cd $currentDirectory
export PERL5LIB=$currentDirectory/Super-Movie-Recomendator/lib/perl5
