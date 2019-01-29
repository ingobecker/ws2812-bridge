require 'ceedling'
Ceedling.load_project

directory 'vendor/libopencm3' do
  sh "git submodule update --init"
  sh "make -C vendor/libopencm3"
end

task release: 'vendor/libopencm3'
