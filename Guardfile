notification :tmux,
  :display_message => true,
  :default_message_color => '#000000',
  :success => '#006600',
  :failed  => '#660000',
  :pending => '#660066',
  :default => '#000066'

guard 'spork' do
  watch('Gemfile')
  watch('Gemfile.lock')
  watch('spec/spec_helper.rb')
  watch(%r{^spec/.+_spec\.rb$})
  watch(%r{^ext/blink1/.+.c$})
  watch(%r{^ext/blink1/extconf.rb$})
  watch('spec/spec_helper.rb')
end

guard 'rake', :task => 'build' do
  watch(%r{^lib/blink1.rb$})
  watch(%r{^ext/blink1/blink1_ext.c$})
  watch(%r{^ext/blink1/extconf.rb$})
end

guard 'rspec' do
  watch(%r{^ext/blink1/.+.c$})       { |m| "spec" }
  watch(%r{^ext/blink1/extconf.rb$}) { |m| "spec" }
  watch(%r{^lib/(.+)\.rb$})  { |m| "spec/#{m[1]}_spec.rb" }
  watch(%r{^spec/(.+)\.rb$}) { |m| "spec/#{m[1]}_spec.rb" }
end
