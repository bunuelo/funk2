
%: %.md
	markdown2pdf -S -N -C header.tex $@.md -o $@.pdf

make: lab1.md
	markdown2pdf -S -N -C header.tex lab1.md -o lab1.pdf
	
html: lab1.md
	pandoc -S -N lab1.md  -f markdown -t HTML -A footer.htm --css http://web.media.mit.edu/~dustin/webstyle.css > lab1.html

slides: lab1.md
	s5_reform lab1.md > tmp.s5
	pandoc -w s5 -s tmp.s5 > lab1_slides.html
	rm tmp.s5

rtf: lab1.md
	pandoc -S -N -w latex -C header.tex lab1.md -o lab1.tex
	latex2rtf lab1.tex

clean:
	rm *.bbl; rm *.blg; rm *.aux; rm *.log; rm *.brf; rm *.rst; rm *.out; rm *~;

