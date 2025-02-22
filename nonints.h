/*	$NetBSD: nonints.h,v 1.239 2022/01/15 19:05:23 rillig Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)nonints.h	8.3 (Berkeley) 3/19/94
 */

/*
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)nonints.h	8.3 (Berkeley) 3/19/94
 */

/* arch.c */
void Arch_Init(void);
void Arch_End(void);

bool Arch_ParseArchive(char **, GNodeList *, GNode *);
void Arch_Touch(GNode *);
void Arch_TouchLib(GNode *);
void Arch_UpdateMTime(GNode *gn);
void Arch_UpdateMemberMTime(GNode *gn);
void Arch_FindLib(GNode *, SearchPath *);
bool Arch_LibOODate(GNode *) MAKE_ATTR_USE;
bool Arch_IsLib(GNode *) MAKE_ATTR_USE;

/* compat.c */
bool Compat_RunCommand(const char *, GNode *, StringListNode *);
void Compat_Run(GNodeList *);
void Compat_Make(GNode *, GNode *);

/* cond.c */
CondResult Cond_EvalCondition(const char *) MAKE_ATTR_USE;
CondResult Cond_EvalLine(const char *) MAKE_ATTR_USE;
void Cond_restore_depth(unsigned int);
unsigned int Cond_save_depth(void) MAKE_ATTR_USE;

/* dir.c; see also dir.h */

MAKE_INLINE const char * MAKE_ATTR_USE
str_basename(const char *pathname)
{
	const char *lastSlash = strrchr(pathname, '/');
	return lastSlash != NULL ? lastSlash + 1 : pathname;
}

MAKE_INLINE SearchPath * MAKE_ATTR_USE
SearchPath_New(void)
{
	SearchPath *path = bmake_malloc(sizeof *path);
	Lst_Init(&path->dirs);
	return path;
}

void SearchPath_Free(SearchPath *);

/* for.c */
struct ForLoop;
int For_Eval(const char *) MAKE_ATTR_USE;
bool For_Accum(const char *, int *) MAKE_ATTR_USE;
void For_Run(int, int);
bool For_NextIteration(struct ForLoop *, Buffer *);
char *ForLoop_Details(struct ForLoop *);
void ForLoop_Free(struct ForLoop *);

/* job.c */
#ifdef WAIT_T
void JobReapChild(pid_t, WAIT_T, bool);
#endif

/* main.c */
bool GetBooleanExpr(const char *, bool);
void Main_ParseArgLine(const char *);
char *Cmd_Exec(const char *, char **) MAKE_ATTR_USE;
void Error(const char *, ...) MAKE_ATTR_PRINTFLIKE(1, 2);
void Fatal(const char *, ...) MAKE_ATTR_PRINTFLIKE(1, 2) MAKE_ATTR_DEAD;
void Punt(const char *, ...) MAKE_ATTR_PRINTFLIKE(1, 2) MAKE_ATTR_DEAD;
void DieHorribly(void) MAKE_ATTR_DEAD;
void Finish(int) MAKE_ATTR_DEAD;
bool unlink_file(const char *) MAKE_ATTR_USE;
void execDie(const char *, const char *);
char *getTmpdir(void) MAKE_ATTR_USE;
bool ParseBoolean(const char *, bool) MAKE_ATTR_USE;
const char *cached_realpath(const char *, char *);

/* parse.c */
void Parse_Init(void);
void Parse_End(void);

void Parse_Error(ParseErrorLevel, const char *, ...) MAKE_ATTR_PRINTFLIKE(2, 3);
bool Parse_VarAssign(const char *, bool, GNode *) MAKE_ATTR_USE;
void Parse_AddIncludeDir(const char *);
void Parse_File(const char *, int);
void Parse_PushInput(const char *, int, int, Buffer, struct ForLoop *);
void Parse_MainName(GNodeList *);
int Parse_NumErrors(void) MAKE_ATTR_USE;


#ifndef HAVE_STRLCPY
/* strlcpy.c */
size_t strlcpy(char *, const char *, size_t);
#endif

/* suff.c */
void Suff_Init(void);
void Suff_End(void);

void Suff_ClearSuffixes(void);
bool Suff_IsTransform(const char *) MAKE_ATTR_USE;
GNode *Suff_AddTransform(const char *);
void Suff_EndTransform(GNode *);
void Suff_AddSuffix(const char *);
SearchPath *Suff_GetPath(const char *) MAKE_ATTR_USE;
void Suff_ExtendPaths(void);
void Suff_AddInclude(const char *);
void Suff_AddLib(const char *);
void Suff_FindDeps(GNode *);
SearchPath *Suff_FindPath(GNode *) MAKE_ATTR_USE;
void Suff_SetNull(const char *);
void Suff_PrintAll(void);
char *Suff_NamesStr(void) MAKE_ATTR_USE;

/* targ.c */
void Targ_Init(void);
void Targ_End(void);

