/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

// Heavily inspired by hoc
// Copyright (C) AT&T 1995
// All Rights Reserved
//
// Permission to use, copy, modify, and distribute this software and
// its documentation for any purpose and without fee is hereby
// granted, provided that the above copyright notice appear in all
// copies and that both that the copyright notice and this
// permission notice and warranty disclaimer appear in supporting
// documentation, and that the name of AT&T or any of its entities
// not be used in advertising or publicity pertaining to
// distribution of the software without specific, written prior
// permission.
//
// AT&T DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
// INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
// IN NO EVENT SHALL AT&T OR ANY OF ITS ENTITIES BE LIABLE FOR ANY
// SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
// IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
// ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
// THIS SOFTWARE.


%debug

// %glr-parser
// %defines "engines/director/lingo/lingo-gr.h"

%{
#define FORBIDDEN_SYMBOL_ALLOW_ALL

#include "common/endian.h"
#include "common/hash-str.h"
#include "common/rect.h"

#include "director/lingo/lingo.h"
#include "director/lingo/lingo-gr.h"

extern int yylex();
extern int yyparse();

using namespace Director;
void yyerror(const char *s) {
	g_lingo->_hadError = true;
	warning("######################  LINGO: %s at line %d col %d", s, g_lingo->_linenumber, g_lingo->_colnumber);
}

void checkEnd(Common::String *token, const char *expect, bool required) {
	if (required) {
		if (token->compareToIgnoreCase(expect)) {
			Common::String err = Common::String::format("end mismatch. Expected %s but got %s", expect, token->c_str());
			yyerror(err.c_str());
		}
	}

	delete token;
}

%}

%union {
	Common::String *s;
	int i;
	double f;
	int e[2];	// Entity + field
	int code;
	int narg;	/* number of arguments */
	Common::Array<double> *arr;
}

%token UNARY
%token CASTREF VOID VAR POINT RECT ARRAY OBJECT REFERENCE
%token<i> INT ARGC ARGCNORET
%token<e> THEENTITY THEENTITYWITHID
%token<f> FLOAT
%token<s> BLTIN BLTINNOARGS BLTINNOARGSORONE BLTINONEARG BLTINARGLIST TWOWORDBUILTIN
%token<s> FBLTIN FBLTINNOARGS FBLTINONEARG FBLTINARGLIST RBLTIN RBLTINONEARG
%token<s> ID STRING HANDLER SYMBOL
%token<s> ENDCLAUSE tPLAYACCEL tMETHOD
%token tDOWN tELSE tELSIF tEXIT tGLOBAL tGO tIF tINTO tLOOP tMACRO
%token tMOVIE tNEXT tOF tPREVIOUS tPUT tREPEAT tSET tTHEN tTO tWHEN
%token tWITH tWHILE tNLELSE tFACTORY tOPEN tPLAY tDONE tINSTANCE
%token tGE tLE tEQ tNEQ tAND tOR tNOT tMOD
%token tAFTER tBEFORE tCONCAT tCONTAINS tSTARTS tCHAR tITEM tLINE tWORD
%token tSPRITE tINTERSECTS tWITHIN tTELL tPROPERTY
%token tON tME tENDIF tENDREPEAT tENDTELL

%type<code> asgn begin elseif end expr if when repeatwhile
%type<code> repeatwith stmtlist tell reference simpleexpr
%type<narg> argdef arglist nonemptyarglist
%type<s> on

%left tAND tOR
%left '<' tLE '>' tGE tEQ tNEQ tCONTAINS tSTARTS
%left '&' tCONCAT
%left '+' '-'
%left '*' '/' '%' tMOD
%right UNARY

%%

program: program '\n' programline
	| programline
	| error	'\n'		{ yyerrok; }
	;

programline: /* empty */
	| defn
	| stmt
	;

