require 'ceedling'
Ceedling.load_project

directory 'vendor/libopencm3/include' do
  sh "git submodule update --init"
  sh "make -C vendor/libopencm3"
end

task release: 'vendor/libopencm3/include'

namespace :target do

  desc 'start debug session on target'
  task debug: :release do
    exec <<-GDB.gsub(/\s+/, " ")
        arm-none-eabi-gdb
          -ex 'target extended-remote /dev/ttyACM0'
          -x vendor/black_magic_probe_flash.scr
          #{PROJECT_BUILD_RELEASE_ROOT}/#{RELEASE_BUILD_OUTPUT}
          GDB
  end

  desc 'start debug session on target'
  task flash: :release do
    exec <<-GDB.gsub(/\s+/, " ")
        arm-none-eabi-gdb
          --batch
          -ex 'target extended-remote /dev/ttyACM0'
          -x vendor/black_magic_probe_flash.scr
          #{PROJECT_BUILD_RELEASE_ROOT}/#{RELEASE_BUILD_OUTPUT}
          GDB
  end
end
