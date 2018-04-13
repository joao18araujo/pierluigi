
\version "2.18.2"
% automatically converted by musicxml2ly from 30887-Frere_Jacques.mxl

\header {
    encodingsoftware = "MuseScore 1.1"
    encodingdate = "2011-11-19"
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
PartPOneVoiceOne =  \relative c'' {
    \clef "treble" \key c \major \numericTimeSignature\time 4/4 c4 d4 e4
    c4 | % 2
    c4 d4 e4 c4 | % 3
    e4 f4 g2 | % 4
    e4 f4 g2 | % 5
    g8 [ a8 g8 f8 ] e4 c4 \break | % 6
    g'8 [ a8 g8 f8 ] e4 c4 | % 7
    c4 g4 c2 | % 8
    c4 g4 c2 \bar "|."
    }

PartPOneVoiceOneLyricsOne =  \lyricmode { "Frè" -- re Jac -- "ques,"
    "Frè" -- re Jac -- "ques," Dor -- mez "vous ?" Dor -- mez "vous ?"
    Son -- ti -- nes Son -- ti -- nes Ding ding "dong!" Ding ding
    "dong!" }

% The score definition
\score {
    <<
        \new Staff <<
            \set Staff.instrumentName = "Voice"
            \context Staff << 
                \context Voice = "PartPOneVoiceOne" { \PartPOneVoiceOne }
                \new Lyrics \lyricsto "PartPOneVoiceOne" \PartPOneVoiceOneLyricsOne
                >>
            >>
        
        >>
    \layout {}
    % To create MIDI output, uncomment the following line:
    %  \midi {}
    }