asgn: tPUT expr tINTO ID 		{
		g_lingo->code1(g_lingo->c_varpush);
		g_lingo->codeString($4->c_str());
		g_lingo->code1(g_lingo->c_assign);
		$$ = $2;
		delete $4; }
	| tPUT expr tINTO reference 		{
			g_lingo->code1(g_lingo->c_assign);
			$$ = $2; }
	| tPUT expr tAFTER expr 		{ $$ = g_lingo->code1(g_lingo->c_after); }		// D3
	| tPUT expr tBEFORE expr 		{ $$ = g_lingo->code1(g_lingo->c_before); }		// D3
	| tSET ID tEQ expr			{
		g_lingo->code1(g_lingo->c_varpush);
		g_lingo->codeString($2->c_str());
		g_lingo->code1(g_lingo->c_assign);
		$$ = $4;
		delete $2; }
	| tSET THEENTITY tEQ expr	{
		g_lingo->code1(g_lingo->c_intpush);
		g_lingo->codeInt(0); // Put dummy id
		g_lingo->code1(g_lingo->c_theentityassign);
		g_lingo->codeInt($2[0]);
		g_lingo->codeInt($2[1]);
		$$ = $4; }
	| tSET ID tTO expr			{
		g_lingo->code1(g_lingo->c_varpush);
		g_lingo->codeString($2->c_str());
		g_lingo->code1(g_lingo->c_assign);
		$$ = $4;
		delete $2; }
	| tSET THEENTITY tTO expr	{
		g_lingo->code1(g_lingo->c_intpush);
		g_lingo->codeInt(0); // Put dummy id
		g_lingo->code1(g_lingo->c_theentityassign);
		g_lingo->codeInt($2[0]);
		g_lingo->codeInt($2[1]);
		$$ = $4; }
	| tSET THEENTITYWITHID expr tTO expr	{
		g_lingo->code1(g_lingo->c_swap);
		g_lingo->code1(g_lingo->c_theentityassign);
		g_lingo->codeInt($2[0]);
		g_lingo->codeInt($2[1]);
		$$ = $5; }
	| tSET THEENTITYWITHID simpleexpr tEQ expr	{
		g_lingo->code1(g_lingo->c_swap);
		g_lingo->code1(g_lingo->c_theentityassign);
		g_lingo->codeInt($2[0]);
		g_lingo->codeInt($2[1]);
		$$ = $5; }
	;

stmtoneliner: macro
	| expr
	| proc
	| ifoneliner
	;

stmt: stmtoneliner
	| ifstmt
	// repeat while (expression = TRUE)
	//   statements
	// end repeat
	//
	| repeatwhile expr end stmtlist end tENDREPEAT	{
		inst body = 0, end = 0;
		WRITE_UINT32(&body, $3 - $1);
		WRITE_UINT32(&end, $5 - $1);
		(*g_lingo->_currentScript)[$1 + 1] = body;	/* body of loop */
		(*g_lingo->_currentScript)[$1 + 2] = end; }	/* end, if cond fails */
	;
	// repeat with index = start to end
	//   statements
	// end repeat
	//
	| repeatwith tEQ expr end tTO expr end stmtlist end tENDREPEAT {
		inst init = 0, finish = 0, body = 0, end = 0, inc = 0;
		WRITE_UINT32(&init, $3 - $1);
		WRITE_UINT32(&finish, $6 - $1);
		WRITE_UINT32(&body, $8 - $1);
		WRITE_UINT32(&end, $9 - $1);
		WRITE_UINT32(&inc, 1);
		(*g_lingo->_currentScript)[$1 + 1] = init;	/* initial count value */
		(*g_lingo->_currentScript)[$1 + 2] = finish;/* final count value */
		(*g_lingo->_currentScript)[$1 + 3] = body;	/* body of loop */
		(*g_lingo->_currentScript)[$1 + 4] = inc;	/* increment */
		(*g_lingo->_currentScript)[$1 + 5] = end; }	/* end, if cond fails */

	// repeat with index = high down to low
	//   statements
	// end repeat
	//
	| repeatwith tEQ expr end tDOWN tTO expr end stmtlist end tENDREPEAT {
		inst init = 0, finish = 0, body = 0, end = 0, inc = 0;
		WRITE_UINT32(&init, $3 - $1);
		WRITE_UINT32(&finish, $7 - $1);
		WRITE_UINT32(&body, $9 - $1);
		WRITE_UINT32(&end, $10 - $1);
		WRITE_UINT32(&inc, (uint32)-1);
		(*g_lingo->_currentScript)[$1 + 1] = init;	/* initial count value */
		(*g_lingo->_currentScript)[$1 + 2] = finish;/* final count value */
		(*g_lingo->_currentScript)[$1 + 3] = body;	/* body of loop */
		(*g_lingo->_currentScript)[$1 + 4] = inc;	/* increment */
		(*g_lingo->_currentScript)[$1 + 5] = end; }	/* end, if cond fails */
	| when stmtoneliner end {
		inst end = 0;
		WRITE_UINT32(&end, $3 - $1);
		g_lingo->code1(STOP);
		(*g_lingo->_currentScript)[$1 + 1] = end; }
	| tell expr '\n' stmtlist end tENDTELL {
			warning("STUB: TELL is not implemented"); }
	| tell expr tTO expr {
			warning("STUB: TELL is not implemented");
		}
	;

