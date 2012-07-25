memory.o: memory.c
	cc -g -c memory.c -lm
runif.o: runif.c
	cc -g -c runif.c -lm
rutils.o: rutils.c
	cc -g -c rutils.c -lm

primes.o: primes.c
	cc -g -c primes.c -lm
galois.o: galois.c galois.h
	cc -g -c galois.c -lm
gfields.o: gfields.c galois.h xtnset.h xtndeclare.h xtndispatch.h
	cc -g -c gfields.c -lm
oa.o: oa.c
	cc -g -c oa.c -lm

construct.o: construct.c galois.h
	cc -g -c construct.c -lm
ak3.o: ak3.c galois.h
	cc -g -c ak3.c -lm
akconst.o: akconst.c galois.h
	cc -g -c akconst.c -lm
akn.o: akn.c galois.h
	cc -g -c akn.c -lm



bose.o: bose.c galois.h
	cc -g -c bose.c -lm
bose: bose.o construct.o akconst.o  oa.o primes.o gfields.o galois.o  memory.o
	cc -g -o bose bose.o construct.o akconst.o  oa.o primes.o gfields.o galois.o memory.o -lm

bush.o: bush.c galois.h
	cc -g -c bush.c -lm
bush: bush.o construct.o akconst.o  oa.o primes.o gfields.o galois.o  memory.o
	cc -g -o bush bush.o construct.o akconst.o  oa.o primes.o gfields.o galois.o memory.o -lm

busht.o: busht.c galois.h
	cc -g -c busht.c -lm
busht: busht.o construct.o akconst.o  oa.o primes.o gfields.o galois.o  memory.o
	cc -g -o busht busht.o construct.o akconst.o  oa.o primes.o gfields.o galois.o memory.o -lm


bosebush.o: bosebush.c galois.h
	cc -g -c bosebush.c -lm
bosebush: bosebush.o construct.o akconst.o  oa.o primes.o gfields.o galois.o  memory.o
	cc -g -o bosebush bosebush.o construct.o akconst.o  oa.o primes.o gfields.o galois.o memory.o -lm


bosebushl.o: bosebushl.c galois.h
	cc -g -c bosebushl.c -lm
bosebushl: bosebushl.o construct.o akconst.o  oa.o primes.o gfields.o galois.o  memory.o
	cc -g -o bosebushl bosebushl.o construct.o akconst.o  oa.o primes.o gfields.o galois.o memory.o -lm


addelkemp.o: addelkemp.c galois.h
	cc -g -c addelkemp.c -lm
addelkemp: addelkemp.o construct.o oa.o primes.o gfields.o galois.o  memory.o akconst.o
	cc -g -o addelkemp addelkemp.o construct.o oa.o primes.o gfields.o galois.o memory.o akconst.o -lm


addelkemp3.o: addelkemp3.c galois.h
	cc -g -c addelkemp3.c -lm
addelkemp3: addelkemp3.o ak3.o akconst.o oa.o primes.o gfields.o galois.o  memory.o
	cc -g -o addelkemp3 addelkemp3.o ak3.o akconst.o oa.o primes.o gfields.o galois.o memory.o -lm

addelkempn.o: addelkempn.c galois.h
	cc -g -c addelkempn.c -lm
addelkempn: addelkempn.o akn.o akconst.o oa.o primes.o gfields.o galois.o  memory.o
	cc -g -o addelkempn addelkempn.o akn.o akconst.o oa.o primes.o gfields.o galois.o memory.o -lm

oarand.o: oarand.c oa.h
	cc -g -c oarand.c -lm
oarand: oarand.o memory.o oa.o primes.o runif.o rutils.o
	cc -g -o oarand oarand.o memory.o oa.o primes.o runif.o rutils.o -lm

oaagree.o: oaagree.c oa.h
	cc -g -c oaagree.c -lm
oaagree: oaagree.o memory.o oa.o primes.o
	cc -g -o oaagree oaagree.o memory.o oa.o primes.o -lm

oatriple.o: oatriple.c oa.h
	cc -g -c oatriple.c -lm
