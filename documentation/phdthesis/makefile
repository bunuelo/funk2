default: phdthesis.pdf

#  bibliography.bib

phdthesis.pdf: \
  makefile \
  phdthesis.tex \
  frontbackmatter/abstract.tex \
  frontbackmatter/acknowledgments.tex \
  frontbackmatter/bibliography.tex \
  frontbackmatter/colophon.tex \
  frontbackmatter/contents.tex \
  frontbackmatter/declaration.tex \
  frontbackmatter/dedication.tex \
  frontbackmatter/publication.tex \
  frontbackmatter/titleback.tex \
  frontbackmatter/titlepage.tex \
  chapters/chapter_models_of_cognition.tex \
  chapters/chapter_stages.tex \
  chapters/chapter02.tex \
  chapters/chapter03.tex \
  chapters/chapter_appendix_philosophy.tex \
  chapters/chapter_appendix_psychology.tex \
  chapters/chapter_appendix_neuroscience.tex \
  chapters/chapter_appendix_artificial_intelligence.tex \
  chapters/chapter_appendix_computer_science.tex \
  chapters/chapter_appendix_mental_health.tex \
  chapters/chapter_appendix_education.tex \
  gfx/objective_description.pdf \
  gfx/agent_environment.pdf \
  gfx/reinforcement_learning.pdf \
  gfx/perception_categorization.pdf
	pdflatex phdthesis
	bibtex   phdthesis
	pdflatex phdthesis
	pdflatex phdthesis

clean:
	rm -f phdthesis.pdf
	rm -f chapters/*.aux
	rm -f frontbackmatter/*.aux
	rm -f phdthesis.aux
	rm -f phdthesis.lof
	rm -f phdthesis.log
	rm -f phdthesis.lol
	rm -f phdthesis.lot
	rm -f phdthesis.out
	rm -f phdthesis.toc

