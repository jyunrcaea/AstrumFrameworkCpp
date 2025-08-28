#pragma once
#include "DataManager.hpp"

namespace InGame {
	class NoteState
	{
	public:
		double GetStarting() const {
			return starting;
		}
		double GetEnding() const {
			return ending;
		}
		bool GetIsHit() const {
			return isHit;
		}

		void Hit() { isHit = true; }
		void Miss() { isMiss = true; }

	private:
		double starting;
		double ending;
		bool isHit = false;
		bool isMiss = false;
	};
}