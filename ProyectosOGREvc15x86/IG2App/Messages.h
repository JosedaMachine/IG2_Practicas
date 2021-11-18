#pragma once
enum Messages { R, PlaneExplodes, SinBadDies };

struct Message{
	Message(Messages mensaje) {
		m = mensaje;
	}

	Messages m;
};
