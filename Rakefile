require 'bundler/gem_tasks'
require 'rake/extensiontask'
require 'rake/clean'

CLEAN.include 'lib/url_parser.so'

desc "Re-build extension library and run spec"
task :spec => [:prereq, :spec_runner]

begin
  require 'rspec/core/rake_task'
  RSpec::Core::RakeTask.new(:spec_runner)
rescue LoadError
end


task :prereq => [:clean, :liburlparser, :compile]

Rake::ExtensionTask.new('url_parser')

desc "Build static library liburlparser.a"
task :liburlparser do
  sh "make -C ext/lib/url_parser_re2c"
end
