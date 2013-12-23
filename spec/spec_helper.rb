require 'rubygems'
require 'spork'
require 'rspec'
require "codeclimate-test-reporter"
# require 'spork/ext/ruby-debug'

CodeClimate::TestReporter.start

Spork.prefork do; end

Spork.each_run do; end

require 'blink1'

RSpec.configure do |config|
  if ENV['CI']
    config.filter_run_excluding device: true
  end
end

$LOAD_PATH.unshift(File.dirname(__FILE__))
$LOAD_PATH.unshift(File.join(File.dirname(__FILE__), '..', 'lib'))
$LOAD_PATH.unshift(File.join(File.dirname(__FILE__), '..', 'ext'))

