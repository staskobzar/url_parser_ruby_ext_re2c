# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'url_parser/version'

Gem::Specification.new do |spec|
  spec.name          = "url_parser"
  spec.version       = UrlParser::VERSION
  spec.authors       = ["Stas Kobzar"]
  spec.email         = ["stas@modulis.ca"]
  spec.summary       = %q{URL parser library.}
  spec.description   = %q{URL parser made with ruby C extension. C library is in git submodule.}
  spec.homepage      = "https://github.com/staskobzar/url_parser_ruby_ext_re2c"
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0")
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]
  spec.extensions    = ["ext/url_parser/extconf.rb"]

  spec.add_development_dependency "bundler", "~> 1.12"
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "rspec", "~> 3.0"
  spec.add_development_dependency "guard"
  spec.add_development_dependency "guard-rspec"
  spec.add_development_dependency "rake-compiler"
end
