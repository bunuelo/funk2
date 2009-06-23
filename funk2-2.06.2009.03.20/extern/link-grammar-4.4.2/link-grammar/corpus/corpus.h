/*
 * corpus.h
 *
 * Data for corpus statistics, used to provide a parse ranking
 * to drive the SAT solver, as well as parse ranking with the
 * ordinary solver. 
 */

#ifndef _LINKGRAMMAR_CORPUS_H
#define _LINKGRAMMAR_CORPUS_H

#ifdef USE_CORPUS

#include <sqlite3.h>
#include "../api-types.h"
#include "../link-includes.h"

struct corpus_s
{
	char * dbname;
	sqlite3 *dbconn;
	sqlite3_stmt *rank_query;
	sqlite3_stmt *sense_query;
	char *errmsg;
};

typedef struct corpus_s Corpus;

Corpus * lg_corpus_new(void);
void lg_corpus_delete(Corpus *);
void lg_corpus_disjuncts(Corpus *, Sentence, Linkage_info *);
void lg_corpus_score(Corpus *, Sentence, Linkage_info *);
void lg_corpus_senses(Corpus *, const char *, const char *);


#endif /* USE_CORPUS */

#endif /* _LINKGRAMMAR_CORPUS_H */
