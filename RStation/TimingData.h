#ifndef _TIMING_DATA_H_
#define _TIMING_DATA_H_

// please edit this until you think it is sane.

enum NoteType {
	NOTE_TAP,
	NOTE_HOLD,
	NOTE_ROLL,
	NOTE_MINE
};

enum NoteAttribute {
	NOTE_ATTR_FAKE,
	NOTE_ATTR_VISIBLE
};

struct Note
{
	NoteType type;
	int column;
	float width;
	vec3 position;
	std::vector<NoteAttribute> flags;
};

struct TimingData
{
	std::vector<Note> note_row; // notes on this row
	int time; // time in milliseconds.
	/*
	 * Note: This can be zero. Notes will always arrive on time, regardless
	 * of the scrolling speed.
	 */
	float scroll_speed;
};

#endif
