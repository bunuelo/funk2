date_tag = $(shell date +%Y.%m.%d)
version = $(shell cat trunk/funk2/version)
upstream_version = 1
version_tag = $(version).$(date_tag)-$(upstream_version)
package_rootname = funk2-$(version_tag)
tmp_dir = /tmp/funk2-deb/
export_dir = $(tmp_dir)$(package_rootname)/

clean-export:
	rm -Rf $(export_dir)

export:
	mkdir -p $(tmp_dir)
	svn export trunk/funk2 $(export_dir)

tar.gz: export
	cd $(export_dir)..; tar cf $(package_rootname).tar $(package_rootname); gzip $(package_rootname).tar

deb: export
	cd $(export_dir); dpkg-buildpackage -rfakeroot


clean: clean-export

