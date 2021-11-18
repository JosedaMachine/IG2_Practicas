#pragma once
enum Messages { R, Samir, SamirExplota };

struct Message{
	Message(Messages mensaje) {
		m = mensaje;
	}

	Messages m;
};
