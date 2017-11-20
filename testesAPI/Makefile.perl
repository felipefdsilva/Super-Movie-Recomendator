# Universidade Federal do Rio de Janeiro
# Escola Politecnica
# Departamento de Eletronica e de Computacao
# Linguagens de Programação - Turma 2017/2
# Prof. Miguel Campista
# Autor: Felipe Ferraira da Silva

CC=$(shell perl -V::cc:)
LD=$(shell perl -V::ld:)

CCFLAGS=$(shell perl -MExtUtils::Embed -e ccopts)
LDFLAGS=$(shell perl -MExtUtils::Embed -e ldopts)

EXECS=perl-ex perl-ex2 perl-ex3 perl-ex4

.c.o:
	$(CC) $(CCFLAGS) -c $<

all:$(EXECS)

perl-ex: perl-ex.o
	$(LD) -o $@ $? $(LDFLAGS)

perl-ex2: perl-ex2.o
	$(LD) -o $@ $? $(LDFLAGS)

perl-ex3: perl-ex3.o
	$(LD) -o $@ $? $(LDFLAGS)

perl-ex4: perl-ex4.o
	$(LD) -o $@ $? $(LDFLAGS)

clean:
	rm -f *.o $(EXECS)
