% Lily was here -- automatically converted by /usr/bin/midi2ly from test.mid
\version "2.14.0"

\layout {
  \context {
    \Voice
    \remove "Note_heads_engraver"
    \consists "Completion_heads_engraver"
    \remove "Rest_engraver"
    \consists "Completion_rest_engraver"
  }
}

trackAchannelA = {


  \key c \major

  \time 4/4


  \key c \major

  \tempo 4 = 120

}

trackAchannelB = \relative c {
  g,4 c, g c
  | % 2
  g' c' g'' c''
  | % 3
  g' c' a c
  | % 4
  g, c, d, 
}

trackA = <<

  \clef bass

  \context Voice = voiceA \trackAchannelA
  \context Voice = voiceB \trackAchannelB
>>


\score {
  <<
    \context Staff=trackA \trackA
  >>
  \layout {}
  \midi {}
}
