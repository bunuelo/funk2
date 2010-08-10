;; 
;; Copyright (c) 2007 Bo Morgan.
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

(add-to-list 'auto-mode-alist '("\\.funk\\'" . funk-mode))
(add-to-list 'auto-mode-alist '("\\.fu\\'"   . funk-mode))
(add-to-list 'auto-mode-alist '("\\.fu2\\'"  . funk-mode))
(add-to-list 'auto-mode-alist '("\\.fpkg\\'" . funk-mode))

(add-to-list 'interpreter-mode-alist '("funk" . funk-mode))


;; only defined one keyword list right now 
(defconst funk-font-lock-keywords-3
  (list
   '("\\('[a-zA-Z0-9\n\t\\ _-~!@#$%^&*/()_+-={}]+'\\)" . font-lock-string-face)
   '("\\(&\\)\\([a-zA-Z0-9]+\\)" . font-lock-function-name-face)
   '("\\<action\\|actor\\|act\\>" . font-lock-keyword-face)
   '("\\<elt\\>" . font-lock-keyword-face)
   '("\\<f\\(?:irst\\|ourth\\)\\|make-\\(?:funk\\|metro\\)\\|s\\(?:econd\\|et-car\\|et-cdr\\)\\|t\\(?:hird\\|hread-\\(?:complete\\?\\|value\\)\\)\\>" . font-lock-function-name-face)
   '("\\<format\\|or\\>" . font-lock-function-name-face)
   ;;'("\\[\\<format\\|or\\> " . font-lock-function-name-face)
   ;;'("\\<format\\|or\\> " . font-lock-function-name-face)
   '("\\<range\\>" . font-lock-function-name-face)
   '("\\<join\\>" . font-lock-function-name-face)
   '("\\<parlet\\>" . font-lock-keyword-face)
   '("\\<partimes\\>" . font-lock-keyword-face)
   '("\\<act\\(?:ion\\|or\\|\\)\\|ca\\(?:dddr\\|ddr\\|dr\\)\\|cd\\(?:ddr\\|ddr\\|dr\\)\\|cond\\|def\\(?:unk\\|ine-funk\\|ine\\|metro\\)\\|dotimes\\|funk\\|g\\(?:lobalize-funk\\|lobalize\\)\\|if\\|let\\|metro\\|p\\(?:arlet\\|rog\\|ut\\)\\|quote\\|while\\>" . font-lock-keyword-face)
   '("\\<and\\|apply\\|c\\(?:ar\\|dr\\|ons\\)\\|list\\|ma\\(?:pc\\(?:ar\\|\\)\\)\\|null\\|print\\|set\\|get\\|have\\>" . font-lock-function-name-face)
   '("\\<nil\\>" . font-lock-keyword-face)
   '("\\(:\\)\\([a-zA-Z0-9]+\\)" . font-lock-type-face)
   '("\\([a-zA-Z0-9]+\\)\\([?]\\)" . font-lock-type-face)
   '("\\(\\\\x\\)\\([a-fA-F0-9]+\\)" . font-lock-string-face)
   '("\\([+-*/=]\\)" . font-lock-function-name-face)
   '("\\([a-zA-Z0-9_-~!@#$%^&*()_+-={}]+\\)" . font-lock-variable-name-face)
   ) 
  "Maximum highlighting for Funk major mode")

(defconst funk-font-lock-keywords-i
  (eval-when-compile
    (list
     ;;'("\\([a-zA-Z0-9_-~!@#$%^&*()_+-={}]+\\)" . font-lock-variable-name-face)
     (cons (regexp-opt
            '("and" "apply" "car" "cdr" "cons" "list" "mapc" "mapcar" "null" "print"
              "range" "join" "format" "or" "not" "cadr" "caddr" "cadddr" "cddr" "cdddr"
              "first" "fourth" "make-funk" "make-metro" "second" "set-car" "set-cdr"
              "third" "thread-complete" "thread-value" "eq" "equals" "set" "get" "have" "execute")
            'words)
           'font-lock-function-name-face)
     (cons (regexp-opt
            '("+" "-" "*" "/" "=" "<" ">" "!=" "<=" ">=") 'words)
           'font-lock-function-name-face)
     (cons (regexp-opt
            '("action" "actor" "act" "elt" "parlet" "partimes" "cond"
              "defunk" "define-funk" "define" "defmetro" "deftypefunk" "deframe" "deftypeconstruct" "dotimes" "funk"
              "globalize" "globalize-funk" "if" "let" "let*" "metro" "parlet" "prog" "put" "quote" "while" "nil" "t")
            'words)
           'font-lock-keyword-face)
     ;;'("\\('[a-zA-Z0-9\n\t\\ _-~!@#$%^&*/()_+-={}]+'\\)" . font-lock-string-face)
     '("\\(&\\)\\([a-zA-Z0-9_]+\\)" . font-lock-function-name-face)
     '("\\(:\\)\\([a-zA-Z0-9_]+\\)" . font-lock-type-face)
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
   ;;(modify-syntax-entry ?_ "w" funk-mode-syntax-table)
   ;;(modify-syntax-entry ?# "<" funk-mode-syntax-table)
   ;;(modify-syntax-entry ?\n ">" funk-mode-syntax-table)
   (modify-syntax-entry ?' "\"" funk-mode-syntax-table)
   (modify-syntax-entry ?_ "w" funk-mode-syntax-table)
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




