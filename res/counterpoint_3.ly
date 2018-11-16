
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
	\key g \major \time 4/4
	g,16 b,16 e16 e16 b16 fis16 b16 b,16 fis16 b16
	b,16 d16 a,32 a32 a32 e32 d32 g32 g,32 g32
	e32 a32 e32 a32 b,32 g32 d32 g32 a,16 c16
	fis16 c16 fis16 fis,16 c16 fis16 e,32 b,32 e32 b,32
	fis32 fis,32 fis32 fis,32 g16 g,16 d16 g16 a,32 c32
	fis32 c32 g32 d32 g32 g,32 a16 a,16 e16 a16
	g,32 b,32 g32 g,32 g,32 e32 b,32 e32 d16 g16
	g,16 g16 fis,8. c8. fis8. c8. e,16 e16 b,16 e16
	fis16 b16 b,16 d16 fis16 b16 fis16 b16 c32 e32
	a32 a,32 b,32 d32 g32 g,32 a32 a,32 e32 a32
	b,32 g32 d32 g32 fis,16 a,16 c16 fis16 c16 fis16
	c16 fis16 g,32 b,32 e32 e,32 c32 fis32 c32 fis32
	d16 g16 d16 g16 c32 fis32 c32 fis32 d32 g32
	d32 g32 e16 a16 e16 a16 d32 g32 d32 g32
	g,32 e32 b,32 e32 fis4 b4 fis4 b4 b,16 e16
	b,16 e16 fis16 b16 fis16 b16 fis16 b16 b,16 d16
	a,32 c32 e32 a32 d32 g32 g,32 g32 e32 a32
	e32 a32 b,32 g32 g,32 g32 a,16 fis16 c16 fis16
	c16 fis16 fis,16 a,16 e,32 e32 b,32 e32 c32 fis32
	fis,32 fis32 d16 g16 d16 g16 a,32 fis32 c32 fis32
	d32 g32 d32 g32 e16 a16 e16 a16 b,32 d32
	g32 g,32 g,32 b,32 e32 b,32 g16 d16 g16 g,16
	a,16 c16 fis16 fis,16 fis8 fis,8 c8 fis8 b,16 e16
	e,16 e16 fis16 b16 fis16 b16 fis16 b16 fis16 b16
	c32 a32 a,32 e32 b,32 d32 g32 d32 a32 e32
	a32 a,32 b,32 g32 d32 g32 c16 fis16 fis,16 c16
	fis16 fis,16 c16 fis16 e,32 g,32 b,32 e32 c32 fis32
	fis,32 a,32 d16 g16 d16 g16 d32 g32 g,32 g32
	e32 a32 a,32 c32 b16 b,16 fis16 b16 b,32 d32
	b32 fis32 c'32 g32 c'32 g32 g'2
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
