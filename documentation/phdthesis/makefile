default: phdthesis.pdf

phdthesis.pdf: \
  makefile \
  phdthesis.tex \
  bibliography.bib \
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
  chapters/models_of_cognition_introduction.tex \
  chapters/literature_of_cognition_and_commonsense.tex \
  chapters/problems_to_solve.tex \
  chapters/theory_and_alternatives.tex \
  chapters/a_system.tex \
  chapters/experiments.tex \
  chapters/discussion.tex \
  chapters/future.tex \
  chapters/appendix_philosophy.tex \
  chapters/appendix_psychology.tex \
  chapters/appendix_neuroscience.tex \
  chapters/appendix_artificial_intelligence.tex \
  chapters/appendix_computer_science.tex \
  chapters/appendix_mental_health.tex \
  chapters/appendix_education.tex \
  gfx/objective_description.pdf \
  gfx/agent_environment.pdf \
  gfx/multiple_agent_environment.pdf \
  gfx/reinforcement_learning.pdf \
  gfx/perception_categorization.pdf \
  gfx/problem_complexity_versus_algorithm_adaptability.pdf \
  gfx/feedback_control.pdf \
  gfx/difference_engine_feedback_control.pdf \
  gfx/state_action.pdf \
  gfx/partially_observable.pdf \
  gfx/environment_perception_physical.pdf \
  gfx/frame_representation.pdf \
  gfx/frame_perception.pdf \
  gfx/physical_perception.pdf \
  gfx/goal_state.pdf
	pdflatex phdthesis
	bibtex   phdthesis
	pdflatex phdthesis
	pdflatex phdthesis

%.pdf: %.neato makefile
	neato $< -Tpdf > $@

%.pdf: %.dot makefile
	dot -Txdot $< | dot2tex -c -ftikz -tmath > temp.tex
	pdflatex temp.tex
	rm -f temp.tex
	mv -f temp.pdf $@

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
	rm -f phdthesis.bbl
	rm -f phdthesis.blg

