date_tag = $(shell date +%Y.%m.%d)
version = $(shell cat trunk/funk2/version)
version_tag = $(version).$(date_tag)
package_rootname = funk2-$(version_tag)
tmp_dir = /tmp/funk2-deb/
deb_create_dir = $(tmp_dir)deb_create_dir/
export_dir = $(deb_create_dir)$(package_rootname)/

clean-export:
	rm -Rf $(export_dir)

export:
	mkdir -p $(deb_create_dir)
	svn export trunk/funk2 $(export_dir)

tar.gz: export
	cd $(export_dir)..; tar cf $(package_rootname).tar $(package_rootname); gzip $(package_rootname).tar

deb: export
	cd $(export_dir); dpkg-buildpackage -rfakeroot
	mkdir -p releases/$(package_rootname)/
	cp $(deb_create_dir)/*.deb releases/$(package_rootname)/
	cp $(deb_create_dir)/*.dsc releases/$(package_rootname)/
	cp $(deb_create_dir)/*.changes releases/$(package_rootname)/
	cp $(deb_create_dir)/*.tar.gz releases/$(package_rootname)/

clean: clean-export

