guard 'spork' do
  watch('Gemfile')
  watch('Gemfile.lock')
  watch('spec/spec_helper.rb')
  watch(%r{^spec/.+_spec\.rb$})
  watch(%r{^ext/blink1/blink1.c$})
  watch(%r{^ext/blink1/extconf.rb$})
  watch('spec/spec_helper.rb')
end

guard 'rake', :task => 'build' do
  watch(%r{^lib/blink1.rb$})
  watch(%r{^ext/blink1/blink1.c$})
  watch(%r{^ext/blink1/extconf.rb$})
end

guard 'rspec' do
  watch(%r{^lib/blink1.rb$}) { |m| "spec/lib/blink1_spec.rb" }
  watch(%r{^ext/blink1/blink1.c$}) { |m| "spec/lib/blink1_spec.rb" }
  watch(%r{^ext/blink1/extconf.rb$}) { |m| "spec/lib/blink1_spec.rb" }
end
