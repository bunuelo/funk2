

%: %.md
	markdown2pdf -S -N -C header.tex $@.md -o $@.pdf

make: lab2.md
	markdown2pdf -S -N -C header.tex lab2.md -o lab2.pdf
	
html: lab2.md
	pandoc -S -N lab2.md  -f markdown -t HTML -A footer.htm --css http://web.media.mit.edu/~dustin/webstyle.css > lab2.html

slides: lab2.md
	s5_reform lab2.md > tmp.s5
	pandoc -w s5 -s tmp.s5 > lab2_slides.html
	rm tmp.s5

rtf: lab2.md
	pandoc -S -N -w latex -C header.tex lab2.md -o lab2.tex
	latex2rtf lab2.tex

clean:
	rm *.bbl; rm *.blg; rm *.aux; rm *.log; rm *.brf; rm *.rst; rm *.out; rm *~;

