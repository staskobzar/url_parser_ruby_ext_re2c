require 'mkmf'

find_executable('cc')
find_executable('ar')

libdir = File.expand_path(File.join(File.dirname(__FILE__), "../lib/url_parser_re2c/src"))

Dir.chdir(libdir) do
  system 'cc -fPIC -c -o url_parser.o url_parser.c'
  system 'ar rcs liburlparser.a url_parser.o'
end

$libs += " -lurlparser"
$INCFLAGS << " -I#{libdir}"
$LIBPATH << libdir

create_makefile 'url_parser'
