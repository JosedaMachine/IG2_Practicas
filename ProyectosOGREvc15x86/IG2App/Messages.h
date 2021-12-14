#pragma once
enum Messages { R, PlaneExplodes, SinBadDies, HappyInvBeing, HappyInvFinal };

struct Message{
	Message(Messages mensaje) {
		m = mensaje;
	}

	Messages m;
};
