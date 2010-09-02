#ifndef _TIMING_DATA_H_
#define _TIMING_DATA_H_

#include "RStation.h"

// please edit this until you think it is sane.

enum NoteType {
	NOTE_TAP,
	NOTE_HOLD,
	NOTE_ROLL,
	NOTE_TAIL,
	NOTE_MINE
};

enum NoteAttribute {
	NOTE_ATTR_FAKE,
	NOTE_ATTR_VISIBLE
};

struct Note
{
	// Generic stuff.
	NoteType type;
	std::vector<NoteAttribute> flags;

	// For games which use columns (StepMania-esque)
	int column;
	int width; // cover multiple columns

	// For mouse-based games which use coords (osu!-esque)
	float scale;
	vec3 position;
};

struct NoteRow
{
	std::vector<Note> notes; // Notes on this row
	int time; // Time in milliseconds.

	// This is independent of time - use for stops, delays, warping, whatever.
	float scroll_speed;
};

struct NoteRegion
{
	int combo_rate; // aka tickcount
	float bpm; // For display purposes, not timing.

	struct TimeSignature
	{
		int numerator;
		int denominator;
	} time_sig;

	int time;
};

struct TimingData
{
	std::vector<NoteRow> note_rows;
	std::vector<NoteRegion> note_regions;

	int timing_offset;
};

#endif
