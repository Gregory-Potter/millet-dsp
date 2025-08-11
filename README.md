<picture>
	<source srcset="./millet.png" media="(prefers-color-scheme: light)">
	<source srcset="./millet.png" media="(prefers-color-scheme: dark)">
	<img title="MilletDSP head of millet graphic" alt="A vector graphics image of a head of millet." src="./millet.png">
</picture>

# MilletDSP

A C++ library for digital signal processing — intended for handling audio processing within AudioUnit/VST plugins.

## Repository Organization

This library largely takes a class-per-file approach.
The main `MilletDSP` namespace is divided into several other namespaces,
which each have their own sub-directory. The library does not actually implement interfaces,
but I have provided some interface-like quick-references below.

### [MilletDSP::Data](./Data/)

Data container classes, the most important and prevelent of which is [`Buffer`](./Data/Buffer.h), which is a collection class for samples that is used heavily throughout the library.

### [MilletDSP::Delay](./Delay/)

Classes for delaying a signal. The `process` function takes in the input sample and stores it in a ring buffer, then outputs a sample from the ring buffer based on the delay length. Delay constructors will have a maximum delay parameter for allocating memory during initialization unless they have a fixed length.

```cpp
float process(float inputSample);
float getDelay() const;
void setDelay(float length); // OPTIONAL
```

### [MilletDSP::Envelope](./Envelope/)

Classes for shaping the amplitude of a signal, initiated by a velocity trigger. The `process` function progresses the envelope and outputs the attenuated input sample. Calling the `trigger` function will set the envelope to its first stage. As `process` is called, it will progress through the envelope stages until going into the idle stage, which just returns zeros.

```cpp
float process(float inputSample);
void triggerOn(float velocity); // velocity ranged 0 to 1
void triggerOff(); // OPTIONAL
```

### [MilletDSP::Exciter](./Exciter/)

Classes that generally combine a Generator and Envelope, meant to be used to excite a Resonator.

```cpp
float excite();
void triggerOn(float velocity); // velocity ranged 0 to 1
void triggerOff(); // OPTIONAL
```

### [MilletDSP::Executor](./Executor/)

Classes for cutting out large function chains when they would just be producing silence. This has been separated from envelopes to have the flexibility to use this functionality elsewhere; this comes up often when using resonators and other recursive delays. Use a lambda to pass in the function in the constructor.

```cpp
float handle();
void execute();
```

### [MilletDSP::Filter](./Filter/)

Classes for filtering a signal, like lowpass and highpass IIR filters.

```cpp
float process(float inputSample);
```

### [MilletDSP::Generator](./Generator/)

Classes for creating samples, i.e. audio signal generators like noise, sine wave, etc. It is expected that you will call the `generate` function once per output sample while sounding.

```cpp
float generate();
void setFrequency(); // OPTIONAL
void resetPhase(); // OPTIONAL
```

### [MilletDSP::Resonator](./Resonator/)

Classes that process incoming samples through filtered feedback loops.

```cpp
float process(float inputSample);
```

### [MilletDSP::Other](./Other/)

Various utilities that don't fit neatly in another category.
