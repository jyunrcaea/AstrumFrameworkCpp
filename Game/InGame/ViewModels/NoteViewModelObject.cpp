#include "NoteViewModelObject.hpp"

namespace InGame {
	void NoteViewModelObject::GenerateNote(const Arcaea::NoteData& data) {
		switch (data.NoteType) {
		case Arcaea::NoteType::Tap:
			AddObject(std::make_shared<NoteViewObject>(data));
			break;
		case Arcaea::NoteType::Hold:
			AddObject(std::make_shared<HoldNoteViewObject>(data));
			break;
		case Arcaea::NoteType::Arc:
			AddObject(std::make_shared<ArcViewObject>(data));
			break;
		case Arcaea::NoteType::Trace:
			AddObject(std::make_shared<TraceLineViewObject>(data));
			break;
		case Arcaea::NoteType::ArcTap:
			AddObject(std::make_shared<SkyNoteViewObject>(data));
			break;
		}
	}
}