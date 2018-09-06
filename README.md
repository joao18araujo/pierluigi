# Palestrina-style Counterpoint Generator

[![pipeline status](https://api.travis-ci.org/joao18araujo/ly_parser.svg?branch=master)](https://travis-ci.org/joao18araujo/ly_parser)

### Dependencies

* **G++ 5.4**

### Optionals

* **Lilypond**
* **Timidity**

### Installation and Compilation

* **Install**

__Step 1:__ Clone the repository

`$ git clone https://github.com/joao18araujo/ly_parser.git`

__Step 2:__ Install C++ compiler

`$ sudo apt-get install g++`

* **Compile**

To compile all .cpp files from src/ folder all the .h headers from include/ folder, use the **make** command:

`$ make`

Optionally, to a faster compilation, you can use the **-j** flag:

`$ make -j`


* **Cleaning obj/ folder**

To remove all .d and .o files from obj/ folder , use the **clean** command:

`$ make clean`

* **Cleaning obj/ folder and removing software executable**

To remove all .d and .o files from obj/ folder and delete the binary executable from bin/ folder, user the **dist-clean** command:

`$ make dist-clean`

* **Running the program**

To run the compiled program with a previously defined test file, use the **run** command:

`$ make run`

To run the program with another .ly file, run **bin/prog**:

`bin/prog $(FILE_PATH)`

The .ly file must be in a simplified format and must have this structure:

```
  \key melody_scale
  \time melody_tempo
  melody_notes_in_Lilypond_format
```
An example of a correct format can be found in [only_notes.ly](https://github.com/joao18araujo/ly_parser/blob/master/only_notes.ly) file:

```
\key c \major
\time 4/4
g,4 c, g c
g' c' g'' c''
g' c' a c
g, c, d,
```

Currently, the melody must be monophonic and its note with the shortest duration must be a 8th note with no dots.
