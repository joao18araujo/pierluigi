
\version "2.18.2"
% automatically converted by musicxml2ly from beethoven2.xml

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
PartPOneVoiceOne =  {
    \clef "treble" \key c \major \numericTimeSignature\time 4/4 e'4 e'4
    f'4 g'4 | % 2
    g'4 f'4 e'4 d'4 | % 3
    c'4 c'4 d'4 e'4 | % 4
    e'4 ~ e'8 [ d'8 ] d'2 \break | % 5
    e'4 e'4 f'4 g'4 | % 6
    g'4 f'4 e'4 d'4 | % 7
    c'4 c'4 d'4 e'4 | % 8
    d'4 ~ d'8 [ c'8 ] c'2 \bar "|."
    }

PartPTwoVoiceOne =  {
    \clef "treble" \key c \major \numericTimeSignature\time 4/4 e'4 e'4
    a'4 d'4 | % 2
    e'4 f'4 e'4 a'4 | % 3
    a'4 c''4 a'4 f'4 | % 4
    b'4 b'8 [ g'8 ] e'2 \break | % 5
    d''4 f'4 g'4 f'4 | % 6
    c''4 f''4 d'4 f'4 | % 7
    a'4 r4 a'4 g'4 | % 8
    b'4 ~ b'8 [ g'8 ] a'2 \bar "|."
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