ifstmt: if expr end tTHEN stmtlist end elseifstmtlist end tENDIF {
		inst then = 0, else1 = 0, end = 0;
		WRITE_UINT32(&then, $3 - $1);
		WRITE_UINT32(&else1, $6 - $1);
		WRITE_UINT32(&end, $8 - $1);
		(*g_lingo->_currentScript)[$1 + 1] = then;	/* thenpart */
		(*g_lingo->_currentScript)[$1 + 2] = else1;	/* elsepart */
		(*g_lingo->_currentScript)[$1 + 3] = end;	/* end, if cond fails */

		g_lingo->processIf($1, $8 - $1, 0); }
	| if expr end tTHEN stmtlist end elseifstmtlist tELSE begin stmtlist end tENDIF {
		inst then = 0, else1 = 0, end = 0;
		WRITE_UINT32(&then, $3 - $1);
		WRITE_UINT32(&else1, $6 - $1);
		WRITE_UINT32(&end, $11 - $1);
		(*g_lingo->_currentScript)[$1 + 1] = then;	/* thenpart */
		(*g_lingo->_currentScript)[$1 + 2] = else1;	/* elsepart */
		(*g_lingo->_currentScript)[$1 + 3] = end;	/* end, if cond fails */

		g_lingo->processIf($1, $11 - $1, $9 - $1); }
	;

elseifstmtlist:	/* nothing */
	| elseifstmt elseifstmtlist
	;

elseifstmt: elseif expr end tTHEN stmtlist end {
		inst then = 0;
		WRITE_UINT32(&then, $3 - $1);
		(*g_lingo->_currentScript)[$1 + 1] = then;	/* thenpart */

		g_lingo->codeLabel($1); }
	;

ifoneliner: if expr end tTHEN stmtoneliner end tELSE begin stmtoneliner end tENDIF {
		inst then = 0, else1 = 0, end = 0;
		WRITE_UINT32(&then, $3 - $1);
		WRITE_UINT32(&else1, $6 - $1);
		WRITE_UINT32(&end, $10 - $1);
		(*g_lingo->_currentScript)[$1 + 1] = then;	/* thenpart */
		(*g_lingo->_currentScript)[$1 + 2] = else1;	/* elsepart */
		(*g_lingo->_currentScript)[$1 + 3] = end;	/* end, if cond fails */

		g_lingo->processIf($1, $10 - $1, $8 - $1); }
	| if expr end tTHEN stmtoneliner end tENDIF {
			inst then = 0, else1 = 0, end = 0;
			WRITE_UINT32(&then, $3 - $1);
			WRITE_UINT32(&else1, 0);
			WRITE_UINT32(&end, $6 - $1);
			(*g_lingo->_currentScript)[$1 + 1] = then;	/* thenpart */
			(*g_lingo->_currentScript)[$1 + 2] = else1;	/* elsepart */
			(*g_lingo->_currentScript)[$1 + 3] = end;	/* end, if cond fails */

			g_lingo->processIf($1, $6 - $1, $6 - $1); }
	;


