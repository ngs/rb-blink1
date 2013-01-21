require 'rubygems'
require 'spork'
require 'rspec'
#uncomment the following line to use spork with the debugger
#require 'spork/ext/ruby-debug'

$LOAD_PATH.unshift(File.dirname(__FILE__))
$LOAD_PATH.unshift(File.join(File.dirname(__FILE__), '..', 'lib'))
$LOAD_PATH.unshift(File.join(File.dirname(__FILE__), '..', 'ext'))

require 'blink1'

RSpec.configure do |config|
  if !ENV['CI'] &&Blink1.list.length > 0
    puts "\nTesting with device at path #{ Blink1.cached_path(0) }\n\n"
  else
    config.filter_run_excluding :device => true
  end
end

Spork.prefork do; end

Spork.each_run do; end


