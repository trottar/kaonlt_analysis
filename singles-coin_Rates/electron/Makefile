#
# NOTE: in order to use this for the ntuples created on general, histo_maker.f MUST
# be compiled on general!!!!!!!
#

my_objs = qfsv.o

INC = 
RM        = rm -f 
SHELL     = /bin/sh

ifeq ($(OSTYPE),HPUX)
  FFLAGS=+U77 +ppu -C +es -O +Obb1000 +FPVZOU
  LDFLAGS=-Wl,-a archive
  OTHERLIBS =
endif

ifeq ($(OSTYPE),ULTRIX)
  FFLAGS=-check_bounds
  LDFLAGS=
  OTHERLIBS =
endif

ifeq ($(OSTYPE),OSF1)
  FFLAGS=-O -C -extend_source -fpe
  LDFLAGS=
  OTHERLIBS =
endif

ifeq ($(OSTYPE),linux)
  FFLAGS=-g -O 
  LDFLAGS=
  OTHERLIBS=-L/usr/X11R6/lib -lcrypt -lXt -lXext -lXp -lX11 -lcrypt -ldl -lnsl
  F77 = g77
endif

none: run_qfs

all: run_qfs

run_qfs: $(my_objs) run_qfs.o Makefile $(OURLIBS)
	$(F77) -g -o  $@ $(FFLAGS) run_qfs.o $(my_objs) $(OTHERLIBS)

clean: 
	$(RM) *.o run_qfs



