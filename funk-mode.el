;; 
;; Copyright (c) 2007-2012 Bo Morgan.
;; All rights reserved.
;; 
;; Author: Bo Morgan
;; 
;; Permission to use, copy, modify and distribute this software and its
;; documentation is hereby granted, provided that both the copyright
;; notice and this permission notice appear in all copies of the
;; software, derivative works or modified versions, and any portions
;; thereof, and that both notices appear in supporting documentation.
;; 
;; BO MORGAN ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION.
;; BO MORGAN DISCLAIMS ANY LIABILITY OF ANY KIND FOR ANY DAMAGES
;; WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
;; 
;; Bo Morgan requests users of this software to return to bo@mit.edu any
;; improvements or extensions that they make and grant Bo Morgan the
;; rights to redistribute these changes.
;; 

;; custom hooks 
(defvar funk-mode-hook nil)

;(defun indent-this-list ()
;  "Indents the current list."
;  (interactive)
;  (save-excursion
;    (backward-up-list)
;    (lisp-indent-line)))

;; default mode map
(defvar funk-mode-map  
  (let ((funk-mode-map (make-keymap)))
    (define-key funk-mode-map "\t" 'lisp-indent-line)
    funk-mode-map)
  "Keymap for Funk major mode")

(add-to-list 'auto-mode-alist '("\\.funk" . funk-mode))
(add-to-list 'auto-mode-alist '("\\.fu"   . funk-mode))
(add-to-list 'auto-mode-alist '("\\.fu2"  . funk-mode))
(add-to-list 'auto-mode-alist '("\\.fpkg" . funk-mode))

(add-to-list 'interpreter-mode-alist '("funk" . funk-mode))


;; The following piece of code generates the type list below.
;;
;; [mapc [funk [x]
;;         [if [> 16 [get [get x as-string] length]]
;;             [format stdout '  "' x '"\n']]]
;;       [have [system-type_names] sort [funk [x y] [> [get x as-string] [get y as-string]]]]]


;; only defined one keyword list right now 
(defconst funk-font-lock-keywords-3
  (list
   '("\\('[a-zA-Z0-9\n\t\\ _-~!@#$%^&*/()_+-={}]+'\\)" . font-lock-string-face)
   '("\\(&\\)\\([a-zA-Z0-9]+\\)" . font-lock-function-name-face)
   ;;'("\\(:\\)\\([a-zA-Z0-9]+\\)" . font-lock-type-face)
   '("\\(`\\)\\([a-zA-Z0-9]+\\)" . font-lock-function-name-face)
   '("\\([a-zA-Z0-9]+\\)\\([?]\\)" . font-lock-type-face)
   '("\\(\\\\x\\)\\([a-fA-F0-9]+\\)" . font-lock-string-face)
   '("\\([a-zA-Z0-9_-~!@#$%^&*()_+-={}]+\\)" . font-lock-variable-name-face)
   ) 
  "Maximum highlighting for Funk major mode")

(defconst funk-font-lock-keywords-i
  (eval-when-compile
    (list
     ;;'("\\([a-zA-Z0-9_-~!@#$%^&*()_+-={}]+\\)" . font-lock-variable-name-face)
     (cons (regexp-opt
            '("append"
	      "apply"
	      "assert"
	      "car"
	      "car-set"
	      "cdr"
	      "cdr-set"
	      "cadr"
	      "caddr"
	      "cadddr"
	      "call"
	      "call-below"
	      "cddr"
	      "cdddr"
	      "cons"
	      "conslist"
	      "demetropolize"
	      "demetropolize1"
	      "elt"
	      "eq"
	      "equals"
	      "eval"
	      "exists"
	      "exit"
	      "fiber"
	      "filter"
	      "first"
	      "format"
	      "fourth"
	      "is-type"
	      "join"
	      "list"
	      "load"
	      "load_memory_image"
	      "lookup_type"
	      "maparray"
	      "mapc"
	      "mapcar"
	      "microsleep"
	      "millisleep"
	      "nanosleep"
	      "not"
	      "null"
	      "plan"
	      "plan-below"
	      "plan-call"
	      "print"
              "range"
	      "relationship"
	      "save_memory_image" "second" "set-car" "set-cdr" "simple_length" "sleep" "sleep_for_nanoseconds" "slots"
              "t" "third" "this-fiber" "thread-complete" "thread-value" "time" "type" "terminal_format"
	      "quit")
            'words)
           'font-lock-function-name-face)
     (cons (regexp-opt
            '("adjective_group"
	      "adjective_word"
	      "adverb_word"
	      "agency"
	      "agent_body"
	      "array"
	      "binder_word"
	      "blocks_world"
	      "bug"
	      "bytecode"
	      "bytecode_event"
	      "cairo_context"
	      "cairo_object"
	      "cairo_surface"
	      "cause"
	      "cause_group"
	      "cfunk"
	      "char"
	      "character"
	      "chunk"
	      "circular_buffer"
	      "classifier_word"
	      "clause"
	      "cmutex"
	      "compound_object"
	      "cons"
	      "core_extension"
	      "determiner_word"
	      "double"
	      "doublelink"
	      "doublelinklist"
	      "environment"
	      "equals_hash"
	      "event"
	      "event_stream"
	      "exception"
	      "fiber"
	      "fiber_trigger"
	      "fibermon"
	      "fibermon_fiber"
	      "file_handle"
	      "float"
	      "frame"
	      "frame_ball"
	      "funk"
	      "g_object"
	      "gdk_color"
	      "gdk_pixbuf"
	      "graph"
	      "graph_edge"
	      "graph_node"
	      "gtk_box"
	      "gtk_callback"
	      "gtk_entry"
	      "gtk_image"
	      "gtk_label"
	      "gtk_menu"
	      "gtk_menu_bar"
	      "gtk_scale"
	      "gtk_text_buffer"
	      "gtk_text_iter"
	      "gtk_text_mark"
	      "gtk_text_range"
	      "gtk_timeline"
	      "gtk_widget"
	      "hash"
	      "image"
	      "image_sequence"
	      "integer"
	      "interval_tree"
	      "keyboard_editor"
	      "largeinteger"
	      "larva"
	      "lick"
	      "lick_chunk"
	      "list"
	      "matches"
	      "matrix"
	      "mental_layer"
	      "metro"
	      "metrocfunk"
	      "mind"
	      "mindmon"
	      "mindmon_agent"
	      "mindmon_project"
	      "mindmon_world"
	      "movie"
	      "movie_context"
	      "mutex"
	      "noun_group"
	      "noun_word"
	      "number_word"
	      "optimize_chunk"
	      "optimize_data"
	      "optimize_fiber"
	      "ordinal_word"
	      "package"
	      "package_handler"
	      "parse_tree"
	      "parse_tree_node"
	      "particle_word"
	      "physical_world"
	      "place"
	      "pointer"
	      "primobject"
	      "primobject_type"
	      "processor"
	      "pronoun_word"
	      "ptype"
	      "ptypehash"
	      "redblacktree"
	      "reflective_mind"
	      "relative_time"
	      "resource"
	      "scheduler"
	      "self_model"
	      "semantic_action"
	      "semantic_agent"
	      "semantic_event"
	      "semantic_frame"
	      "semantic_object"
	      "semantic_realm"
	      "semantic_time"
	      "set"
	      "simple_array"
	      "size_2d"
	      "source"
	      "speak_language"
	      "story"
	      "story_event"
	      "stream"
	      "string"
	      "symbol"
	      "termios"
	      "time"
	      "timeline"
	      "timeline_event"
	      "traced_array"
	      "traced_cmutex"
	      "traced_mind"
	      "traced_resource"
	      "verb_group"
	      "verb_word")
            'words)
           'font-lock-keyword-face)
     (cons (regexp-opt
            '("!="
	      "<="
	      ">="
	      "=="
	      ">>"
	      "<<"
	      "+"
	      "-"
	      "*"
	      "/"
	      "="
	      "<"
	      ">"
	      "and"
	      "assert-type"
	      "cause-define"
	      "cause-define-funk"
	      "cause-defunk"
	      "cause-lookup"
	      "cause-lookup-funk"
	      "cond"
	      "construct"
	      "defcondition"
	      "defcore"
	      "defcorefunk"
	      "define"
	      "define-funk"
	      "defmetro"
	      "defpackage"
	      "defplan"
	      "deframe"
	      "deftypeconstruct"
	      "deftypefunk"
              "defunk"
	      "defunk-local"
	      "dotimes"
	      "error"
	      "execute"
	      "frame"
	      "funk"
	      "funk-new_with_name"
	      "funkall"
              "get"
	      "get-apply"
	      "globalize"
	      "globalize-funk"
	      "have"
	      "have-apply"
	      "if"
	      "label"
	      "labels"
	      "length"
	      "let"
	      "let*"
	      "metro"
	      "mutate"
	      "new"
	      "new-apply"
	      "nil"
	      "on-trigger"
	      "or"
	      "package"
	      "parc"
	      "parcar"
	      "parlet"
	      "parog"
	      "partimes"
	      "pause"
	      "prog"
	      "put"
	      "quote"
	      "reload"
	      "require"
	      "resume"
	      "set"
	      "set-apply"
	      "shelter"
	      "semantic-lookup_set"
	      "semantic-lookup_set-apply"
	      "semantic-add"
	      "semantic-add-apply"
	      "semantic-remove"
	      "semantic-remove-apply"
	      "type-get"
	      "type-set"
	      "type-execute"
	      "type-have"
	      "type-get-apply"
	      "type-set-apply"
	      "type-execute-apply"
	      "type-have-apply"
	      "wait-for-trigger"
	      "while"
	      "with"
	      "with-new-cause"
	      "yield"
	      )
            'words)
           'font-lock-keyword-face)
     ;;'("\\(:\\)\\([a-zA-Z0-9_]+\\)" . font-lock-type-face)
     ;;'("\\('[a-zA-Z0-9\n\t\\ _-~!@#$%^&*/()_+-={}]+'\\)" . font-lock-string-face)
     '("\\(&\\)\\([a-zA-Z0-9_]+\\)" . font-lock-function-name-face)
     '("\\([a-zA-Z0-9]+\\)\\([?]\\)" . font-lock-type-face)
     '("\\(\\\x\\)\\([a-fA-F0-9]+\\)" . font-lock-string-face)
     ;;'("\\([+-*/=<>]\\|[<>!]=\\)" . font-lock-function-name-face)
     ;;'("\\([+-*/=]\\)" . font-lock-function-name-face)
     ;;'("\\([a-zA-Z0-9_-~!@#$%^&*()_+-={}]+\\)" . font-lock-variable-name-face)
     ;;'("\\(\\\x\\)\\([a-fA-F0-9]+\\)" . font-lock-string-face)
     ;;'("\\([+-*/=<>]\\|[<>!]=\\)" . font-lock-function-name-face)
     ;;'("\\([+-*/=]\\)" . font-lock-function-name-face)
     '("\\([a-zA-Z0-9_-~!@#$%^&*_+-=]+\\)" . font-lock-variable-name-face)
     ))
  "My hightlighting scheme for Funk mode")
     
(defvar funk-font-lock-keywords funk-font-lock-keywords-i
  "Maximum highlighting for Funk major mode")

;; is adding punctuation to word syntax appropriate?? 
(defvar funk-mode-syntax-table
  (let ((funk-mode-syntax-table (make-syntax-table)))
   ;;(modify-syntax-entry ?. "_" funk-mode-syntax-table)
   ;;(modify-syntax-entry ?: "_" funk-mode-syntax-table)
   ;;(modify-syntax-entry ?{ "(" funk-mode-syntax-table)
   ;;(modify-syntax-entry ?} ")" funk-mode-syntax-table)
   ;;(modify-syntax-entry ?[ "(" funk-mode-syntax-table)
   ;;(modify-syntax-entry ?] ")" funk-mode-syntax-table)
   ;;(modify-syntax-entry ?( "(" funk-mode-syntax-table)
   ;;(modify-syntax-entry ?) ")" funk-mode-syntax-table)
   ;;(modify-syntax-entry ?` "\\" funk-mode-syntax-table)
   ;;(modify-syntax-entry ?_ "w" funk-mode-syntax-table)
   ;;(modify-syntax-entry ?# "<" funk-mode-syntax-table)
   ;;(modify-syntax-entry ?\n ">" funk-mode-syntax-table)
   (modify-syntax-entry ?' "\"" funk-mode-syntax-table)
   funk-mode-syntax-table)
  "Syntax for Funk major mode")

(defvar funk-mode-syntax-table-i
  (let ((funk-mode-syntax-table (make-syntax-table)))
    ;;(modify-syntax-entry ?. "_" funk-mode-syntax-table)
    ;;(modify-syntax-entry ?: "_" funk-mode-syntax-table)
    ;;(modify-syntax-entry ?{ "(" funk-mode-syntax-table)
    ;;(modify-syntax-entry ?} ")" funk-mode-syntax-table)
    ;;(modify-syntax-entry ?[ "(" funk-mode-syntax-table)
    ;;(modify-syntax-entry ?] ")" funk-mode-syntax-table)
    ;;(modify-syntax-entry ?( "(" funk-mode-syntax-table)
    ;;(modify-syntax-entry ?) ")" funk-mode-syntax-table)
    ;;(modify-syntax-entry ?` "\\" funk-mode-syntax-table)
    ;;(modify-syntax-entry ?# "<" funk-mode-syntax-table)
    ;;(modify-syntax-entry ?\n ">" funk-mode-syntax-table)
    (modify-syntax-entry ?_ "w" funk-mode-syntax-table)
    (modify-syntax-entry ?` "'" funk-mode-syntax-table)
    (modify-syntax-entry ?, "'" funk-mode-syntax-table)
    (modify-syntax-entry ?' "\"" funk-mode-syntax-table)
    (modify-syntax-entry ?+ "w" funk-mode-syntax-table)
    (modify-syntax-entry ?- "w" funk-mode-syntax-table)
    (modify-syntax-entry ?* "w" funk-mode-syntax-table)
    (modify-syntax-entry ?/ "w" funk-mode-syntax-table)
    (modify-syntax-entry ?= "w" funk-mode-syntax-table)
    (modify-syntax-entry ?< "w" funk-mode-syntax-table)
    (modify-syntax-entry ?> "w" funk-mode-syntax-table)
    ;;(modify-syntax-entry ?( "(" funk-mode-syntax-table)
    ;;(modify-syntax-entry ?) ")" funk-mode-syntax-table)
    funk-mode-syntax-table)
  "Syntax for Funk major mode")

(defun funk-mode ()
  "Major mode for editing Funk files"
  (interactive)
  (kill-all-local-variables)
  (set-syntax-table funk-mode-syntax-table-i)
  (use-local-map funk-mode-map)
  (set (make-local-variable 'font-lock-defaults) '(funk-font-lock-keywords))
  
  (make-local-variable 'compile-command)
  ;;(setq compile-command (format "funk %s"
  ;;			 (expand-file-name buffer-file-name)))
  
  (setq major-mode 'funk-mode)
  (setq mode-name "Funk")
  (run-hooks 'funk-mode-hook))

(provide 'funk-mode)




