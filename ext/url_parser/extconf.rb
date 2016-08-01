require 'mkmf'

libdir = File.expand_path(File.join(File.dirname(__FILE__), "../lib/url_parser_re2c/src"))
$libs += " -lurlparser"
$INCFLAGS << " -I#{libdir}"
$LIBPATH << libdir

create_makefile 'url_parser'
