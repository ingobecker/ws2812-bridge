require 'ceedling'
Ceedling.load_project

directory 'libopencm3' do
  sh "git submodule update --init"
  sh "make -C libopencm3"
end

task release: :libopencm3
