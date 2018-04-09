
\version "2.18.2"
% automatically converted by musicxml2ly from cancan.xml

\header {
    encodingsoftware = "MuseScore 2.0.2"
    source = "http://musescore.com/score/1712921"
    encodingdate = "2018-04-09"
    composer = Composer
    title = Title
    }

#(set-global-staff-size 29.0218110236)
\paper {
    paper-width = 21.01\cm
    paper-height = 29.69\cm
    top-margin = 1.8\cm
    bottom-margin = 2.2\cm
    left-margin = 1.5\cm
    right-margin = 1.2\cm
    }
\layout {
    \context { \Score
        autoBeaming = ##f
        }
    }
PartPOneVoiceOne =  {
    \clef "treble_8" \key g \major \numericTimeSignature\time 4/4 | % 1
    \tempo 2=120 | % 1
    g1 | % 2
    a4 -2 c'4 -1 b4 a4 -2 | % 3
    d'2 -3 d'2 -3 | % 4
    d'4 -3 e'4 b4 c'4 -1 \break | % 5
    a2 -2 a2 -2 | % 6
    a4 -2 c'4 -1 b4 a4 -2 | % 7
    g4 g'4 -3 fis'4 -2 e'4 | % 8
    d'4 -3 c'4 -1 b4 a4 -2 \break | % 9
    g1 | \barNumberCheck #10
    a4 -2 c'4 -1 b4 a4 -2 | % 11
    d'2 -3 d'2 -3 | % 12
    d'4 -3 e'4 b4 c'4 -1 \break | % 13
    a2 -2 a2 -2 | % 14
    a4 -2 c'4 -1 b4 a4 -2 | % 15
    g4 d'4 -3 a4 -2 b4 | % 16
    g1 \bar "|."
    }

  PartPTwoVoiceOne =  {
      \clef "treble" \key c \major \numericTimeSignature\time 4/4 g1 f4 aes4 gis,4 f,4 bes2 f2 b4 cis'4 g,4 c4 fis,2 a,2 f4 aes4 b,4 f,4 b,4 e'4 ais4 e4 bes,4 c4 g,4 a,4 ees,1 a,4 e4 g,4 a,4 b2 bes,2 b4 g4 g4 e4 fis,2 c2 f4 c4 g,4 c4 g,4 f4 fis,4 gis4 g,1
      }

% The score definition
\score {
  \midi {
      \tempo 4 = 72
    }
    <<
        \new Staff <<
            \set Staff.instrumentName = "Piano"
            \context Staff <<
                \context Voice = "PartPOneVoiceOne" { \PartPOneVoiceOne }
                >>
            >>

        \new Staff <<
            \set Staff.instrumentName = "Piano"
            \set Staff.shortInstrumentName = "Pno"
            \context Staff <<
                \context Voice = "PartPTwoVoiceOne" { \PartPTwoVoiceOne }
                >>
            >>




        >>
    \layout {}
    % To create MIDI output, uncomment the following line:
    %  \midi {}
    }
