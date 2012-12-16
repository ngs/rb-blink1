# -*- encoding: utf-8 -*-
$:.push File.expand_path("../lib", __FILE__)
require "blink1/version"

Gem::Specification.new do |s|
  s.name        = "blink1"
  s.version     = Blink1::VERSION
  s.platform    = Gem::Platform::RUBY
  s.authors     = ['Atsushi Nagase']
  s.email       = ['a@ngs.io']
  s.homepage    = "http://github.com/ngs/blink1.rb"
  s.summary     = "Ruby interface for blink(1)"
  s.description = "Controls blink(1)"

  s.rubyforge_project = "blink1"

  s.add_development_dependency  'bundler',     '~> 1.0'
  # s.add_development_dependency  'rspec',       '~> 2.11'
  # s.add_development_dependency  'guard-rspec', '~> 1.2'

  s.files        = Dir.glob('{lib,ext}/**/*') + %w[LICENSE README.rdoc]
  s.require_path = 'lib'
end