oatriple: oatriple.o memory.o oa.o primes.o
	cc -g -o oatriple oatriple.o memory.o oa.o primes.o -lm

oadimen.o: oadimen.c oa.h
	cc -g -c oadimen.c -lm
oadimen: oadimen.o memory.o oa.o primes.o
	cc -g -o oadimen oadimen.o memory.o oa.o primes.o -lm


oastr1.o: oastr1.c oa.h
	cc -g -c oastr1.c -lm
oastr1: oastr1.o memory.o oa.o primes.o oa.h
	cc -g -o oastr1 oastr1.o memory.o oa.o primes.o -lm
oastr2.o: oastr2.c oa.h
	cc -g -c oastr2.c -lm
oastr2: oastr2.o memory.o oa.o primes.o oa.h
	cc -g -o oastr2 oastr2.o memory.o oa.o primes.o -lm
oastr3.o: oastr3.c oa.h
	cc -g -c oastr3.c oa.o primes.o -lm
oastr3: oastr3.o memory.o
	cc -g -o oastr3 oastr3.o memory.o oa.o primes.o -lm
oastr4.o: oastr4.c oa.h
	cc -g -c oastr4.c oa.o primes.o -lm
oastr4: oastr4.o memory.o
	cc -g -o oastr4 oastr4.o memory.o oa.o primes.o -lm
oastr.o: oastr.c oa.h
	cc -g -c oastr.c -lm
oastr: oastr.o memory.o oa.o primes.o oa.h
	cc -g -o oastr oastr.o memory.o oa.o primes.o -lm



allstr: oastr1 oastr2 oastr3 oastr4 oastr
alldes:   bose bush busht bosebush bosebushl addelkemp addelkemp3

all: allstr alldes oarand oatriple oadimen oaagree
	echo "To remove .o files: make cleanup"

b9: bose oarand
	bose 9 | oarand 9 81 10 > b9


cleanup:
	rm -f *.o


lint_bose: galois.h oa.h bose.c construct.c oa.c primes.c gfields.c galois.c memory.c 
	lint bose.c construct.c oa.c primes.c gfields.c galois.c memory.c 

lint_bush: galois.h oa.h bush.c construct.c oa.c primes.c \
	gfields.c galois.c memory.o
	lint bush.c construct.c oa.c primes.c gfields.c galois.c memory.c 

lint_busht: galois.h oa.h busht.c construct.c oa.c primes.c\
	 gfields.c galois.c memory.o
	lint busht.c construct.c oa.c primes.c gfields.c galois.c memory.c 

lint_bosebush: galois.h oa.h bosebush.c construct.c oa.c primes.c\
	 gfields.c galois.c memory.o
	lint bosebush.c construct.c oa.c primes.c gfields.c galois.c memory.c 

lint_bosebushl: galois.h oa.h bosebushl.c construct.c oa.c primes.c\
	gfields.c galois.c memory.o
	lint bosebushl.c construct.c oa.c primes.c gfields.c galois.c memory.c 

lint_addelkemp: galois.h oa.h addelkemp.c construct.c oa.c primes.c\
	 gfields.c galois.c memory.o
	lint addelkemp.c construct.c oa.c primes.c gfields.c galois.c memory.c 

lint_addelkemp3: galois.h oa.h addelkemp3.c ak3.c oa.c primes.c\
	 gfields.c galois.c memory.o
	lint addelkemp3.c construct.c oa.c primes.c gfields.c galois.c memory.c 
 
lint_all_des: lint_bose lint_bush lint_busht lint_bosebush \
	lint_bosebushl lint_addelkemp lint_addelkemp3



lint_str1: galois.h oa.h oastr1.c memory.c oa.c
	lint oastr1.c memory.c oa.c

lint_str2: galois.h oa.h oastr2.c memory.c oa.c
	lint oastr2.c memory.c oa.c

lint_str3: galois.h oa.h oastr3.c memory.c oa.c
	lint oastr3.c memory.c oa.c

lint_str4: galois.h oa.h oastr4.c memory.c oa.c
	lint oastr4.c memory.c oa.c

lint_all_str: lint_str1 lint_str2 lint_str3 lint_str4


