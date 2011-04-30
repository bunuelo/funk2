default: phdthesis.pdf

phdthesis.pdf: \
  makefile \
  phdthesis.tex \
  FrontBackmatter/Abstract.tex \
  FrontBackmatter/Acknowledgments.tex \
  FrontBackmatter/Bibliography.tex \
  FrontBackmatter/Colophon.tex \
  FrontBackmatter/Contents.tex \
  FrontBackmatter/Declaration.tex \
  FrontBackmatter/Dedication.tex \
  FrontBackmatter/Publication.tex \
  FrontBackmatter/Titleback.tex \
  FrontBackmatter/Titlepage.tex \
  chapters/chapter_stages.tex
	pdflatex phdthesis.tex
	pdflatex phdthesis.tex

clean:
	rm -f phdthesis.pdf
	rm -f chapters/*.aux
	rm -f FrontBackmatter/*.aux
	rm -f phdthesis.aux
	rm -f phdthesis.lof
	rm -f phdthesis.log
	rm -f phdthesis.lol
	rm -f phdthesis.lot
	rm -f phdthesis.out
	rm -f phdthesis.toc

