# $NetBSD: opt-file.mk,v 1.7 2020/12/06 20:55:30 rillig Exp $
#
# Tests for the -f command line option.

# TODO: Implementation

all: .PHONY
all: file-ending-in-backslash
all: file-containing-null-byte

# Passing '-' as the filename reads from stdin.  This is unusual but possible.
#
# In the unlikely case where a file ends in a backslash instead of a newline,
# that backslash is trimmed.  See ParseGetLine.
#
# make-2014.01.01.00.00.00 invoked undefined behavior, reading text from
# outside of the file buffer.
#
#	printf '%s' 'VAR=value\' \
#	| MALLOC_OPTIONS=JA make-2014.01.01.00.00.00 -r -f - -V VAR -dA 2>&1 \
#	| less
#
# The debug output shows how make happily uses freshly allocated memory (the
# <A5>) and already freed memory ('Z').
#
#	ParseReadLine (1): 'VAR=value\<A5><A5><A5><A5><A5><A5>'
#	Global:VAR = value\<A5><A5><A5><A5><A5><A5>value\<A5><A5><A5><A5><A5><A5>
#	ParseReadLine (2): 'alue\<A5><A5><A5><A5><A5><A5>'
#	ParseDoDependency(alue\<A5><A5><A5><A5><A5><A5>)
#	make-2014.01.01.00.00.00: "(stdin)" line 2: Need an operator
#	ParseReadLine (3): '<A5><A5><A5>ZZZZZZZZZZZZZZZZ'
#	ParseDoDependency(<A5><A5><A5>ZZZZZZZZZZZZZZZZ)
#
file-ending-in-backslash: .PHONY
	@printf '%s' 'VAR=value\' \
	| ${MAKE} -r -f - -V VAR

# If a file contains null bytes, the rest of the line is skipped, and parsing
# continues in the next line.  Throughout the history of make, the behavior
# has changed several times, sometimes knowingly, sometimes by accident.
#
#	echo 'VAR=value' | tr 'l' '\0' > zero-byte.in
#	printf '%s\n' 'all:' ': VAR=${VAR:Q}' >> zero-byte.in
#
#	for year in $(seq 2003 2020); do
#	  echo $year:
#	  make-$year.01.01.00.00.00 -r -f zero-byte.in
#	  echo "exit status $?"
#	  echo
#	done 2>&1 \
#	| sed "s,$PWD/,.,"
#
# This program generated the following output:
#
#	2003 to 2007:
#	exit status 0
#
#	2008 to 2010:
#	make: "zero-byte.in" line 1: Zero byte read from file
#	make: Fatal errors encountered -- cannot continue
#
#	make: stopped in .
#	exit status 1
#
#	2011 to 2013:
#	make: no target to make.
#
#	make: stopped in .
#	exit status 2
#
#	2014 to 2020-12-06:
#	make: "zero-byte.in" line 1: warning: Zero byte read from file, skipping rest of line.
#	exit status 0
#
#	Since 2020-12-07:
#	make: "zero-byte.in" line 1: Zero byte read from file
#	make: Fatal errors encountered -- cannot continue
#	make: stopped in .
#	exit status 1
file-containing-null-byte: .PHONY
	@printf '%s\n' 'VAR=value' 'VAR2=VALUE2' \
	| tr 'l' '\0' \
	| ${MAKE} -r -f - -V VAR -V VAR2

all:
	: Making ${.TARGET}