repeatwhile:	tREPEAT tWHILE		{ $$ = g_lingo->code3(g_lingo->c_repeatwhilecode, STOP, STOP); }
	;

repeatwith:		tREPEAT tWITH ID	{
		$$ = g_lingo->code3(g_lingo->c_repeatwithcode, STOP, STOP);
		g_lingo->code3(STOP, STOP, STOP);
		g_lingo->codeString($3->c_str());
		delete $3; }
	;

if:	  tIF					{
		$$ = g_lingo->code1(g_lingo->c_ifcode);
		g_lingo->code3(STOP, STOP, STOP);
		g_lingo->code1(0);  // Do not skip end
		g_lingo->codeLabel(0); } // Mark beginning of the if() statement
	;

elseif:	  tELSIF			{
		inst skipEnd;
		WRITE_UINT32(&skipEnd, 1); // We have to skip end to avoid multiple executions
		$$ = g_lingo->code1(g_lingo->c_ifcode);
		g_lingo->code3(STOP, STOP, STOP);
		g_lingo->code1(skipEnd); }
	;

begin:	  /* nothing */		{ $$ = g_lingo->_currentScript->size(); }
	;

end:	  /* nothing */		{ g_lingo->code1(STOP); $$ = g_lingo->_currentScript->size(); }
	;

stmtlist: 					{ $$ = g_lingo->_currentScript->size(); }
	| stmtlist '\n'
	| stmtlist stmt
	;

when:	  tWHEN	ID tTHEN	{
		$$ = g_lingo->code1(g_lingo->c_whencode);
		g_lingo->code1(STOP);
		g_lingo->codeString($2->c_str());
		delete $2; }

tell:	  tTELL				{
		$$ = g_lingo->code1(g_lingo->c_tellcode);
		g_lingo->code1(STOP); }

simpleexpr: INT		{
		$$ = g_lingo->code1(g_lingo->c_intpush);
		g_lingo->codeInt($1); }
	| FLOAT		{
		$$ = g_lingo->code1(g_lingo->c_floatpush);
		g_lingo->codeFloat($1); }
	| SYMBOL	{											// D3
		$$ = g_lingo->code1(g_lingo->c_symbolpush);
		g_lingo->codeString($1->c_str()); }
	| STRING		{
		$$ = g_lingo->code1(g_lingo->c_stringpush);
		g_lingo->codeString($1->c_str()); }
	| ID		{
		$$ = g_lingo->code1(g_lingo->c_eval);
		g_lingo->codeString($1->c_str());
		delete $1; }
	;

