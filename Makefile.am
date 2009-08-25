ACLOCAL_AMFLAGS = -I m4

dist-hook:
	if test -d $(top_srcdir)/.svn; then \
    (cd $(top_srcdir) && rm ChangeLog && svn2cl --group-by-day); \
    cp $(top_srcdir)/ChangeLog $(distdir); \
fi
