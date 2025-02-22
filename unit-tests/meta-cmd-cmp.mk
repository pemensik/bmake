# $NetBSD: meta-cmd-cmp.mk,v 1.3 2022/01/14 19:31:44 sjg Exp $
#
# Tests META_MODE command line comparison
#

.MAIN: all

.MAKE.MODE= meta verbose silent=yes curdirok=yes
tf:= .${.PARSEFILE:R}

.if ${.TARGETS:Nall} == ""
all: prep one two change1 change2 filter0 filter1 filter2 post

CLEANFILES= ${tf}*

prep post: .PHONY
	@rm -f ${CLEANFILES}

.endif

FLAGS?=
FLAGS2?=

tests= ${tf}.cmp ${tf}.nocmp ${tf}.cmp2
filter_tests= ${tf}.filter

${tf}.cmp:
	@echo FLAGS=${FLAGS:Uempty} > $@

${tf}.nocmp: .NOMETA_CMP
	@echo FLAGS=${FLAGS:Uempty} > $@

# a line containing ${.OODATE} will not be compared
# this allows the trick below
${tf}.cmp2:
	@echo FLAGS2=${FLAGS2:Uempty} > $@
	@echo This line not compared FLAGS=${FLAGS:Uempty} ${.OODATE:MNOMETA_CMP}

CCACHE= ccache
.ifdef WITH_CMP_FILTER
.MAKE.META.CMP_FILTER += Nccache Ndistcc
.endif

${tf}.filter:
	@echo ${CCACHE} cc -c foo.c > $@

# these do the same 
one two: .PHONY
	@echo $@:
	@${.MAKE} -dM -r -C ${.CURDIR} -f ${MAKEFILE} ${tests}

change1: .PHONY
	@echo $@:
	@${.MAKE} -dM -r -C ${.CURDIR} -f ${MAKEFILE} FLAGS=changed ${tests}

change2: .PHONY
	@echo $@:
	@${.MAKE} -dM -r -C ${.CURDIR} -f ${MAKEFILE} FLAGS2=changed ${tests}

filter0: .PHONY
	@echo $@:
	@${.MAKE} -dM -r -C ${.CURDIR} -f ${MAKEFILE} ${filter_tests}

filter1: .PHONY
	@echo $@:
	@${.MAKE} -dM -r -C ${.CURDIR} -f ${MAKEFILE} CCACHE= ${filter_tests}

filter2: .PHONY
	@echo $@:
	@${.MAKE} -dM -r -C ${.CURDIR} -f ${MAKEFILE} -DWITH_CMP_FILTER \
		CCACHE=distcc ${filter_tests}

# don't let gcov mess up the results
.MAKE.META.IGNORE_PATTERNS+= *.gcda
