require 'bundler/gem_tasks'
require 'rake/extensiontask'
require 'rake/clean'

CLEAN.include 'lib/url_parser/url.so'

task :prereq => [:clean, :liburlparser, :compile]

Rake::ExtensionTask.new('url_parser') do |ext|
  ext.name    = 'url'
  ext.lib_dir = 'lib/url_parser'
end

desc "Build static library liburlparser.a"
task :liburlparser do
  sh "make -C ext/lib/url_parser_re2c"
end
