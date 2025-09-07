#include "DataManager.hpp"
#include "../../Astrum/Objects/AstrumMaterialObject.hpp"

namespace Selector {
	class CurrentSelectedObject : public AstrumMaterialObject {
	public:
		CurrentSelectedObject();
		virtual void Update() override;
	};
}