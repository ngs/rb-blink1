require 'bundler/gem_tasks'
require 'rdoc/task'
require 'rspec/core/rake_task'

task :default => :spec
task :spec => :build

task :build do
  Dir.chdir('ext/blink1') do
    output = `ruby extconf.rb`
    raise output unless $? == 0
    output = `make`
    raise output unless $? == 0
  end
end


RSpec::Core::RakeTask.new

RDoc::Task.new do |rdoc|

  rdoc.main = "README.rdoc"
  rdoc.rdoc_files.include("README.rdoc", "lib/**/*.rb", "ext/blink1/blink1.c")

end
