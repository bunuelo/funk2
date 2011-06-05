default: phdthesis.pdf

phdthesis.pdf: \
  makefile \
  phdthesis.tex \
  frontbackmatter/Abstract.tex \
  frontbackmatter/Acknowledgments.tex \
  frontbackmatter/Bibliography.tex \
  frontbackmatter/Colophon.tex \
  frontbackmatter/Contents.tex \
  frontbackmatter/Declaration.tex \
  frontbackmatter/Dedication.tex \
  frontbackmatter/Publication.tex \
  frontbackmatter/Titleback.tex \
  frontbackmatter/Titlepage.tex \
  chapters/chapter_stages.tex
	pdflatex phdthesis.tex
	pdflatex phdthesis.tex

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

