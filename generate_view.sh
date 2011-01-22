#!/bin/zsh -f

(   (echo "Beginning of View Buffer")                                                                                                                           &&
    (echo "")                                                                                                                                                   &&
    (echo "")                                                                                                                                                   &&
    (echo "")                                                                                                                                                   &&
    (echo "  Project Statistics")                                                                                                                               &&
    (echo "")                                                                                                                                                   &&
    (echo -n "    Lines of Funk2 Code.....: "; (wc --lines */*.fu2 */*/*.fu2 */*/*.fpkg                                                             | tail -1)) &&
    (echo -n "    Words of Funk2 Code.....: "; (wc --words */*.fu2 */*/*.fu2 */*/*.fpkg                                                             | tail -1)) &&
    (echo -n "    Characters of Funk2 Code: "; (wc --chars */*.fu2 */*/*.fu2 */*/*.fpkg                                                             | tail -1)) &&
    (echo "")                                                                                                                                                   &&
    (echo -n "    Lines of C Code.........: "; (wc --lines */*.[ch] */*/*.[ch]                                                                      | tail -1)) &&
    (echo -n "    Words of C Code.........: "; (wc --words */*.[ch] */*/*.[ch]                                                                      | tail -1)) &&
    (echo -n "    Characters of C Code....: "; (wc --chars */*.[ch] */*/*.[ch]                                                                      | tail -1)) &&
    (echo "")                                                                                                                                                   &&
    (echo -n "    Total Lines of Code.....: "; (wc --lines view.sh README Makefile.am funk-mode.el */*.[ch] */*.fu2 */*/*.[ch] */*/*.fu2 */*/*.fpkg | tail -1)) &&
    (echo -n "    Total Words of Code.....: "; (wc --words view.sh README Makefile.am funk-mode.el */*.[ch] */*.fu2 */*/*.[ch] */*/*.fu2 */*/*.fpkg | tail -1)) &&
    (echo -n "    Total Characters of Code: "; (wc --chars view.sh README Makefile.am funk-mode.el */*.[ch] */*.fu2 */*/*.[ch] */*/*.fu2 */*/*.fpkg | tail -1)) &&
    (echo "")                                                                                                                                                   &&
    (echo "")                                                                                                                                                   &&
    (echo "  Funk2 Code Files")                                                                                                                                 &&
    (echo "")                                                                                                                                                   &&
    (wc                                                  */*.fu2 */*/*.fu2 */*/*.fpkg                                                             | head -n -1) &&
    (echo "")                                                                                                                                                   &&
    (echo "")                                                                                                                                                   &&
    (echo "  C Code Files")                                                                                                                                     &&
    (echo "")                                                                                                                                                   &&
    (wc                                                  */*.[ch] */*/*.[ch]                                                                      | head -n -1) &&
    (echo "")                                                                                                                                                   &&
    (echo "")                                                                                                                                                   &&
    (echo "  Other Text Files")                                                                                                                                 &&
    (echo "")                                                                                                                                                   &&
    (wc                                                  view.sh README Makefile.am funk-mode.el                                                  | head -n -1) &&
    (echo "")                                                                                                                                                   &&
    (echo "")                                                                                                                                                   &&
    (echo "End of View Buffer")                                                                                                                                    )

