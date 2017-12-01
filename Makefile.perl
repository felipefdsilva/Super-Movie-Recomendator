# Universidade Federal do Rio de Janeiro
# Escola Politecnica
# Departamento de Eletronica e de Computacao
# Linguagens de Programação - Turma 2017/2
# Prof. Miguel Campista
# Autor: Felipe Ferreira da Silva

CCPP=g++
LCPP=g++

CCPPFLAGS=`perl -MExtUtils::Embed -e ccopts`
LCPPFLAGS=`perl -MExtUtils::Embed -e ldopts`

SMROBJS= mainSmr.o recomendator.o marathon.o movie.o production.o split.o wrapper.o

EXECS=SMR

.cpp.o:
	$(CCPP) -c $< $(CCPPFLAGS)

all:$(EXECS)

SMR: $(SMROBJS)
	$(LCPP) -o $@ $? $(LCPPFLAGS)

clean:
	rm -f *.o $(EXECS)
