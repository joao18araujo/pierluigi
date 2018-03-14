#include <iostream>
#include <cmath>
#include <list>
#include <set>

using namespace std;

typedef struct _Note{
    string base;
    string modifier;
    int duration;
} Note;

#define Y_BLOCK 5
string base;
#define X_BLOCK 142
#define SCALE_SHIFT (12 * Y_BLOCK)

const list< set<string> > scale {
    { "c", "bis" },  // pos = 0
    { "cis", "des" },
    { "d" },
    { "dis", "ees" },
    { "e", "fes" },
    { "eis", "f" },
    { "fis", "ges" },
    { "g" },
    { "gis", "aes" },
    { "a" },
    { "ais", "bes"},
    { "b", "ces" } // pos = 11
};

Note parse_note(const char *s){
    char base[128], modifier[128];
    int duration = 0, idx_base = 0, idx_mod = 0;

    for (auto p = s; *p; ++p){
        if (isdigit(*p)){
            duration *= 10;
            duration += (*p - '0');
        } else if (isalpha(*p))
            base[idx_base++] = *p;
        else
            modifier[idx_mod++] = *p;
    }

    base[idx_base] = 0;
    modifier[idx_mod] = 0;

    Note n { base, modifier, duration };

    return n;
}

int extract_tempo(FILE *score){
    int tempo = 0;

    fscanf(score, " \\tempo %d ", &tempo);

    return tempo;
}

pair<int, int> extract_compass(FILE *score){
    pair<int, int> compass;

    fscanf(score, " \\time %d/%d ", &compass.first, &compass.second);

    return compass;
}

int find_note(const string& n){
    int index = 0;

    for (auto s : scale){
        if (s.count(n))
            return index;

        ++index;
    }

    return -1;
}

int pitch(const Note& n){
    int pos = find_note(n.base);

    if (pos == -1)
        return -1;

    int h = pos * Y_BLOCK - SCALE_SHIFT;

    for (auto p : n.modifier){
        if (p == '\'')
            h += SCALE_SHIFT;
	    else if (p == ',')
            h += SCALE_SHIFT;
	}

    return h;
}

Note extract_relative(FILE *score){
    char info[16];

    fscanf(score, " \\relative %s ", info);

    Note note = parse_note(info);

    return note;
}

Note extract_key(FILE *score){
    char base_note[256];

    fscanf(score, "\\key %s ", base_note);

    Note note = parse_note(base_note);

    return note;
}

bool is_pause(const Note& note){
    return find_note(note.base) == -1;
}

list<Note> extract_notes(FILE *score, const Note& rel){
    Note prev = rel;
    char n[128];
    list<Note> notes;

    while (fscanf(score, "%s", n) == 1){
        auto note = parse_note(n);

        if (not note.duration)
            note.duration = prev.duration;

        if (note.modifier.size() == 0){
            note.modifier = prev.modifier;

            int p = pitch(note);
            int q = pitch(prev);

            if (p != -1 and q != -1){
                if (p - q > 120)
                    note.modifier.pop_back();

                if (p - q < -120)
                    note.modifier.push_back('\'');
            }
        }else{
            if (note.modifier.front() == '\'')
                note.modifier += prev.modifier;
        }

        if (is_pause(note))
            prev.duration = note.duration;
        else
            prev = note;

        notes.push_back(note);
    }

    return notes;
}

unsigned frames(const list<Note>& notes, int unit){
    double fs = 0.0;

    for (auto note : notes){
        fs += (double) unit / note.duration;
    }
    return (unsigned) round(fs);
}

int main(int argc, char *argv[]){
    if (argc < 3){
        printf("Usage: %s {score.ly} {output}\n", argv[0]);
        return -1;
    }

    FILE *score = fopen(argv[1], "r");

    if (not score){
        printf("Invalid score file: %s\n", argv[1]);
        return -2;
    }

	FILE *output = fopen(argv[2], "w");

	if(not output){
		printf("Invalid output file: %s\n", argv[2]);
		return -3;
	}

	int time = extract_tempo(score);

    // printf("Score = %s\n", argv[1]);
    // printf("Tempo = %d\n", time);

	int n_blocks = 3000, n_background = 3;

	fprintf(output, "%d\n", time);
	fprintf(output, "%d %d\n", n_blocks, n_background);

    auto compass = extract_compass(score);
    // printf("Compass = %d/%d\n", compass.first, compass.second);

    auto relative = extract_relative(score);
    // printf("Relative = %d [%s]\n", pitch(relative), relative.base.c_str());

    auto n = extract_key(score);
    // printf("Key = %d [%s]\n", pitch(n), n.base.c_str());

    auto notes = extract_notes(score, relative);

    // printf("count = %lu, frames = %u\n", notes.size(), frames(notes, compass.second));

	fprintf(output, "50 0 0\n");
	fprintf(output, "50 0 0\n");
	fprintf(output, "50 0 0\n");

	for (auto note : notes){
		int h = pitch(note);
		int d = (compass.second * 4) / note.duration;

		if(h <= 0){
			while(d--){
				fprintf(output, "50 0 0\n");
			}
		}else{
			fprintf(output, "%d 0 1 %d\n", h-40, h);
			while(--d){
				fprintf(output, "%d 0 0\n", h-40);
			}
		}
    }


    int left = 25;
	while(left--){
		fprintf(output, "50 0 0\n");
	}


    fclose(score);

	fclose(output);

    return 0;
}