expr: simpleexpr { $$ = $1; }
	| reference
	| FBLTINNOARGS 	{
		g_lingo->codeFunc($1, 0);
		delete $1; }
	| FBLTINONEARG expr		{
		g_lingo->codeFunc($1, 1);
		delete $1; }
	| FBLTINARGLIST nonemptyarglist			{ g_lingo->codeFunc($1, $2); }
	| ID '(' arglist ')'	{
		$$ = g_lingo->codeFunc($1, $3);
		delete $1; }
	| THEENTITY	{
		$$ = g_lingo->code1(g_lingo->c_intpush);
		g_lingo->codeInt(0); // Put dummy id
		g_lingo->code1(g_lingo->c_theentitypush);
		inst e = 0, f = 0;
		WRITE_UINT32(&e, $1[0]);
		WRITE_UINT32(&f, $1[1]);
		g_lingo->code2(e, f); }
	| THEENTITYWITHID expr	{
		$$ = g_lingo->code1(g_lingo->c_theentitypush);
		inst e = 0, f = 0;
		WRITE_UINT32(&e, $1[0]);
		WRITE_UINT32(&f, $1[1]);
		g_lingo->code2(e, f); }
	| asgn
	| expr '+' expr				{ g_lingo->code1(g_lingo->c_add); }
	| expr '-' expr				{ g_lingo->code1(g_lingo->c_sub); }
	| expr '*' expr				{ g_lingo->code1(g_lingo->c_mul); }
	| expr '/' expr				{ g_lingo->code1(g_lingo->c_div); }
	| expr tMOD expr			{ g_lingo->code1(g_lingo->c_mod); }
	| expr '>' expr				{ g_lingo->code1(g_lingo->c_gt); }
	| expr '<' expr				{ g_lingo->code1(g_lingo->c_lt); }
	| expr tEQ expr				{ g_lingo->code1(g_lingo->c_eq); }
	| expr tNEQ expr			{ g_lingo->code1(g_lingo->c_neq); }
	| expr tGE expr				{ g_lingo->code1(g_lingo->c_ge); }
	| expr tLE expr				{ g_lingo->code1(g_lingo->c_le); }
	| expr tAND expr			{ g_lingo->code1(g_lingo->c_and); }
	| expr tOR expr				{ g_lingo->code1(g_lingo->c_or); }
	| tNOT expr  %prec UNARY	{ g_lingo->code1(g_lingo->c_not); }
	| expr '&' expr				{ g_lingo->code1(g_lingo->c_ampersand); }
	| expr tCONCAT expr			{ g_lingo->code1(g_lingo->c_concat); }
	| expr tCONTAINS expr		{ g_lingo->code1(g_lingo->c_contains); }
	| expr tSTARTS expr			{ g_lingo->code1(g_lingo->c_starts); }
	| '+' expr  %prec UNARY		{ $$ = $2; }
	| '-' expr  %prec UNARY		{ $$ = $2; g_lingo->code1(g_lingo->c_negate); }
	| '(' expr ')'				{ $$ = $2; }
	| '[' arglist ']'			{ $$ = g_lingo->code1(g_lingo->c_arraypush); g_lingo->codeArray($2); }
	| tSPRITE expr tINTERSECTS expr 	{ g_lingo->code1(g_lingo->c_intersects); }
	| tSPRITE expr tWITHIN expr		 	{ g_lingo->code1(g_lingo->c_within); }
	| tCHAR expr tOF expr				{ g_lingo->code1(g_lingo->c_charOf); }
	| tCHAR expr tTO expr tOF expr		{ g_lingo->code1(g_lingo->c_charToOf); }
	| tITEM expr tOF expr				{ g_lingo->code1(g_lingo->c_itemOf); }
	| tITEM expr tTO expr tOF expr		{ g_lingo->code1(g_lingo->c_itemToOf); }
	| tLINE expr tOF expr				{ g_lingo->code1(g_lingo->c_lineOf); }
	| tLINE expr tTO expr tOF expr		{ g_lingo->code1(g_lingo->c_lineToOf); }
	| tWORD expr tOF expr				{ g_lingo->code1(g_lingo->c_wordOf); }
	| tWORD expr tTO expr tOF expr		{ g_lingo->code1(g_lingo->c_wordToOf); }
	| tME '(' ID ')'					{ g_lingo->codeMe($3, 0); }
	| tME '(' ID ',' arglist ')'		{ g_lingo->codeMe($3, $5); }
	| tME								{ g_lingo->codeMe(nullptr, 0); }
	;

reference: 	RBLTINONEARG simpleexpr	{
		g_lingo->codeFunc($1, 1);
		delete $1; }
	;

