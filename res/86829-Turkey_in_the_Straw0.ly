
\version "2.18.2"
% automatically converted by musicxml2ly from 86829-Turkey_in_the_Straw.mxl

\header {
    encodingsoftware = "MuseScore 1.2"
    encodingdate = "2013-02-01"
    }

#(set-global-staff-size 20.0762645669)
\paper {
    paper-width = 21.0\cm
    paper-height = 29.7\cm
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
PartPOneVoiceOne =  {
    \clef "treble" \key c \major \numericTimeSignature\time 4/4 \partial
    4

    c''4 c'' g'' g''
    a'' a'' g''2
    f''4 f'' e'' e''
    d'' d'' c''2
    g''4 g'' f'' f''
    e'' e'' d''2
    g''4 g'' f'' f''
    e'' e'' d''2
    c''4 c'' g'' g''
    a'' a'' g''2
    f''4 f'' e'' e''
    d'' d'' c''2
    }

  PartPTwoVoiceOne =  {
      \clef "treble" \key d \major \numericTimeSignature\time 4/4 fis'8 c'8 bes8 ais8 b8 gis'8 fis'8 fis'8 dis'8 ees'8 fis'8 g'8 f8 fis8 f'4 b'8 c''8 dis''4 d''4 b'8 c'8 b8 e'8 a'4 gis'4 c''4 dis''8 cis'8 bes8 ais8 b'8 c''8 f'8 cis'8 dis8 g8 fis'8 g'8 f8 fis8 c'4 fis'8 cis''8 d''4 fis''4 d''8 ais'8 bes8 cis'8 fis'4 c'4 b4 c,4 dis8 cis'4 dis8 f'4 cis'4 a8 cis'4 a8 fis'2 ees8 dis'4 bes8 gis'4 gis4 ees8 gis'4 g8 gis'2 bes'4 b'4 c'4 fis'4 d'4 a4 cis4 bes,8 c'8 dis'8 f'8 d'8 g'8 c'8 dis8 bes,8 cis8 fis8 b,8 cis'8 e8 bes4 c,4




      }



% The score definition
\score {
	\midi {
		  \tempo 4 = 120
		}
    <<
        \new Staff <<
            \set Staff.instrumentName = "Violin"
            \set Staff.shortInstrumentName = "Vln."
            \context Staff <<
                \context Voice = "PartPOneVoiceOne" { \PartPOneVoiceOne }
                >>
            >>

		\new Staff <<
            \set Staff.instrumentName = "Piano"
            \set Staff.shortInstrumentName = "Pno."
            \context Staff <<
                \context Voice = "PartPTwoVoiceOne" { \PartPTwoVoiceOne }
                >>
            >>

        >>
    \layout {}
    % To create MIDI output, uncomment the following line:
    %  \midi {}
    }
