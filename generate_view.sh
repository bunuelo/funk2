#!/bin/zsh -f

(   (echo "Beginning of View Buffer")                                                                                                                           &&
    (echo "")                                                                                                                                                   &&
    (echo "")                                                                                                                                                   &&
    (echo "")                                                                                                                                                   &&
    (echo "  Project Statistics")                                                                                                                               &&
    (echo "")                                                                                                                                                   &&
    (./generate_statistics.sh)                                                                                                                                  &&
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

