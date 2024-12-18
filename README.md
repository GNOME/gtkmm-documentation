# gtkmm-documentation
This is the documentation for gtkmm, a C++ API for GTK.

gtkmm-documentation can be built with Autotools or Meson.
Autotools support may be dropped in the future.

docs/tutorial/C/index-in.docbook and the built index.docbook files are
DocBook 5.0 documents. index.docbook requires these packages (Ubuntu names,
can have other names in other distros):
  * docbook5-xml
  * docbook-xsl

It may be possible to build without these packages, but it will be much slower.
The xmllint command is told to read files from http://docbook.org.
The xsltproc command is told to read files from http://docbook.sourceforge.net.
The commands first search for local copies of those files. If local copies exist
and are installed at expected locations, the commands make no network accesses.

# General information

Web site
 - https://gtkmm.gnome.org

Download location
 - https://download.gnome.org/sources/gtkmm-documentation

Programming with gtkmm4 (gtkmm tutorial)
 - https://gnome.pages.gitlab.gnome.org/gtkmm-documentation

Tarballs contain the tutorial in HTML format.
See the docs/tutorial/html directory.

Discussion on GNOME's discourse forum
 - https://discourse.gnome.org/tag/cplusplus
 - https://discourse.gnome.org/c/platform

Git repository
 - https://gitlab.gnome.org/GNOME/gtkmm-documentation

Bugs can be reported to
 - https://gitlab.gnome.org/GNOME/gtkmm-documentation/issues

Patches can be submitted to
 - https://gitlab.gnome.org/GNOME/gtkmm-documentation/merge_requests

# Building with Meson

Create a build directory:
```
  $ cd gtkmm-documentation
  $ meson setup [options] <build-dir>
```
Do not call the build-dir gtkmm-documentation/build. There is already such a
directory, used when building with Autotools.

Print a list of configuration options:
```
  $ cd <build-dir>
  $ meson configure
```

Example of changing options:
```
  $ cd <build-dir>
  $ meson configure --prefix=/opt/gnome -Dbuild-translations=true
```

Create the html files of the tutorial:
```
  $ cd <build-dir>
  $ ninja
```

Install them:
```
  $ ninja install
```

Build the example programs:
```
  $ ninja examples
```
or (probably slower)
```
  $ ninja test
```

Create a PDF file:
```
  $ meson configure -Dbuild-pdf=true
  $ ninja
```
This requires that you have xsltproc and either the dblatex or fop commands
installed.

Make a tarball:
```
  $ ninja dist
```
or, if you don't want to build all example programs:
```
  $ meson dist --no-tests
```
In addition to the files in the git repository, the tarball will contain some
built files. These files must already exist. `ninja dist` will fail, unless you
have previously run `ninja` with build-translations=true.

This tarball is not identical to one made with `make dist` or `make distcheck`.
There is e.g. no `configure` file. If you want to use a tarball made with
`ninja dist` for building with Autotools, you have to start with ./autogen.sh.
