
%: %.md
	markdown2pdf -S -N -C header.tex $@.md -o $@.pdf

make: final.md
	markdown2pdf -S -C header.tex final.md -o final.pdf
	
html: final.md
	pandoc -S -N final.md  -f markdown -t HTML -A footer.htm --css http://web.media.mit.edu/~dustin/webstyle.css > final.html

slides: final.md
	s5_reform final.md > tmp.s5
	pandoc -w s5 -s tmp.s5 > final_slides.html
	rm tmp.s5

rtf: final.md
	pandoc -S -N -w latex -C header.tex final.md -o final.tex
	latex2rtf final.tex

clean:
	rm *.bbl; rm *.blg; rm *.aux; rm *.log; rm *.brf; rm *.rst; rm *.out; rm *~;

