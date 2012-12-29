# -*- encoding: utf-8 -*-
$:.push File.expand_path("../lib", __FILE__)
require "blink1/version"

Gem::Specification.new do |s|
  s.name        = "rb-blink1"
  s.version     = Blink1::VERSION
  s.platform    = Gem::Platform::RUBY
  s.authors     = ['Atsushi Nagase']
  s.email       = ['a@ngs.io']
  s.homepage    = "http://github.com/ngs/rb-blink1"
  s.summary     = "Ruby interface for blink(1)"
  s.description = "Controls blink(1)"
  s.requirements << "libusb, version 1.0 or greater"

  s.rubyforge_project = "blink1"
  s.add_development_dependency  'bundler'
  s.add_development_dependency  'rspec'
  s.add_development_dependency  'rake'
  # s.add_development_dependency  'guard-rspec', '~> 1.2'

  s.files        = `git ls-files`.split("\n").reject{|f| f =~ /^(\..+|Gemfile.*)$/}
  s.extensions = ["ext/blink1/extconf.rb"]
  s.require_paths = ["lib", "ext"]
end

