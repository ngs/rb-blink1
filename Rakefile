require "bundler/gem_tasks"

task :default => :spec

task :build do
  Dir.chdir('ext/blink1') do
    output = `ruby extconf.rb`
    raise output unless $? == 0
    output = `make`
    raise output unless $? == 0
  end
end

require 'rspec/core/rake_task'
RSpec::Core::RakeTask.new
