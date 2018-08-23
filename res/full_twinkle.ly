
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
    \clef "treble" \key c \major \numericTimeSignature\time 4/4
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
      d'' d'' c''2 \bar "|."
    }

PartPTwoVoiceOne =  {
    \clef "treble" \key c \major \numericTimeSignature\time 4/4
    c'4 e'4 e'4 g'4
    f'4 c''4 e''2 d''4
    a'4 c''4 c''4 b'4
    b4 c'2 e'4 b'4
    d''4 d'4 c''4 c'4
    b'2 b'4 e''4 d''4
    a'4 c''4 c'4 d'2
    e'4 a'4 e'4 b'4
    a'4 c''4 g'2 a'4
    f'4 g'4 e'4 f'4
    b'4 c''2
     \bar "|."
  }

% The score definition
\score {
	\midi {
		  \tempo 4 = 120
		}
    <<
        \new Staff <<
          \set Staff.instrumentName = "Melodia"
            \context Staff <<
                \context Voice = "PartPOneVoiceOne" { \PartPOneVoiceOne }
                >>
            >>

        \new Staff <<
            \set Staff.instrumentName = "Contraponto"
            \context Staff <<
                \context Voice = "PartPTwoVoiceOne" { \PartPTwoVoiceOne }
                >>
            >>

        >>
    \layout {}
    % To create MIDI output, uncomment the following line:
    %  \midi {}
    }
