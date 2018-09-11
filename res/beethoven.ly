
\version "2.18.2"
% automatically converted by musicxml2ly from beethoven.xml

\header {
    encodingsoftware = "MuseScore 2.0.2"
    encodingdate = "2018-04-09"
    composer = Composer
    title = Title
    }

#(set-global-staff-size 20.0750126457)
\paper {
    paper-width = 21.01\cm
    paper-height = 29.69\cm
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
PartPOneVoiceOne =  \relative e' {
    \clef "treble" \key c \major \numericTimeSignature\time 4/4 e4 e4 f4
    g4 | % 2
    g4 f4 e4 d4 | % 3
    c4 c4 d4 e4 | % 4
    e4 ~ e8 [ d8 ] d2 \break | % 5
    e4 e4 f4 g4 | % 6
    g4 f4 e4 d4 | % 7
    c4 c4 d4 e4 | % 8
    d4 ~ d8 [ c8 ] c2 \bar "|."
    }


% The score definition
\score {
    <<
        \new Staff <<
            \set Staff.instrumentName = "Piano"
            \set Staff.shortInstrumentName = "Pno."
            \context Staff << 
                \context Voice = "PartPOneVoiceOne" { \PartPOneVoiceOne }
                >>
            >>
        
        >>
    \layout {}
    % To create MIDI output, uncomment the following line:
    %  \midi {}
    }