proc: tPUT expr				{ g_lingo->code1(g_lingo->c_printtop); }
	| gotofunc
	| playfunc
	| tEXIT tREPEAT			{ g_lingo->code1(g_lingo->c_exitRepeat); }
	| tEXIT					{ g_lingo->code1(g_lingo->c_procret); }
	| tGLOBAL globallist
	| tPROPERTY propertylist
	| tINSTANCE instancelist
	| BLTINNOARGS 	{
		g_lingo->codeFunc($1, 0);
		delete $1; }
	| BLTINONEARG expr		{
		g_lingo->codeFunc($1, 1);
		delete $1; }
	| BLTINNOARGSORONE expr	{
		g_lingo->codeFunc($1, 1);
		delete $1; }
	| BLTINNOARGSORONE 		{
		g_lingo->code1(g_lingo->c_voidpush);
		g_lingo->codeFunc($1, 1);
		delete $1; }
	| BLTINARGLIST nonemptyarglist			{ g_lingo->codeFunc($1, $2); }
	| tOPEN expr tWITH expr	{ g_lingo->code1(g_lingo->c_open); }
	| tOPEN expr 			{ g_lingo->code2(g_lingo->c_voidpush, g_lingo->c_open); }
	| TWOWORDBUILTIN ID arglist	{ Common::String s(*$1); s += '-'; s += *$2; g_lingo->codeFunc(&s, $3); }
	;

globallist: ID					{ g_lingo->code1(g_lingo->c_global); g_lingo->codeString($1->c_str()); delete $1; }
	| globallist ',' ID			{ g_lingo->code1(g_lingo->c_global); g_lingo->codeString($3->c_str()); delete $3; }
	;

propertylist: ID				{ g_lingo->code1(g_lingo->c_property); g_lingo->codeString($1->c_str()); delete $1; }
	| propertylist ',' ID		{ g_lingo->code1(g_lingo->c_property); g_lingo->codeString($3->c_str()); delete $3; }
	;

instancelist: ID				{ g_lingo->code1(g_lingo->c_instance); g_lingo->codeString($1->c_str()); delete $1; }
	| instancelist ',' ID		{ g_lingo->code1(g_lingo->c_instance); g_lingo->codeString($3->c_str()); delete $3; }
	;

// go {to} {frame} whichFrame {of movie whichMovie}
// go {to} {frame "Open23" of} movie whichMovie
// go loop
// go next
// go previous
// go to {frame} whichFrame {of movie whichMovie}
// go to {frame whichFrame of} movie whichMovie

gotofunc: tGO tLOOP				{ g_lingo->code1(g_lingo->c_gotoloop); }
	| tGO tNEXT					{ g_lingo->code1(g_lingo->c_gotonext); }
	| tGO tPREVIOUS				{ g_lingo->code1(g_lingo->c_gotoprevious); }
	| tGO expr 			{
		g_lingo->code1(g_lingo->c_intpush);
		g_lingo->codeInt(1);
		g_lingo->code1(g_lingo->c_goto); }
	| tGO expr gotomovie	{
		g_lingo->code1(g_lingo->c_intpush);
		g_lingo->codeInt(3);
		g_lingo->code1(g_lingo->c_goto); }
	| tGO gotomovie				{
		g_lingo->code1(g_lingo->c_intpush);
		g_lingo->codeInt(2);
		g_lingo->code1(g_lingo->c_goto); }
	;

gotomovie: tOF tMOVIE expr
	| tMOVIE expr
	;

playfunc: tPLAY tDONE			{ g_lingo->code1(g_lingo->c_playdone); }
	| tPLAY expr 			{
		g_lingo->code1(g_lingo->c_intpush);
		g_lingo->codeInt(1);
		g_lingo->code1(g_lingo->c_play); }
	| tPLAY expr gotomovie	{
		g_lingo->code1(g_lingo->c_intpush);
		g_lingo->codeInt(3);
		g_lingo->code1(g_lingo->c_play); }
	| tPLAY gotomovie				{
		g_lingo->code1(g_lingo->c_intpush);
		g_lingo->codeInt(2);
		g_lingo->code1(g_lingo->c_play); }
	| tPLAYACCEL { g_lingo->codeSetImmediate(true); } arglist	{
		g_lingo->codeSetImmediate(false);
		g_lingo->codeFunc($1, $3); }
	;

