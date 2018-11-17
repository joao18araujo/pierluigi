
\version "2.18.2"
% automatically converted by musicxml2ly from 1675666-Top_Gun_Theme.mxl

\header {
    encodingsoftware = "MuseScore 2.0.2"
    source = "http://api.musescore.com/score/1675666"
    encodingdate = "2016-01-26"
    title = "Top Gun Theme "
    }

#(set-global-staff-size 20.0750126457)
\paper {
    paper-width = 21.59\cm
    paper-height = 27.94\cm
    top-margin = 1.0\cm
    bottom-margin = 2.0\cm
    left-margin = 1.0\cm
    right-margin = 1.0\cm
    }
\layout {
    \context { \Score
        autoBeaming = ##f
        }
    }


CounterpointVoice = {
	\clef bass \key g \major \time 4/4
	g,8 e8 d8 fis8 b8 b8 a16 a,16 b,16 d16
	a,16 e16 g16 g,16 a,8 fis8 fis,8 a,8 b,16 e16
	c16 fis16 b,8 d8 fis16 c16 g,16 d16 a,8 a8
	g16 d16 e16 e,16 g,8 b,8 c4. a,4. e8 b,8
	b,8 b8 fis8 d8 e16 c16 g16 g,16 c16 e16
	g16 g,16 c8 fis8 fis,8 a,8 b,16 e16 a,16 c16
	b,8 d8 fis16 fis,16 b,16 g16 a,8 e8 g16 d16
	e16 b,16 b,2 fis2 e8 b,8 b,8 b8 b,8 d8
	e16 c16 g16 g,16 c16 e16 g16 d16 fis8 fis,8
	fis8 c8 e16 e,16 a,16 c16 g,8 d8 fis16 c16
	b,16 g16 e8 c8 g16 d16 e16 b,16 g,8 b,8
	fis8 fis,8 a,4 c4 e8 b,8 b,8 fis8 b8 fis8
	a16 e16 g16 g,16 c16 e16 g16 d16 fis8 fis,8
	c8 a,8 e16 e,16 a,16 fis16 d8 g8 g,16 d16
	c16 e16 b,8 fis8 b16 fis16 e16 c'16 g2
}

PartPOneVoiceOne =  {
    \clef "treble_8" \key g \major \numericTimeSignature\time 4/4 g4 d'4
    d'4 c'8 [ b8 ] | % 2
    c'8 [ b8 ] a4 a4 g8 [ a8 ] | % 3
    b4 a8 [ b8 ] c'4 b8 [ g8 ] | % 4
    b4 a2. \break | % 5
    g4 d'4 d'4 c'8 [ b8 ] | % 6
    c'8 [ b8 ] a4 a4 g8 [ a8 ] | % 7
    b4 a8 [ b8 ] c'4 b8 [ g8 ] | % 8
    d'1 \break | % 9
    g4 d'4 d'4 c'8 [ b8 ] | \barNumberCheck #10
    c'8 [ b8 ] a4 a4 g8 [ a8 ] | % 11
    b4 a8 [ b8 ] c'4 b8 [ g8 ] | % 12
    b4 a4 a2 \break | % 13
    g4 d'4 d'4 c'8 [ b8 ] | % 14
    c'8 [ b8 ] a4 a4 g8 [ a8 ] | % 15
    \[ b4 \2 -0 b8 [ c'8 -1 ] d'4 ^\fermata -3 d'8 -1 [ e'8 -3 ] s2 \]
    g'2 ^\fermata -4 \bar "|."
    }

% The score definition
\score {
    <<
        \new Staff <<
            \set Staff.instrumentName = "Classical Guitar"
            \set Staff.shortInstrumentName = "Guit."
            \context Staff <<
                \context Voice = "PartPOneVoiceOne" { \PartPOneVoiceOne }
                >>
            >>



		\new Staff <<
			\set Staff.instrumentName = "Piano"
			\set Staff.shortInstrumentName = "Pno."
			\context Staff <<
				\context Voice = "CounterpointVoice" { \CounterpointVoice }
			>>
		>>

        >>
    \layout {}
     \midi {
		\tempo 4 = 120
	 }
    }