void Targ_Stats(void);
GNodeList *Targ_List(void) MAKE_ATTR_USE;
GNode *GNode_New(const char *) MAKE_ATTR_USE;
GNode *Targ_FindNode(const char *) MAKE_ATTR_USE;
GNode *Targ_GetNode(const char *) MAKE_ATTR_USE;
GNode *Targ_NewInternalNode(const char *) MAKE_ATTR_USE;
GNode *Targ_GetEndNode(void);
void Targ_FindList(GNodeList *, StringList *);
void Targ_PrintCmds(GNode *);
void Targ_PrintNode(GNode *, int);
void Targ_PrintNodes(GNodeList *, int);
const char *Targ_FmtTime(time_t) MAKE_ATTR_USE;
void Targ_PrintType(GNodeType);
void Targ_PrintGraph(int);
void Targ_Propagate(void);
const char *GNodeMade_Name(GNodeMade) MAKE_ATTR_USE;

/* var.c */
void Var_Init(void);
void Var_End(void);

typedef enum VarEvalMode {

	/*
	 * Only parse the expression but don't evaluate any part of it.
	 *
	 * TODO: Document what Var_Parse and Var_Subst return in this mode.
	 *  As of 2021-03-15, they return unspecified, inconsistent results.
	 */
	VARE_PARSE_ONLY,

	/* Parse and evaluate the expression. */
	VARE_WANTRES,

	/*
	 * Parse and evaluate the expression.  It is an error if a
	 * subexpression evaluates to undefined.
	 */
	VARE_UNDEFERR,

	/*
	 * Parse and evaluate the expression.  Keep '$$' as '$$' instead of
	 * reducing it to a single '$'.  Subexpressions that evaluate to
	 * undefined expand to an empty string.
	 *
	 * Used in variable assignments using the ':=' operator.  It allows
	 * multiple such assignments to be chained without accidentally
	 * expanding '$$file' to '$file' in the first assignment and
	 * interpreting it as '${f}' followed by 'ile' in the next assignment.
	 */
	VARE_EVAL_KEEP_DOLLAR,

	/*
	 * Parse and evaluate the expression.  Keep undefined variables as-is
	 * instead of expanding them to an empty string.
	 *
	 * Example for a ':=' assignment:
	 *	CFLAGS = $(.INCLUDES)
	 *	CFLAGS := -I.. $(CFLAGS)
	 *	# If .INCLUDES (an undocumented special variable, by the
	 *	# way) is still undefined, the updated CFLAGS becomes
	 *	# "-I.. $(.INCLUDES)".
	 */
	VARE_EVAL_KEEP_UNDEF,

	/*
	 * Parse and evaluate the expression.  Keep '$$' as '$$' and preserve
	 * undefined subexpressions.
	 */
	VARE_KEEP_DOLLAR_UNDEF
} VarEvalMode;

typedef enum VarSetFlags {
	VAR_SET_NONE		= 0,

	/* do not export */
	VAR_SET_NO_EXPORT	= 1 << 0,

	/*
	 * Make the variable read-only. No further modification is possible,
	 * except for another call to Var_Set with the same flag.
	 */
	VAR_SET_READONLY	= 1 << 1
} VarSetFlags;

/* The state of error handling returned by Var_Parse. */
typedef enum VarParseResult {

	/* Both parsing and evaluation succeeded. */
	VPR_OK,

	/* Parsing or evaluating failed, with an error message. */
	VPR_ERR,

	/*
	 * Parsing succeeded, undefined expressions are allowed and the
	 * expression was still undefined after applying all modifiers.
	 * No error message is printed in this case.
	 *
	 * Some callers handle this case differently, so return this
	 * information to them, for now.
	 *
	 * TODO: Instead of having this special return value, rather ensure
	 *  that VARE_EVAL_KEEP_UNDEF is processed properly.
	 */
	VPR_UNDEF

} VarParseResult;

typedef enum VarExportMode {
	/* .export-env */
	VEM_ENV,
	/* .export: Initial export or update an already exported variable. */
	VEM_PLAIN,
	/* .export-literal: Do not expand the variable value. */
	VEM_LITERAL
} VarExportMode;

void Var_Delete(GNode *, const char *);
void Var_Undef(const char *);
void Var_Set(GNode *, const char *, const char *);
void Var_SetExpand(GNode *, const char *, const char *);
void Var_SetWithFlags(GNode *, const char *, const char *, VarSetFlags);
void Var_SetExpandWithFlags(GNode *, const char *, const char *, VarSetFlags);
void Var_Append(GNode *, const char *, const char *);
void Var_AppendExpand(GNode *, const char *, const char *);
bool Var_Exists(GNode *, const char *) MAKE_ATTR_USE;
bool Var_ExistsExpand(GNode *, const char *) MAKE_ATTR_USE;
FStr Var_Value(GNode *, const char *) MAKE_ATTR_USE;
const char *GNode_ValueDirect(GNode *, const char *) MAKE_ATTR_USE;
VarParseResult Var_Parse(const char **, GNode *, VarEvalMode, FStr *);
VarParseResult Var_Subst(const char *, GNode *, VarEvalMode, char **);
void Var_Expand(FStr *, GNode *, VarEvalMode);
void Var_Stats(void);
void Var_Dump(GNode *);
void Var_ReexportVars(void);
void Var_Export(VarExportMode, const char *);
void Var_ExportVars(const char *);
void Var_UnExport(bool, const char *);

void Global_Set(const char *, const char *);
void Global_Append(const char *, const char *);
void Global_Delete(const char *);

/* util.c */
typedef void (*SignalProc)(int);
SignalProc bmake_signal(int, SignalProc);
