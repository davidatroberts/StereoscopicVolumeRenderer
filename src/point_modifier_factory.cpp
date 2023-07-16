#include "point_modifier_factory.hpp"

#include "null_modifier.hpp"
#include "perlin_modifier_decorator.hpp"
#include "shading_modifier_decorator.hpp"
#include "util.hpp"

PointModifierFactory::PointModifierFactory() {}

PointModifier *PointModifierFactory::make_modifier(
	PointModifierSettings &settings, RaySettings ray_settings, VolumeSettings volume_settings) {
	PointModifier *mod = new NullModifier();

	// loop through the parameters for the modifiers
	for (auto mod_value : settings.parameters) {
		// get the definition of the modifer
		Util::assert_eq(mod_value.is<picojson::object>(), "Error in modifier definition");
		picojson::value::object &mod_obj = mod_value.get<picojson::object>();

		// check if the modifier is active
		bool active = mod_obj["active"].evaluate_as_boolean();
		if (!active)
			continue;

		// get the type of modifier
		std::string mod_type = mod_obj["type"].to_str();

		// get the settings for this modifier
		picojson::value settings_value = mod_obj["settings"];
		Util::assert_eq(settings_value.is<picojson::object>(), "Error in settings for modifier");
		picojson::value::object &settings_obj = settings_value.get<picojson::object>();

		// loop through create the correct modifier
		if (mod_type.compare("Perlin") == 0) {
			mod = new PerlinModifierDecorator(mod, settings_obj, ray_settings, volume_settings);
		} else if (mod_type.compare("Shading") == 0) {
			mod = new ShadingModifierDecorator(mod, settings_obj, ray_settings, volume_settings);
		}
	}

	return mod;
}
