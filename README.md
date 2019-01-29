# WS2812 bridge

This is a simple serial to WS2812 bridge. It's based on a stm32f103
microcontroller. On the input side, data can be fed into the bridge by using a
very simple protocol over a serial connection. The data is then converted into a
WS2812 compatible output signal.

# Features

**double buffering** There will be no tearing. The bridge doesn't output any
incomplete frames.

**hardware acceleration** The output signal generation is done mostly in
hardware by using DMA and PWM timers. That way, you have a lot of time doing
software processing.

**variable framerate** The framerate can be controlled in software. The maximum
framerate dependes on the number of LEDs connected, the available input speed
of the serial interface and can't be faster than 400 Hz because that's the
internal PWM frequency of the LED.

**input buffering** Set the size of the serial input buffer on compile time.
Use a small buffer size for low latency applications or a lager size to avoid
buffer underruns.

**test coverage** Most parts of the software are tested.

# Development

The buildsystem is installed as a rubygem:

```
$ bundle install
```

The tests can be compiled and run for/on your host system. Make sure you have
gcc installed and run:

```
$ ./bin/ceedling
```

In order to build a binary for the target, make sure you have a
`arm-none-eabi-gcc`-toolchain, make, python and git installed and run:

```
$ ./bin/ceedling release
```
