#include "camera_modifier_factory.hpp"

#include "null_camera_modifier.hpp"
#include "highlight_modifier_decorator.hpp"

CameraModifierFactory::CameraModifierFactory() {

}

CameraModifier* CameraModifierFactory::make_modifier(
	CameraModifierSettings &settings, ViewSettings view_settings) {
	CameraModifier* mod = new NullCameraModifier();

	// loop through the modifiers
	for (auto mod_value: settings.parameters) {
		// get the definition of the modifier
		Util::assert_eq(mod_value.is<picojson::object>(),
			"Error in modifier definition");
		picojson::value::object &mod_obj = mod_value.get<picojson::object>();

		// check if modifier is active
		bool active = mod_obj["active"].evaluate_as_boolean();
		if (!active)
			continue;

		// get the type of modifier
		std::string mod_type = mod_obj["type"].to_str();

		// get the settings for this modifier
		picojson::value settings_value = mod_obj["settings"];
		Util::assert_eq(settings_value.is<picojson::object>(),
			"Error in settings for modifier");
		picojson::value::object &settings_obj = 
			settings_value.get<picojson::object>();

		// loop through and create the correct modifier
		if (mod_type.compare("Highlight") == 0) {
			mod = new HighlightModifierDecorator(mod, settings_obj, 
				view_settings);
		}
	}

	return mod;
}