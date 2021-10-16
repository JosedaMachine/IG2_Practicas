#pragma once
enum Messages { R };

struct Message{
	Message(Messages mensaje) {
		m = mensaje;
	}

	Messages m;
};