// macro
//
// Special Note  The macro keyword is retained in Director 3.0 to maintain compatibility
// with scripts developed under Version 2.0. When writing new scripts, or editing old
// scripts, you should use handlers instead of macros. (Handlers are defined with the on keyword.)
//
// Syntax:
//
// --  [comment]
// macro macroName [argument1] [, argument2]
// [, argument3]
// [statement1]
// [statement2]
//
// Keyword.  Defines a macro. A macro is a multiple-line script defined
// in the Text window. Macros can accept arguments (inputs) and
// optionally return a result. Macros can call other macros and can be
// called from any other script or factory.
//
// The first line of a castmember in the Text window that contains a macro must be
// a comment (--). You can define more than one macro in a given text castmember.
// The macro definition ends where the next macro (or factory) begins.
//
// See also:
//   on keyword
defn: tMACRO ID { g_lingo->_indef = kStateInArgs; g_lingo->_currentFactory.clear(); }
		begin argdef '\n' argstore stmtlist 		{
			g_lingo->code1(g_lingo->c_procret);
			g_lingo->define(*$2, $4, $5);
			g_lingo->clearArgStack();
			g_lingo->_indef = kStateNone; }
	| tFACTORY ID	{ g_lingo->codeFactory(*$2); }
	| tMETHOD { g_lingo->_indef = kStateInArgs; }
		begin argdef '\n' argstore stmtlist 		{
			g_lingo->code1(g_lingo->c_procret);
			g_lingo->define(*$1, $3, $4 + 1, &g_lingo->_currentFactory);
			g_lingo->clearArgStack();
			g_lingo->_indef = kStateNone; }
	| on begin argdef '\n' argstore stmtlist ENDCLAUSE endargdef {	// D3
		g_lingo->code1(g_lingo->c_procret);
		g_lingo->define(*$1, $2, $3);
		g_lingo->clearArgStack();
		g_lingo->_indef = kStateNone;
		g_lingo->_ignoreMe = false;

		checkEnd($7, $1->c_str(), false); }
	| on begin argdef '\n' argstore stmtlist {	// D4. No 'end' clause
		g_lingo->code1(g_lingo->c_procret);
		g_lingo->define(*$1, $2, $3);
		g_lingo->_indef = kStateNone;
		g_lingo->clearArgStack();
		g_lingo->_ignoreMe = false; }

on:  tON ID { $$ = $2; g_lingo->_indef = kStateInArgs; g_lingo->_currentFactory.clear(); g_lingo->_ignoreMe = true; }

argdef:  /* nothing */ 		{ $$ = 0; }
	| ID					{ g_lingo->codeArg($1); $$ = 1; }
	| argdef ',' ID			{ g_lingo->codeArg($3); $$ = $1 + 1; }
	| argdef '\n' ',' ID	{ g_lingo->codeArg($4); $$ = $1 + 1; }
	;

endargdef:	/* nothing */
	| ID
	| endargdef ',' ID
	;

argstore:	  /* nothing */		{ g_lingo->codeArgStore(); g_lingo->_indef = kStateInDef; }
	;

macro: ID nonemptyarglist	{
		g_lingo->code1(g_lingo->c_call);
		g_lingo->codeString($1->c_str());
		inst numpar = 0;
		WRITE_UINT32(&numpar, $2);
		g_lingo->code1(numpar); }
	;

arglist:  /* nothing */ 	{ $$ = 0; }
	| expr					{ $$ = 1; }
	| arglist ',' expr		{ $$ = $1 + 1; }
	;

nonemptyarglist:  expr			{ $$ = 1; }
	| nonemptyarglist ',' expr	{ $$ = $1 + 1; }
	;

%%
